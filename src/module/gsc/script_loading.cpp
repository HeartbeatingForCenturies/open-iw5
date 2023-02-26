#include <std_include.hpp>
#include <loader/module_loader.hpp>
#include "game/game.hpp"

#include "script_loading.hpp"

#include "module/console.hpp"
#include "module/file_system.hpp"
#include "module/scripting.hpp"

#include <utils/compression.hpp>
#include <utils/hook.hpp>
#include <utils/memory.hpp>

#include <gsc_interface.hpp>

namespace gsc
{
	namespace
	{
		utils::memory::allocator script_file_allocator;

		std::unordered_map<std::string, game::native::ScriptFile*> loaded_scripts;

		std::unordered_map<std::string, int> main_handles;
		std::unordered_map<std::string, int> init_handles;

		const game::native::dvar_t* developer_script;

		void clear()
		{
			script_file_allocator.clear();
			loaded_scripts.clear();
			main_handles.clear();
			init_handles.clear();
		}

		bool read_raw_script_file(const std::string& name, std::string* data)
		{
			assert(data->empty());

			char* buffer{};
			const auto file_len = game::native::FS_ReadFile(name.data(), &buffer);
			if (file_len > 0 && buffer)
			{
				data->append(buffer, file_len);
				game::native::Hunk_FreeTempMemory(buffer);
				return true;
			}

			return false;
		}

		std::pair<xsk::gsc::buffer, std::vector<std::uint8_t>> read_compiled_script_file(const std::string& name, const std::string& real_name)
		{
			const auto* script_file = game::native::DB_FindXAssetHeader(game::native::ASSET_TYPE_SCRIPTFILE, name.data(), false).scriptfile;
			if (!script_file)
			{
				throw std::runtime_error(std::format("Could not load scriptfile '{}'", real_name));
			}

			console::info("Decompiling scriptfile '%s'\n", real_name.data());

			const auto len = script_file->compressedLen ? script_file->compressedLen : script_file->len;
			const std::string stack{ script_file->buffer, static_cast<std::uint32_t>(len) };

			const auto decompressed_stack = utils::compression::zlib::decompress(stack);
			std::vector<std::uint8_t> stack_data;
			stack_data.assign(decompressed_stack.begin(), decompressed_stack.end());

			return { { script_file->bytecode, static_cast<std::uint32_t>(script_file->bytecodeLen) } , stack_data };
		}

		game::native::ScriptFile* load_custom_script(const char* file_name, const std::string& real_name)
		{
			if (const auto itr = loaded_scripts.find(real_name); itr != loaded_scripts.end())
			{
				return itr->second;
			}

			try
			{
				auto& compiler = gsc::cxt->compiler();
				auto& assembler = gsc::cxt->assembler();

				std::string source_buffer;
				if (!read_raw_script_file(real_name + ".gsc", &source_buffer))
				{
					return nullptr;
				}

				std::vector<std::uint8_t> data;
				data.assign(source_buffer.begin(), source_buffer.end());

				const auto assembly_ptr = compiler.compile(real_name, data);
				// Pair of two buffers. First is the byte code and second is the stack
				const auto output_script = assembler.assemble(*assembly_ptr);

				const auto script_file_ptr = static_cast<game::native::ScriptFile*>(script_file_allocator.allocate(sizeof(game::native::ScriptFile)));
				script_file_ptr->name = file_name;

				const auto compressed_stack = utils::compression::zlib::compress({ reinterpret_cast<const char*>(output_script.second.data), output_script.second.size });
				const auto byte_code_size = output_script.first.size + 1;

				script_file_ptr->len = static_cast<int>(output_script.second.size);
				script_file_ptr->bytecodeLen = static_cast<int>(output_script.first.size);

				script_file_ptr->buffer = static_cast<char*>(script_file_allocator.allocate(compressed_stack.size()));
				std::memcpy(const_cast<char*>(script_file_ptr->buffer), compressed_stack.data(), compressed_stack.size());

				script_file_ptr->bytecode = static_cast<std::uint8_t*>(game::native::PMem_AllocFromSource_NoDebug(byte_code_size, 4, 0, game::native::PMEM_SOURCE_SCRIPT));
				std::memcpy(script_file_ptr->bytecode, output_script.first.data, output_script.first.size);

				script_file_ptr->compressedLen = static_cast<int>(compressed_stack.size());

				loaded_scripts[real_name] = script_file_ptr;

				return script_file_ptr;
			}
			catch (const std::exception& ex)
			{
				console::error("*********** script compile error *************\n");
				console::error("failed to compile '%s':\n%s", real_name.data(), ex.what());
				console::error("**********************************************\n");
				return nullptr;
			}
		}

		std::string get_script_file_name(const std::string& name)
		{
			const auto id = gsc::cxt->token_id(name);
			if (!id)
			{
				return name;
			}

			return std::to_string(id);
		}

		std::string get_raw_script_file_name(const std::string& name)
		{
			if (name.ends_with(".gsh"))
			{
				return name;
			}

			return name + ".gsc";
		}

		int db_is_x_asset_default(game::native::XAssetType type, const char* name)
		{
			if (loaded_scripts.contains(name))
			{
				return 0;
			}

			return game::native::DB_IsXAssetDefault(type, name);
		}

		void load_scripts_from_folder(const char* dir)
		{
			char path[game::native::MAX_OSPATH]{};
			char search_path[game::native::MAX_OSPATH]{};

			strncpy_s(search_path, dir, _TRUNCATE);
			strncat_s(search_path, "/", _TRUNCATE);

			auto num_files = 0;
			auto** list = file_system::list_files(search_path, "gsc", game::native::FS_LIST_ALL, &num_files, 10);

			for (auto i = 0; i < num_files; ++i)
			{
				const auto* script_file = list[i];
				console::info("Loading script %s...\n", script_file);

				const auto len = sprintf_s(path, "%s/%s", dir, script_file);
				if (len == -1)
				{
					continue;
				}

				// Scr_LoadScriptInternal will add the '.gsc' suffix so we remove it
				path[len - 4] = '\0';

				if (!game::native::Scr_LoadScript(path))
				{
					console::error("Script %s encountered an error while loading\n", path);
					continue;
				}

				console::info("Script %s.gsc loaded successfully\n", path);

				const auto main_handle = game::native::Scr_GetFunctionHandle(path, static_cast<std::uint16_t>(gsc::cxt->token_id("main")));
				if (main_handle)
				{
					console::info("Loaded '%s::main'\n", path);
					main_handles[path] = main_handle;
				}

				const auto init_handle = game::native::Scr_GetFunctionHandle(path, static_cast<std::uint16_t>(gsc::cxt->token_id("init")));
				if (init_handle)
				{
					console::info("Loaded '%s::init'\n", path);
					init_handles[path] = init_handle;
				}
			}

			file_system::free_file_list(list);
		}

		void load_scripts()
		{
			// Both SP & MP
			load_scripts_from_folder("scripts");

			// Game specific
			const auto* game_dir = game::is_mp() ? "scripts/mp" : "scripts/sp";
			load_scripts_from_folder(game_dir);
		}

		void g_scr_load_scripts_mp_stub()
		{
			load_scripts();
			utils::hook::invoke<void>(0x523DA0);
		}

		__declspec(naked) void g_scr_load_script_and_label_stub()
		{
			static const DWORD GScr_LoadScriptAndLabel_t = 0x5D9900;

			__asm
			{
				call GScr_LoadScriptAndLabel_t

				pushad
				call load_scripts
				popad

				ret
			}
		}

		void scr_load_level_stub()
		{
			for (const auto& handle : main_handles)
			{
				console::info("Executing '%s::main'\n", handle.first.data());
				const auto id = game::native::Scr_ExecThread(handle.second, 0);
				game::native::Scr_FreeThread(static_cast<std::uint16_t>(id));
			}

			utils::hook::invoke<void>(SELECT_VALUE(0x50AF70, 0x517410)); // Scr_LoadLevel

			for (const auto& handle : init_handles)
			{
				console::info("Executing '%s::init'\n", handle.first.data());
				const auto id = game::native::Scr_ExecThread(handle.second, 0);
				game::native::Scr_FreeThread(static_cast<std::uint16_t>(id));
			}			
		}

		void scr_begin_load_scripts_stub()
		{
			const auto comp_mode = developer_script->current.enabled ?
				xsk::gsc::build::dev :
				xsk::gsc::build::prod;

			gsc::cxt->init(comp_mode, [](const std::string& include_name) -> std::pair<xsk::gsc::buffer, std::vector<std::uint8_t>>
			{
				const auto real_name = get_raw_script_file_name(include_name);

				std::string file_buffer;
				if (!read_raw_script_file(real_name, &file_buffer) || file_buffer.empty())
				{
					const auto name = get_script_file_name(include_name);
					if (game::native::DB_XAssetExists(game::native::ASSET_TYPE_SCRIPTFILE, name.data()))
					{
						return read_compiled_script_file(name, real_name);
					}

					throw std::runtime_error(std::format("Could not load gsc file '{}'", real_name));
				}

				std::vector<std::uint8_t> script_data;
				script_data.assign(file_buffer.begin(), file_buffer.end());

				return { {}, script_data };
			});

			utils::hook::invoke<void>(SELECT_VALUE(0x4B4EE0, 0x561E80));
		}

		void scr_end_load_scripts_stub()
		{
			// Cleanup the compiler
			gsc::cxt->cleanup();

			utils::hook::invoke<void>(SELECT_VALUE(0x5DF010, 0x561D00));
		}
	}

	game::native::ScriptFile* find_script(game::native::XAssetType type, const char* name, int allow_create_default)
	{
		std::string real_name = name;
		const auto id = static_cast<std::uint16_t>(std::strtol(name, nullptr, 10));
		if (id)
		{
			real_name = gsc::cxt->token_name(id);
		}

		auto* script = load_custom_script(name, real_name);
		if (script)
		{
			return script;
		}

		return game::native::DB_FindXAssetHeader(type, name, allow_create_default).scriptfile;
	}

	class script_loading final : public module
	{
	public:
		void post_start() override
		{
			gsc::cxt = std::make_unique<xsk::gsc::iw5_pc::context>();
		}

		void post_load() override
		{
			if (game::is_sp()) this->patch_sp();
			else this->patch_mp();

			utils::hook(SELECT_VALUE(0x50C575, 0x50D4ED), scr_load_level_stub, HOOK_CALL).install()->quick();

			// ProcessScript
			utils::hook(SELECT_VALUE(0x44685E, 0x56B13E), find_script, HOOK_CALL).install()->quick();
			utils::hook(SELECT_VALUE(0x446868, 0x56B148), db_is_x_asset_default, HOOK_CALL).install()->quick();

			utils::hook(SELECT_VALUE(0x4FDD65, 0x523E03), scr_begin_load_scripts_stub, HOOK_CALL).install()->quick();
			utils::hook(SELECT_VALUE(0x4FDECF, 0x523F4D), scr_end_load_scripts_stub, HOOK_CALL).install()->quick(); // GScr_LoadScripts

			developer_script = game::native::Dvar_RegisterBool("developer_script", false, game::native::DVAR_NONE, "Enable developer script comments");

			scripting::on_shutdown([](int free_scripts) -> void
			{
				if (free_scripts)
				{
					clear();
				}
			});
		}

		static void patch_sp()
		{
			utils::hook(0x4BE6A5, g_scr_load_script_and_label_stub, HOOK_CALL).install()->quick();
		}

		static void patch_mp()
		{
			utils::hook(0x523F3E, g_scr_load_scripts_mp_stub, HOOK_CALL).install()->quick();
		}
	};
}

REGISTER_MODULE(gsc::script_loading)

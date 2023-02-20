#include <std_include.hpp>
#include <loader/module_loader.hpp>
#include "game/game.hpp"

#include "command.hpp"
#include "console.hpp"

#include <utils/hook.hpp>
#include <utils/io.hpp>
#include <utils/string.hpp>

namespace
{
	utils::hook::detour db_find_x_asset_header_hook;

	const game::native::dvar_t* g_dump_scripts;

	__declspec(naked) void db_load_stub_client(game::native::XZoneInfo*, unsigned int, int)
	{
		__asm
		{
			sub esp, 0Ch
			mov eax, [esp + 18h]

			mov ecx, game::native::DB_LoadXAssets
			add ecx, 7h
			push ecx
			ret
		}
	}

	void dump_gsc_script(const std::string& name, game::native::XAssetHeader header)
	{
		if (!g_dump_scripts->current.enabled)
		{
			return;
		}

		std::string buffer;
		buffer.append(header.scriptfile->name, std::strlen(header.scriptfile->name) + 1);
		buffer.append(reinterpret_cast<char*>(&header.scriptfile->compressedLen), sizeof(int));
		buffer.append(reinterpret_cast<char*>(&header.scriptfile->len), sizeof(int));
		buffer.append(reinterpret_cast<char*>(&header.scriptfile->bytecodeLen), sizeof(int));
		buffer.append(header.scriptfile->buffer, header.scriptfile->compressedLen);
		buffer.append(reinterpret_cast<char*>(header.scriptfile->bytecode), header.scriptfile->bytecodeLen);

		const auto out_name = std::format("gsc_dump/{}.gscbin", name);
		utils::io::write_file(out_name, buffer);

		console::info("Dumped %s\n", out_name.data());
	}

	game::native::XAssetHeader db_find_x_asset_header_stub(game::native::XAssetType type, const char* name, int allow_create_default)
	{
		const auto start = game::native::Sys_Milliseconds();
		const auto result = db_find_x_asset_header_hook.invoke<game::native::XAssetHeader>(type, name, allow_create_default);
		const auto diff = game::native::Sys_Milliseconds() - start;

		if (type == game::native::ASSET_TYPE_SCRIPTFILE)
		{
			dump_gsc_script(name, result);
		}

		if (diff > 100)
		{
			console::print(
				result.data == nullptr
				? console::con_type_error
				: console::con_type_warning,
				"Waited %i msec for asset '%s' of type '%s'.\n",
				diff,
				name,
				game::native::g_assetNames[type]
			);
		}

		return result;
	}
}

void enum_assets(const int type, const std::function<void(game::native::XAssetHeader)>& callback, const bool include_override)
{
	game::native::DB_EnumXAssets(type, static_cast<void(*)(game::native::XAssetHeader, void*)>([](game::native::XAssetHeader header, void* data)
	{
		const auto& cb = *static_cast<std::function<void(game::native::XAssetHeader)>*>(data);
		cb(header);
	}), &callback, include_override);
}

class fastfiles final : public module
{
public:
	void post_load() override
	{
		utils::hook(game::native::DB_LoadXAssets, db_load_stub, HOOK_JUMP).install()->quick();

		db_find_x_asset_header_hook.create(game::native::DB_FindXAssetHeader, &db_find_x_asset_header_stub);

		g_dump_scripts = game::native::Dvar_RegisterBool("g_dumpScripts", false, game::native::DVAR_NONE, "Dump GSC scripts to binary format");

		command::add("listassetpool", [](const command::params& params)
		{
			if (params.size() < 2)
			{
				console::info("listassetpool <poolnumber> [filter]: list all the assets in the specified pool\n");

				for (auto i = 0; i < game::native::ASSET_TYPE_COUNT; ++i)
				{
					console::info("%d %s\n", i, game::native::g_assetNames[i]);
				}

				return;
			}

			int type;
			try
			{
				type = std::stoi(params.get(1), nullptr, 0);
			}
			catch (const std::exception& ex)
			{
				console::error("Invalid pool passed. Got: %s, causing error: %s\n", params.get(1), ex.what());
				return;
			}

			if (type < 0 || type >= game::native::ASSET_TYPE_COUNT)
			{
				console::error("Invalid pool number passed, must be between [%d, %d]\n", 0, game::native::ASSET_TYPE_COUNT - 1);
				return;
			}

			console::info("Listing assets in pool %s\n", game::native::g_assetNames[type]);

			const std::string filter = params.get(2);
			enum_assets(type, [type, filter](game::native::XAssetHeader header)
			{
				const auto asset = game::native::XAsset{ type, header };
				const auto* const asset_name = game::native::DB_GetXAssetName(&asset);

				if (!filter.empty() && !utils::string::match_compare(filter, asset_name, false))
				{
					return;
				}

				console::info("%s\n", asset_name);
			}, true);
		});
	}

private:
	static void db_load_stub(game::native::XZoneInfo* zone_info, const unsigned int zone_count, const int sync)
	{
		for (unsigned int i = 0; i < zone_count; ++i)
		{
			if (zone_info[i].name)
			{
				console::info("Loading FastFile: %s (0x%X | 0x%X)\n", zone_info[i].name, zone_info[i].allocFlags, zone_info[i].freeFlags);
			}
		}

		return db_load_stub_client(zone_info, zone_count, sync);
	}
};

REGISTER_MODULE(fastfiles)

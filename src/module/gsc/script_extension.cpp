#include <std_include.hpp>
#include <loader/module_loader.hpp>
#include "game/game.hpp"

#include "script_extension.hpp"
#include "script_error.hpp"

#include "module/console.hpp"
#include "module/scripting.hpp"

#include <utils/hook.hpp>
#include <utils/string.hpp>

#include <gsc_interface.hpp>

namespace gsc
{
	std::uint16_t scr_func_max_id = 0x1C7;
	std::uint16_t scr_meth_max_id = 0x830C;

	void* func_table[1000];
	void* meth_table[1000];

	namespace
	{
		struct builtin_function
		{
			std::string name;
			std::uint16_t id; // actual 'name'
			void(*actionFunc)();
		};

		struct builtin_method
		{
			std::string name;
			std::uint16_t id; // actual 'name'
			void(*actionFunc)(game::native::scr_entref_t);
		};

		utils::hook::detour scr_register_function_hook;

		std::vector<builtin_function> custom_functions;
		std::vector<builtin_method> custom_methods;

		std::unordered_map<const char*, const char*> replaced_funcs;

		const char* vm_execute_code_pos = nullptr;
		DWORD vm_execute_addr;

		DWORD vm_execute_func_addr;
		DWORD vm_execute_meth_addr;

		void scr_register_function_stub(void* func, [[maybe_unused]] int type, unsigned int name)
		{
			assert(name);

			if ((name - 1) < scr_func_max_id)
			{
				func_table[name] = func;
			}
			else
			{
				meth_table[name] = func;
			}
		}

		unsigned int scr_get_function_stub(char** p_name, int* type)
		{
			std::memset(func_table, 0, sizeof(func_table));

			for (const auto& func : custom_functions)
			{
				scr_register_function_stub(reinterpret_cast<void*>(func.actionFunc), 0, func.id);
			}

			return utils::hook::invoke<unsigned int>(SELECT_VALUE(0x4CAC00, 0x527750), p_name, type); // Scr_GetFunction
		}

		unsigned int scr_get_method_stub(const char** p_name, int* type)
		{
			std::memset(meth_table, 0, sizeof(meth_table));

			for (const auto& meth : custom_methods)
			{
				scr_register_function_stub(reinterpret_cast<void*>(meth.actionFunc), 0, meth.id);
			}

			return utils::hook::invoke<unsigned int>(SELECT_VALUE(0x51A4F0, 0x5277C0), p_name, type); // Scr_GetMethod
		}

		const char* get_replaced_func_pos(const char* pos)
		{
			if (const auto itr = replaced_funcs.find(pos); itr != replaced_funcs.end())
			{
				return itr->second;
			}

			return pos;
		}

		__declspec(naked) void vm_execute_func_stub()
		{
			__asm
			{
				mov eax, dword ptr ds:[func_table + eax * 4]

				jmp vm_execute_func_addr
			}
		}

		__declspec(naked) void vm_execute_meth_stub()
		{
			__asm
			{
				mov edx, dword ptr ds:[meth_table + ecx * 4]

				jmp vm_execute_meth_addr
			}
		}

		__declspec(naked) void vm_execute_stub()
		{
			__asm
			{
				pushad

				push esi
				call get_replaced_func_pos;
				mov vm_execute_code_pos, eax
				pop esi

				popad

				mov esi, vm_execute_code_pos

				jmp vm_execute_addr
			}
		}

		void scr_print()
		{
			for (std::size_t i = 0; i < game::native::Scr_GetNumParam(); ++i)
			{
				console::info("%s", game::native::Scr_GetString(i));
			}
		}

		void scr_print_ln()
		{
			for (std::size_t i = 0; i < game::native::Scr_GetNumParam(); ++i)
			{
				console::info("%s", game::native::Scr_GetString(i));
			}

			console::info("\n");
		}
	}

	void register_function(const std::string& name, const game::native::BuiltinFunction& func)
	{
		const auto lowered_name = utils::string::to_lower(name);

		constexpr auto is_duplicate = [](const std::string s)
		{
			return [s](const builtin_function& f) { return s == f.name; };
		};

		if (std::ranges::any_of(custom_functions, is_duplicate(lowered_name)))
		{
			console::error("Function '%s' is already registered!", name.data());
			return;
		}

		++scr_func_max_id;
		custom_functions.push_back({ name, scr_func_max_id, func });
		cxt->func_add(name, scr_func_max_id);
	}

	void register_method(const std::string& name, const game::native::BuiltinMethod& meth)
	{
		const auto lowered_name = utils::string::to_lower(name);

		constexpr auto is_duplicate = [](const std::string s)
		{
			return [s](const builtin_method& m) { return s == m.name; };
		};

		if (std::ranges::any_of(custom_methods, is_duplicate(lowered_name)))
		{
			console::error("Method '%s' already registered!", name.data());
			return;
		}

		++scr_meth_max_id;
		custom_methods.push_back({ name, scr_meth_max_id, meth });
		cxt->meth_add(name, scr_meth_max_id);
	}

	const char* get_code_pos(int index)
	{
		if (static_cast<unsigned int>(index) >= game::native::scr_VmPub->outparamcount)
		{
			scr_error("Scr_GetCodePos: index is out of range");
			return "";
		}

		const auto* value = &game::native::scr_VmPub->top[-index];

		if (value->type != game::native::VAR_FUNCTION)
		{
			scr_error("Scr_GetCodePos requires a function as parameter");
			return "";
		}

		return value->u.codePosValue;
	}

	class script_extension final : public module
	{
	public:
		void post_load() override
		{
			utils::hook(SELECT_VALUE(0x4B4F87, 0x561F27), scr_get_function_stub, HOOK_CALL).install()->quick();
			utils::hook(SELECT_VALUE(0x4B4F92, 0x561F32), scr_get_method_stub, HOOK_CALL).install()->quick();

			utils::hook(SELECT_VALUE(0x611C5B, 0x56C8EB), vm_execute_func_stub, HOOK_JUMP).install()->quick();
			utils::hook::nop(SELECT_VALUE(0x611C5B + 5, 0x56C8EB + 5), 2);

			utils::hook(SELECT_VALUE(0x611F4C, 0x56CBDC), vm_execute_meth_stub, HOOK_JUMP).install()->quick();
			utils::hook::nop(SELECT_VALUE(0x611F4C + 5, 0x56CBDC + 5), 2);

			vm_execute_func_addr = SELECT_VALUE(0x611C62, 0x56C8F2);
			vm_execute_meth_addr = SELECT_VALUE(0x611F53, 0x56CBE3);

			scr_register_function_hook.create(SELECT_VALUE(0x49E190, 0x561520), scr_register_function_stub);

			utils::hook::set<game::native::BuiltinFunction>(SELECT_VALUE(0x92B8DC, 0x8ABDC4), scr_print);
			utils::hook::set<game::native::BuiltinFunction>(SELECT_VALUE(0x92B8E8, 0x8ABDD0), scr_print_ln);

			vm_execute_addr = SELECT_VALUE(0x610A90, 0x56B720);
			utils::hook(SELECT_VALUE(0x611EF1, 0x56CB81), vm_execute_stub, HOOK_JUMP).install()->quick();

			scripting::on_shutdown([](int free_scripts) -> void
			{
				if (free_scripts)
				{
					replaced_funcs.clear();
				}
			});

			add_gsc_functions();
		}

		static void add_gsc_functions()
		{
			register_function("replacefunc", []
			{
				if (scr_get_type(0) != game::native::VAR_FUNCTION || scr_get_type(1) != game::native::VAR_FUNCTION)
				{
					scr_error("ReplaceFunc requires two functions pointers");
				}

				replaced_funcs[get_code_pos(0)] = get_code_pos(1);
			});
		}
	};
}

REGISTER_MODULE(gsc::script_extension)

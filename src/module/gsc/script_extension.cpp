#include <std_include.hpp>
#include <loader/module_loader.hpp>
#include "game/game.hpp"

#include "module/console.hpp"

#include <utils/hook.hpp>

namespace gsc
{
	namespace
	{
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

	class script_extension final : public module
	{
	public:
		void post_load() override
		{
			utils::hook::set<game::native::BuiltinFunction>(SELECT_VALUE(0x92B8DC, 0x8ABDC4), scr_print);
			utils::hook::set<game::native::BuiltinFunction>(SELECT_VALUE(0x92B8E8, 0x8ABDD0), scr_print_ln);
		}
	};
}

REGISTER_MODULE(gsc::script_extension)

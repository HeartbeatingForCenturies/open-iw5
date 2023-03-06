#include <std_include.hpp>
#include <loader/module_loader.hpp>
#include "game/game.hpp"

#include "script_error.hpp"
#include "script_extension.hpp"

namespace gsc
{
	class string final : public module
	{
	public:
		void post_load() override
		{
			register_function("getchar", []
			{
				const auto* str = game::native::Scr_GetString(0);
				const auto index = scr_get_int(1);

				if (!str)
				{
					scr_error("^GetChar: Illegal parameter!");
					return;
				}

				if (static_cast<std::size_t>(index) >= std::strlen(str))
				{
					scr_error("GetChar: char index is out of bounds");
				}

				game::native::Scr_AddInt(str[index]);
			});
		}
	};
}

REGISTER_MODULE(gsc::string)

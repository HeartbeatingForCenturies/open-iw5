#include <std_include.hpp>
#include "game.hpp"
#include "dvars.hpp"

namespace dvars
{
	const game::native::dvar_t** com_sv_running;

	const game::native::dvar_t** sv_maxclients;

	const game::native::dvar_t** loc_language;

	void initialize()
	{
		com_sv_running = reinterpret_cast<const game::native::dvar_t**>(SELECT_VALUE(0x1769F50, 0x1CEF588));

		sv_maxclients = reinterpret_cast<const game::native::dvar_t**>(SELECT_VALUE(0x0, 0x21223C0));

		loc_language = reinterpret_cast<const game::native::dvar_t**>(SELECT_VALUE(0x1BF6938, 0x58D5A90));
	}
}

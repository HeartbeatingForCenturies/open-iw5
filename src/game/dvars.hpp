#pragma once

namespace dvars
{
	extern const game::native::dvar_t** com_sv_running;

	extern const game::native::dvar_t** sv_maxclients;

	extern const game::native::dvar_t** loc_language;

	void initialize();
}

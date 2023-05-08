#include <std_include.hpp>
#include <loader/module_loader.hpp>
#include "game/game.hpp"

#include "game_log.hpp"

#include <utils/hook.hpp>

namespace
{
	void notify_on_say(game::native::gentity_s* ent, int mode, const char* message)
	{
		game::native::Scr_AddString(message + 1); // First character has nothing to do with actual message
		game::native::Scr_AddInt(mode);
		game::native::Scr_AddEntityNum(ent - game::native::mp::g_entities, 0);

		game::native::Scr_NotifyLevel(game::native::SL_GetString("say", 0), 3);

		const auto* guid = game::native::mp::SV_GetGuid(ent - game::native::mp::g_entities);
		const auto* name = game::native::mp::svs_clients[ent - game::native::mp::g_entities].name;

		if (mode == 0)
		{
			game_log::g_log_printf("say;%s;%d;%s;%s\n", guid, ent - game::native::mp::g_entities, name, message);
		}
		else
		{
			game_log::g_log_printf("sayteam;%s;%d;%s;%s\n", guid, ent - game::native::mp::g_entities, name, message);
		}
	}

	__declspec(naked) void g_say_stub()
	{
		__asm
		{
			pushad

			push [esp + 0x20 + 0x108] // message
			push [esp + 0x20 + 0x108] // mode
			push ebp // ent
			call notify_on_say
			add esp, 0xC

			popad

			push 0x5C2940 // I_strncpyz
			retn
		}
	}
}

class chat final : public module
{
public:
	static_assert(offsetof(game::native::mp::client_t, name) == 0x2142C);

	void post_load() override
	{
		if (game::is_mp())
		{
			utils::hook(0x502BAF, &g_say_stub, HOOK_CALL).install()->quick(); // I_strncpyz
		}
	}
};

REGISTER_MODULE(chat)

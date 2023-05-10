#include <std_include.hpp>
#include <loader/module_loader.hpp>
#include "game/game.hpp"

#include "command.hpp"
#include "scheduler.hpp"

#include "gsc/script_error.hpp"

#include <utils/hook.hpp>
#include <utils/string.hpp>

namespace
{
	const game::native::dvar_t* g_cheats;

	bool cheats_ok(game::native::gentity_s* ent)
	{
		if (!g_cheats->current.enabled)
		{
			game::native::mp::SV_GameSendServerCommand(ent->s.number, game::native::SV_CMD_CAN_IGNORE,
				utils::string::va("%c \"GAME_CHEATSNOTENABLED\"", 0x65));
			return false;
		}

		if (ent->health < 1)
		{
			game::native::mp::SV_GameSendServerCommand(ent->s.number, game::native::SV_CMD_CAN_IGNORE,
				utils::string::va("%c \"GAME_MUSTBEALIVECOMMAND\"", 0x65));
			return false;
		}

		return true;
	}

	void cmd_noclip_f(game::native::gentity_s* ent, [[maybe_unused]] const command::params_sv& params)
	{
		if (!cheats_ok(ent))
			return;

		ent->client->flags ^= 1;

		game::native::mp::SV_GameSendServerCommand(ent->s.number, game::native::SV_CMD_CAN_IGNORE,
			utils::string::va("%c \"%s\"", 0x65, (ent->client->flags & 1) ? "GAME_NOCLIPON" : "GAME_NOCLIPOFF"));
	}

	void cmd_ufo_f(game::native::gentity_s* ent, [[maybe_unused]] const command::params_sv& params)
	{
		if (!cheats_ok(ent))
			return;

		ent->client->flags ^= 2;

		game::native::mp::SV_GameSendServerCommand(ent->s.number, game::native::SV_CMD_CAN_IGNORE,
			utils::string::va("%c \"%s\"", 0x65, (ent->client->flags & 2) ? "GAME_UFOON" : "GAME_UFOOFF"));
	}

	void player_cmd_noclip(game::native::scr_entref_t entref)
	{
		auto* ent = gsc::mp::get_player_entity(entref);
		cmd_noclip_f(ent, command::params_sv{});
	}

	void player_cmd_ufo(game::native::scr_entref_t entref)
	{
		auto* ent = gsc::mp::get_player_entity(entref);
		cmd_ufo_f(ent, command::params_sv{});
	}
}

class client_command final : public module
{
public:
	void post_load() override
	{
		if (game::is_mp())
		{
			g_cheats = game::native::Dvar_RegisterBool("sv_cheats", true, game::native::DVAR_CODINFO, "Enable cheats");
			add_mp_client_commands();

			utils::hook::set<game::native::BuiltinMethod>(0x7FDBC8, player_cmd_noclip);
			utils::hook::set<game::native::BuiltinMethod>(0x7FDBD4, player_cmd_ufo);
		}
	}

private:
	static void add_mp_client_commands()
	{
		command::add_sv("noclip", cmd_noclip_f);
		command::add_sv("ufo", cmd_ufo_f);

		command::add_sv("god", [](game::native::gentity_s* ent, [[maybe_unused]] const command::params_sv& params)
		{
			if (!cheats_ok(ent))
				return;

			ent->flags ^= game::native::FL_GODMODE;

			game::native::mp::SV_GameSendServerCommand(ent->s.number, game::native::SV_CMD_CAN_IGNORE,
				utils::string::va("%c \"%s\"", 0x65, (ent->flags & game::native::FL_GODMODE) ? "GAME_GODMODE_ON" : "GAME_GODMODE_OFF"));
		});

		command::add_sv("demigod", [](game::native::gentity_s* ent, [[maybe_unused]] const command::params_sv& params)
		{
			if (!cheats_ok(ent))
				return;

			ent->flags ^= game::native::FL_DEMI_GODMODE;

			game::native::mp::SV_GameSendServerCommand(ent->s.number, game::native::SV_CMD_CAN_IGNORE,
				utils::string::va("%c \"%s\"", 0x65, (ent->flags & game::native::FL_DEMI_GODMODE) ? "GAME_DEMI_GODMODE_ON" : "GAME_DEMI_GODMODE_OFF"));
		});

		command::add_sv("notarget", [](game::native::gentity_s* ent, [[maybe_unused]] const command::params_sv& params)
		{
			if (!cheats_ok(ent))
				return;

			ent->flags ^= game::native::FL_NOTARGET;

			game::native::mp::SV_GameSendServerCommand(ent->s.number, game::native::SV_CMD_CAN_IGNORE,
				utils::string::va("%c \"%s\"", 0x65, (ent->flags & game::native::FL_NOTARGET) ? "GAME_NOTARGETON" : "GAME_NOTARGETOFF"));
		});

		command::add_sv("setviewpos", [](game::native::gentity_s* ent, [[maybe_unused]] const command::params_sv& params)
		{
			if (!cheats_ok(ent))
				return;

			game::native::vec3_t origin, angles{0.f, 0.f, 0.f};

			if (params.size() < 4 || params.size() > 6)
			{
				game::native::mp::SV_GameSendServerCommand(ent->s.number, game::native::SV_CMD_CAN_IGNORE,
					utils::string::va("%c \"GAME_USAGE\x15: setviewpos x y z [yaw] [pitch]\"", 0x65));
				return;
			}

			for (auto i = 0; i < 3; i++)
			{
				origin[i] = std::strtof(params.get(i + 1), nullptr);
			}

			if (params.size() > 4)
			{
				angles[game::native::YAW] = std::strtof(params.get(4), nullptr); // Yaw
			}

			if (params.size() == 6)
			{
				angles[game::native::PITCH] = std::strtof(params.get(5), nullptr); // Pitch
			}

			game::native::TeleportPlayer(ent, origin, angles);
		});

		command::add_sv("kill", [](game::native::gentity_s* ent, [[maybe_unused]] const command::params_sv& params)
		{
			assert(ent->client->sess.connected != game::native::CON_DISCONNECTED);

			if (ent->client->sess.sessionState != game::native::SESS_STATE_PLAYING || !cheats_ok(ent))
				return;

			scheduler::once([ent]
			{
				ent->flags &= ~(game::native::FL_GODMODE | game::native::FL_DEMI_GODMODE);
				ent->health = 0;
				game::native::player_die(ent, ent, ent, 100000, 12, nullptr, false, nullptr, game::native::hitLocation_t::HITLOC_NONE, 0);
			}, scheduler::pipeline::server);
		});
	}
};

REGISTER_MODULE(client_command);

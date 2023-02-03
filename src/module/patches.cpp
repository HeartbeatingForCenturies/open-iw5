#include <std_include.hpp>
#include <loader/module_loader.hpp>
#include "game/game.hpp"

#include <utils/hook.hpp>

#include "console.hpp"

namespace
{
	__declspec(noreturn) void long_jump_stub(jmp_buf buf, const int value) noexcept(false)
	{
#ifdef _DEBUG
		{
			printf("Unwinding the stack...\n");
		}
#endif

		longjmp(buf, value);
	}

	const game::native::dvar_t* dvar_register_com_max_fps(const char* dvarName, int value,
		int min, int /*max*/, unsigned __int16 /*flags*/, const char* description)
	{
		return game::native::Dvar_RegisterInt(dvarName, value, min, 1000, game::native::DVAR_ARCHIVE, description);
	}

	const char* live_get_local_client_name_stub()
	{
		return game::native::Dvar_FindVar("name")->current.string;
	}

	void com_clamp_msec(const int msec)
	{
		if (msec > 500 && msec < 500000)
		{
			console::warn("Hitch warning: %i msec frame time\n", msec);
		}
	}

	__declspec(naked) void com_clamp_msec_stub()
	{
		using namespace game::native;

		__asm
		{
			pushad

			push esi
			call com_clamp_msec
			add esp, 0x4

			popad

			// Game's code
			cmp esi, eax
			jle label_5565DA

			mov esi, eax

			push 0x5565D6
			ret

		label_5565DA:
			push 0x5565DA
			ret
		}
	}
}

class patches final : public module
{
public:
	void post_load() override
	{
		this->patch_clients();

		if (game::is_sp()) this->patch_sp();
		else if (game::is_mp()) this->patch_mp();

		utils::hook(game::native::_longjmp, long_jump_stub, HOOK_JUMP).install()->quick();
	}

private:
	void patch_clients() const
	{
		// Remove improper quit check
		utils::hook::nop(SELECT_VALUE(0x53444A, 0x5CCDC0), 9);

		// Ignore sdm files
		utils::hook::nop(SELECT_VALUE(0x4438BA, 0x6371EA), 2);
	}

	void patch_sp() const
	{
		// SP doesn't initialize WSA
		WSADATA wsa_data;
		WSAStartup(MAKEWORD(2, 2), &wsa_data);

		// Disable remote storage
		utils::hook::set<std::uint8_t>(0x663B5A, 0xEB);
		utils::hook::set<std::uint8_t>(0x663C54, 0xEB);

		// Archive "name" dvar
		utils::hook::set<std::uint8_t>(0x4296F9, game::native::DVAR_ARCHIVE);

		utils::hook(0x44C640, &live_get_local_client_name_stub, HOOK_JUMP).install()->quick();

		// Some whitelist
		utils::hook::nop(0x605F3C, 2);
	}

	void patch_mp() const
	{
		// Note: on SP the max value is already 1000
		utils::hook(0x55411F, &dvar_register_com_max_fps, HOOK_CALL).install()->quick();

		// Archive "name" dvar
		utils::hook::set<std::uint32_t>(0x492C82, game::native::DVAR_USERINFO | game::native::DVAR_ARCHIVE);

		utils::hook(0x5C9980, &live_get_local_client_name_stub, HOOK_JUMP).install()->quick();

		// Add back warning
		utils::hook(0x5565D0, &com_clamp_msec_stub, HOOK_JUMP).install()->quick(); // Com_Frame_Try_Block_Function
		utils::hook::nop(0x5565D0 + 5, 1);

		// Unpure client detected
		utils::hook::set<std::uint8_t>(0x57228C, 0xEB);

		// Allow any IWD file to be loaded
		utils::hook::nop(0x5B090F, 6);
		utils::hook::nop(0x5B092C, 6);

		// Some whitelist
		utils::hook::nop(0x54641D, 2);
	}

	void patch_dedi() const
	{
		// Skip call to queryserverinfo handler in SV_ConnectionlessPacket
		utils::hook::nop(0x4FE051, 5);

		// Disable callvote/vote exploit
		utils::hook::nop(0x47EB9D, 5);
		utils::hook::nop(0x47EBC9, 5);
	}
};

REGISTER_MODULE(patches)

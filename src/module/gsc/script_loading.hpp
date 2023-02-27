#pragma once
#define XSK_GSC_IW5_PC
#include <gsc_api.hpp>

namespace gsc
{
	extern std::unique_ptr<xsk::gsc::iw5_pc::context> gsc_ctx;

	game::native::ScriptFile* find_script(game::native::XAssetType type, const char* name, int allow_create_default);
}

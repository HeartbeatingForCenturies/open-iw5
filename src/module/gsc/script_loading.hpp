#pragma once
#include <iw5/iw5_pc.hpp>

namespace gsc
{
	extern std::unique_ptr<xsk::gsc::iw5_pc::context> gsc_ctx;

	game::native::ScriptFile* find_script(game::native::XAssetType type, const char* name, int allow_create_default);
}

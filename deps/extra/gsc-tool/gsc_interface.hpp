#pragma once
#undef ERROR
#undef IN
#undef TRUE
#undef FALSE

#undef far

#include <stdinc.hpp>
#include <iw5/iw5_pc.hpp>

namespace gsc
{
	extern std::unique_ptr<xsk::gsc::iw5_pc::context> cxt;
}

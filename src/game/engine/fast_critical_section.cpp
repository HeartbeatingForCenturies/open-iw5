#include <std_include.hpp>
#include "game/game.hpp"

#include "fast_critical_section.hpp"

namespace game::engine
{
	fast_critical_section_scope_read::fast_critical_section_scope_read(native::FastCriticalSection* cs)
	{
		this->cs_ = cs;
		if (this->cs_)
		{
			native::Sys_LockRead(this->cs_);
		}
	}

	fast_critical_section_scope_read::~fast_critical_section_scope_read()
	{
		if (this->cs_)
		{
			native::Sys_UnlockRead(this->cs_);
		}
	}

	fast_critical_section_scope_write::fast_critical_section_scope_write(native::FastCriticalSection* cs)
	{
		this->cs_ = cs;
		if (this->cs_)
		{
			native::Sys_LockWrite(this->cs_);
		}
	}

	fast_critical_section_scope_write::~fast_critical_section_scope_write()
	{
		if (this->cs_)
		{
			native::Sys_UnlockWrite(this->cs_);
		}
	}
}

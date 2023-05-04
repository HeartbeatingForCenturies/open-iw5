#include <std_include.hpp>
#include "game/game.hpp"

#include "fast_critical_section.hpp"

namespace game::engine
{
	FastCriticalSectionScopeRead::FastCriticalSectionScopeRead(native::FastCriticalSection* cs)
	{
		this->cs_ = cs;
		if (this->cs_)
		{
			native::Sys_LockRead(this->cs_);
		}
	}

	FastCriticalSectionScopeRead::~FastCriticalSectionScopeRead()
	{
		if (this->cs_)
		{
			native::Sys_UnlockRead(this->cs_);
		}
	}

	FastCriticalSectionScopeWrite::FastCriticalSectionScopeWrite(native::FastCriticalSection* cs)
	{
		this->cs_ = cs;
		if (this->cs_)
		{
			native::Sys_LockWrite(this->cs_);
		}
	}

	FastCriticalSectionScopeWrite::~FastCriticalSectionScopeWrite()
	{
		if (this->cs_)
		{
			native::Sys_UnlockWrite(this->cs_);
		}
	}
}

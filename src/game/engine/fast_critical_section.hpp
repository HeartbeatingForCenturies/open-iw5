#pragma once

namespace game::engine
{
	class FastCriticalSectionScopeRead
	{
	public:
		FastCriticalSectionScopeRead(native::FastCriticalSection* cs);
		~FastCriticalSectionScopeRead();

	private:
		native::FastCriticalSection* cs_;
	};

	class FastCriticalSectionScopeWrite
	{
	public:
		FastCriticalSectionScopeWrite(native::FastCriticalSection* cs);
		~FastCriticalSectionScopeWrite();

	private:
		native::FastCriticalSection* cs_;
	};
}

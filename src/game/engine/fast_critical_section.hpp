#pragma once

namespace game::engine
{
	class fast_critical_section_scope_read
	{
	public:
		fast_critical_section_scope_read(native::FastCriticalSection* cs);
		~fast_critical_section_scope_read();

	private:
		native::FastCriticalSection* cs_;
	};

	class fast_critical_section_scope_write
	{
	public:
		fast_critical_section_scope_write(native::FastCriticalSection* cs);
		~fast_critical_section_scope_write();

	private:
		native::FastCriticalSection* cs_;
	};
}

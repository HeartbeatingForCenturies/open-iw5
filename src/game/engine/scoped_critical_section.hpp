#pragma once

namespace game::engine
{
	class scoped_critical_section
	{
	public:
		scoped_critical_section(native::CriticalSection s, native::ScopedCriticalSectionType type);
		~scoped_critical_section();

		void enter_crit_sect();
		void leave_crit_sect();
		bool try_enter_crit_sect();

		[[nodiscard]] bool has_ownership() const;
		[[nodiscard]] bool is_scoped_release() const;

	private:
		native::CriticalSection s_;
		bool has_ownership_;
		bool is_scoped_release_;
	};
}

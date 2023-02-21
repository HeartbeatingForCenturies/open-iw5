#pragma once

namespace gsc
{
	extern void* func_table[500];
	extern void* meth_table[900];

	extern std::uint16_t scr_func_max_id;

	void register_function(const std::string& name, const game::native::BuiltinFunction& func);
	void register_method(const std::string& name, const game::native::BuiltinMethod& meth);
}

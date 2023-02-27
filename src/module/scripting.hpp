#pragma once

namespace scripting
{
	extern std::unordered_map<std::string, std::unordered_map<std::string, const char*>> script_function_table;
	extern std::unordered_map<std::string, std::vector<std::pair<std::string, const char*>>> script_function_table_sort;
	extern std::unordered_map<const char*, std::pair<std::string, std::string>> script_function_table_rev;

	extern std::string current_file;

	std::string find_token(std::uint32_t id);
	std::string get_token(unsigned int id);

	void on_shutdown(const std::function<void(int)>& callback);
}

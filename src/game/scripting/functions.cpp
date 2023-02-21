#include <std_include.hpp>
#include "game/game.hpp"

#include "module/gsc/script_extension.hpp"

#include "functions.hpp"

#include <utils/string.hpp>

#include <gsc_interface.hpp>

namespace scripting
{
	int find_function_index(const std::string& name, [[maybe_unused]] const bool prefer_global)
	{
		const auto target = utils::string::to_lower(name);
		auto const& first = gsc::cxt->func_map();
		auto const& second = gsc::cxt->meth_map();

		if (const auto itr = first.find(name); itr != first.end())
		{
			return static_cast<int>(itr->second);
		}

		if (const auto itr = second.find(name); itr != second.end())
		{
			return static_cast<int>(itr->second);
		}

		return -1;
	}

	std::uint32_t parse_token_id(const std::string& name)
	{
		if (name.starts_with("_ID"))
		{
			return static_cast<std::uint32_t>(std::strtol(name.substr(3).data(), nullptr, 10));
		}

		return 0;
	}

	std::string find_token(std::uint32_t id)
	{
		return gsc::cxt->token_name(id);
	}

	std::string find_token_single(std::uint32_t id)
	{
		return gsc::cxt->token_name(id);
	}

	unsigned int find_token_id(const std::string& name)
	{
		const auto id = gsc::cxt->token_id(name);
		if (id)
		{
			return id;
		}

		const auto parsed_id = parse_token_id(name);
		if (parsed_id)
		{
			return parsed_id;
		}

		return game::native::SL_GetCanonicalString(name.data());
	}

	game::native::BuiltinFunction get_function_by_index(const std::uint32_t index)
	{
		auto** function_table = gsc::func_table;
		auto** method_table = gsc::meth_table;

		if (index < gsc::scr_func_max_id)
		{
			return reinterpret_cast<game::native::BuiltinFunction*>(function_table)[index - 1];
		}

		return reinterpret_cast<game::native::BuiltinFunction*>(method_table)[index];
	}

	game::native::BuiltinFunction find_function(const std::string& name, const bool prefer_global)
	{
		const auto index = find_function_index(name, prefer_global);
		if (index < 0) return nullptr;

		return get_function_by_index(index);
	}
}

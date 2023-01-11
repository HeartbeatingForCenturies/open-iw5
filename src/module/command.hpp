#pragma once

class command final : public module
{
public:
	class params
	{
	public:
		params();

		int size() const;
		const char* get(int index) const;
		std::string join(int index) const;

		const char* operator[](const int index) const
		{
			return this->get(index);
		}

	private:
		int nesting_;
	};

	class params_sv
	{
	public:
		params_sv();

		int size() const;
		const char* get(int index) const;
		std::string join(int index) const;

		const char* operator[](const int index) const
		{
			return this->get(index);
		}

	private:
		int nesting_;
	};

	static void add(const char* name, const std::function<void(const params&)>& callback);
	static void add(const char* name, const std::function<void()>& callback);

	static void add_sv(const char* name, std::function<void(game::native::gentity_s*, const params_sv&)> callback);
	static void add_sp_sv(const char* name, std::function<void(game::native::sp::gentity_s*, const params_sv&)> callback);

	static void execute(std::string command, bool sync = false);

	void post_load() override;

private:
	static std::unordered_map<std::string, std::function<void(const params&)>> handlers;
	static std::unordered_map<std::string, std::function<void(game::native::gentity_s*, const params_sv&)>> handlers_sv;
	static std::unordered_map<std::string, std::function<void(game::native::sp::gentity_s*, const params_sv&)>> handlers_sp_sv;

	static void main_handler();

	static void client_command_stub(int client_num);
	static void client_command_sp(int client_num, const char* s);
	static void client_command_sp_stub();

	static void add_raw(const char* name, void (*callback)());

	static void add_sp_commands();
};

#define Cmd_AddCommand(cmd_name, function) \
{ \
	static game::native::cmd_function_s function##_VAR; \
	game::native::Cmd_AddCommandInternal(cmd_name, function, &function##_VAR); \
}

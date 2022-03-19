#pragma once

enum class Status
{
	none = 0,
	login_screen = 1,
	info_prompt = 2,
	connecting = 3,
	splash_screen = 4,
	logged_in = 5
};

namespace player
{
	void login(const char* username, const char* password, int worldIndex);
	Status getStatus();
}
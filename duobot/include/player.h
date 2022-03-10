enum class Status
{
	none,
	login_screen,
	info_prompt,
	connecting,
	splash_screen,
	logged_in
};

namespace player
{
	Status getStatus();
}
#pragma once

#include <Windows.h>
#include <string>

namespace screen
{
	void click(POINT p);
	void sendText(std::string text);
	void sendKey(int keyCode);
	POINT getFixedCenter();
	POINT getMinimapCenter();
}
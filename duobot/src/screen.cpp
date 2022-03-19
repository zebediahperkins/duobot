#include <screen.h>
#include <oswin.h>

namespace screen
{
	void click(POINT p)
	{
		RECT position;
		GetWindowRect(oswin::hProc, &position);
		int lparam = MAKELPARAM(p.x + position.left, p.y + position.top);
		PostMessage(oswin::hProc, WM_MOUSEMOVE, 0, lparam);
		Sleep(50);
		PostMessage(oswin::hProc, WM_LBUTTONDOWN, 0, lparam);
		Sleep(100);
		PostMessage(oswin::hProc, WM_LBUTTONUP, 0, lparam);
	}

	void sendText(std::string text)
	{
		for (int i = 0; i < text.size(); ++i)
		{
			PostMessage(oswin::hProc, WM_CHAR, text[i], 0);
			Sleep(50);
		}
	}

	void sendKey(int keyCode)
	{
		PostMessage(oswin::hProc, WM_KEYDOWN, keyCode, 0);
	}

	POINT getFixedCenter()
	{
		POINT p;
		p.x = 382;
		p.y = 251;
		return p;
	}

	POINT getMinimapCenter()
	{
		POINT p;
		p.x = 642;
		p.y = 86;
		return p;
	}
}
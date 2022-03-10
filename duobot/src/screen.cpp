#include <screen.h>
#include <oswin.h>

namespace screen
{
	void click(int x, int y) //TODO: Experiment with sleeps and/or mouse move
	{
		RECT position;
		GetWindowRect(oswin::hProc, &position);
		int lparam = MAKELPARAM(x + position.left, y + position.top);
		PostMessage(oswin::hProc, WM_LBUTTONDOWN, 0, lparam);
		PostMessage(oswin::hProc, WM_LBUTTONUP, 0, lparam);
	}

	POINT getFixedCenter()
	{
		POINT p;
		p.x = 382;
		p.y = 251;
		return p;
	}
}
#include <screen.h>
#include <image.h>
#include <oswin.h>

namespace walking
{
	bool isWalking()
	{
		POINT tl, br;
		tl.x = 590;
		tl.y = 20;
		br.x = 715;
		br.y = 125;
		cv::Mat map1 = image::captureWnd(oswin::hProc, tl, br);
		Sleep(200);
		cv::Mat map2 = image::captureWnd(oswin::hProc, tl, br);
		float cmp = image::imgCmp(map1, map2);
		return cmp < 0.975f;
	}

	void walkTo(int x, int y) //TODO: Implement this. Walk to actual tile
	{
		;
	}

	void walkToRelative(int x, int y)
	{
		POINT p = screen::getMinimapCenter();
		p.x += 4 * x;
		p.y -= 4 * y;
		screen::click(p);
		if (oswin::waitFor(isWalking, 1500)) //TODO: Maybe remove waitFor here and let the script implement it as needed?
		{
			oswin::waitFor([]() -> bool {
				return !isWalking();
			}, 10000);
		}
	}
}
#include <inventory.h>
#include <image.h>
#include <oswin.h>

namespace inventory
{
	bool isSpotEmpty(int x, int y)
	{
		int xOffset = x * 42, yOffset = y * 36;
		POINT tl, br;
		tl.x = 564 + xOffset;
		tl.y = 214 + yOffset;
		br.x = 595 + xOffset;
		br.y = 245 + yOffset;
		cv::Mat img1 = cv::imread(oswin::imgPth + "/control_panel/inventory/slots/invSlt" + std::to_string(x) + "-" + std::to_string(y) + ".png", cv::IMREAD_GRAYSCALE);
		cv::Mat img2 = image::captureWnd(oswin::hProc, tl, br);
		return image::imgCmp(img1, img2) >= 0.975f;
	}

	bool isEmpty()
	{
		for (int x = 0; x < 4; ++x)
			for (int y = 0; y < 7; ++y)
				if (!inventory::isSpotEmpty(x, y)) return false;
		return true;
	}
}
#include <screen.h>
#include <oswin.h>
#include <image.h>
#include <opencv2/opencv.hpp>

namespace screen
{
	Point::Point(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void Point::click()
	{
		RECT position;
		GetWindowRect(oswin::hProc, &position);
		int lparam = MAKELPARAM(x + position.left, y + position.top);
		PostMessage(oswin::hProc, WM_LBUTTONDOWN, 0, lparam);
		PostMessage(oswin::hProc, WM_LBUTTONUP, 0, lparam);
	}

	Widget::Widget(Point* tl, Point* br, const char* imgPth)
	{
		this->tl = tl;
		this->br = br;
		this->imgPth = imgPth;
	}

	bool Widget::isVisible(float minCertainty)
	{
		cv::Mat img1 = cv::imread(imgPth, cv::IMREAD_GRAYSCALE);
		cv::Mat img2 = image::captureWnd(oswin::hProc, *tl, *br);
		return image::imgCmp(img1, img2) >= minCertainty;
	}

	void Widget::captureWdgt(std::string name)
	{
		cv::Mat img = image::captureWnd(oswin::hProc, *tl, *br);
		cv::imwrite(name + ".png", img);
	}

	void Widget::click()
	{
		tl->click(); //TODO: Make this click a random (pseudo-random?) point between tl and br
	}

	Point getFixedCenter()
	{
		RECT position;
		GetWindowRect(oswin::hProc, &position);
		int horiz = position.right - position.left;
		return Point(384, 256);
	}
}
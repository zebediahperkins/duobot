#pragma once

#include <Windows.h>
#include <string>

namespace screen
{
	class Point //TODO: Maybe use POINT struct from windows api instead?
	{
	public:
		int x, y;
		Point(int x, int y);
		void click();
	};

	class Widget
	{
	public:
		Point* tl;
		Point* br;
		const char* imgPth;
		Widget(Point* tl, Point* br, const char* imgPth);
		bool isVisible(float minCertainty = 0.95f);
		void captureWdgt(std::string name);
		void click();
	};

	Point getFixedCenter();
}
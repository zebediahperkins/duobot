#include <image.h>

namespace image
{
	float imgCmp(cv::Mat img1, cv::Mat img2)
	{
		int width = img1.rows < img2.rows ? img1.rows : img2.rows;
		int height = img1.cols < img2.cols ? img1.cols : img2.cols;
		float tot = 0.0f;
		int len = 0;
		for (int x = 0; x < width; ++x)
		{
			for (int y = 0; y < height; ++y, ++len)
			{
				uchar p1 = img1.at<uchar>(x, y);
				uchar p2 = img2.at<uchar>(x, y);
				int gv, lv;
				if (p1 > p2)
				{
					gv = p1;
					lv = p2;
				}
				else
				{
					gv = p2;
					lv = p1;
				}
				if (gv == 0) break;
				tot += ((float)lv / (float)gv);
			}
		}
		return tot / len;
	}

	void showImg(const char* wnd, cv::Mat img)
	{
		cv::namedWindow(wnd);
		cv::imshow(wnd, img);
		cv::waitKey(0);
		cv::destroyWindow(wnd);
	}

	cv::Mat captureWnd(HWND hwnd, POINT tl, POINT br)
	{
		HDC hwindowDC, hwindowCompatibleDC;
		int height, width, srcheight, srcwidth;
		HBITMAP hbwindow;
		cv::Mat src, crop, cropG;
		cv::Rect roi;
		BITMAPINFOHEADER bi;
		RECT windowsize;
		hwindowDC = GetDC(hwnd);
		hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
		SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);
		GetClientRect(hwnd, &windowsize);
		srcheight = windowsize.bottom;
		srcwidth = windowsize.right;
		height = windowsize.bottom;
		width = windowsize.right;
		src.create(height, width, CV_8UC4);
		hbwindow = CreateCompatibleBitmap(hwindowDC, width, height);
		bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = width;
		bi.biHeight = -height;
		bi.biPlanes = 1;
		bi.biBitCount = 32;
		bi.biCompression = BI_RGB;
		bi.biSizeImage = 0;
		bi.biXPelsPerMeter = 0;
		bi.biYPelsPerMeter = 0;
		bi.biClrUsed = 0;
		bi.biClrImportant = 0;
		SelectObject(hwindowCompatibleDC, hbwindow);
		StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, 0, 0, srcwidth, srcheight, SRCCOPY);
		GetDIBits(hwindowCompatibleDC, hbwindow, 0, height, src.data, (BITMAPINFO *)&bi, DIB_RGB_COLORS);
		DeleteObject(hbwindow); DeleteDC(hwindowCompatibleDC); ReleaseDC(hwnd, hwindowDC);
		roi.x = tl.x;
		roi.y = tl.y;
		roi.width = br.x - tl.x;
		roi.height = br.y - tl.y;
		crop = src(roi);
		cv::cvtColor(crop, cropG, cv::COLOR_BGR2GRAY);
		return cropG;
	}
}
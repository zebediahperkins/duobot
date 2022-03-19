#pragma once

#include <Windows.h>
#include <opencv2/opencv.hpp>

namespace image
{
	// Compares two images and returns a percentage representing equality
	// @param img1 Grayscale image
	// @param img2 Grayscale image
	// @returns Value such that 0 <= value <= 1
	float imgCmp(cv::Mat img1, cv::Mat img2);

	// Displays an image in a window
	// @param wnd Name of the window
	// @param img Image being displayed
	void showImg(const char* wnd, cv::Mat img);

	// Captures a window and crops
	// @param tl The top left point of the crop
	// @param br The bottom right point of the crop
	// @returns Cropped window capture as grayscale
	cv::Mat captureWnd(HWND hwnd, POINT tl, POINT br);
}
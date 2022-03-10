#include <widget.h>
#include <image.h>
#include <oswin.h>
#include <screen.h>
#include <json/json.h>
#include <fstream>
#include <opencv2/opencv.hpp>

namespace widget
{
	Widget::Widget(POINT tl, POINT br, std::string imgPth)
	{
		this->tl = tl;
		this->br = br;
		this->imgPth = imgPth;
	}

	bool Widget::isVisible(float minCertainty)
	{
		cv::Mat img1 = cv::imread(imgPth, cv::IMREAD_GRAYSCALE);
		cv::Mat img2 = image::captureWnd(oswin::hProc, tl, br);
		return image::imgCmp(img1, img2) >= minCertainty;
	}

	void Widget::captureWdgt()
	{
		cv::Mat img = image::captureWnd(oswin::hProc, tl, br);
		cv::imwrite(imgPth, img);
	}

	void Widget::showWdgt()
	{
		image::showImg("win", image::captureWnd(oswin::hProc, tl, br));
	}

	void Widget::click()
	{
		screen::click(tl.x, tl.y); //TODO: Make this click a random (pseudo-random?) point between tl and br
	}

	std::ostream& operator<<(std::ostream& os, const Widget &wdgt)
	{
		return os << "{ tl: { x: " << wdgt.tl.x << ", y: " << wdgt.tl.y << " }, br: { x: " << wdgt.br.x << ", y: " << wdgt.br.y << " }, imgPth: \"" << wdgt.imgPth << "\" }";
	}

	std::vector<Widget> widgets;

	void populate()
	{
		std::string cur;
		std::ifstream jFile(oswin::jsonPth + "\\widgets.json");
		while (std::getline(jFile, cur))
		{
			POINT tl, br;
			std::string imgPth;
			nlohmann::json wdgt = nlohmann::json::parse(cur);
			tl.x = wdgt["tl"]["x"];
			tl.y = wdgt["tl"]["y"];
			br.x = wdgt["br"]["x"];
			br.y = wdgt["br"]["y"];
			imgPth = oswin::imgPth + (std::string)wdgt["imgPth"];
			widgets.push_back(Widget(tl, br, imgPth));
		}
		jFile.close();
	}
}
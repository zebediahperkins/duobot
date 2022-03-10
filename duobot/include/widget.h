#include <Windows.h>
#include <string>
#include <vector>

#define LGNPRMPTBTN 0
#define NEWUSRBTN 1
#define LGNCNCLBTN 2
#define LGNBTN 3
#define CNCTNGTXT 4
#define WRLDSLCTBTN 5
#define WRLDCNCLBTN 6
#define WRLDCHSBTN 7
#define PLAYBTN 8
#define COMBATINACTIVE 9
#define COMBATACTIVE 10
#define SKILLSINACTIVE 11
#define SKILLSACTIVE 12
#define QUESTSINACTIVE 13
#define QUESTSACTIVE 14
#define INVENTORYINACTIVE 15
#define INVENTORYACTIVE 16
#define EQUIPMENTINACTIVE 17
#define EQUIPMENTACTIVE 18
#define PRAYERINACTIVE 19
#define PRAYERACTIVE 20
#define MAGICINACTIVE 21
#define MAGICACTIVE 22
#define GROUPINGINACTIVE 23
#define GROUPINGACTIVE 24
#define FRIENDSINACTIVE 25
#define FRIENDSACTIVE 26
#define ACCOUNTINACTIVE 27
#define ACCOUNTACTIVE 28
#define LOGOUTINACTIVE 29
#define LOGOUTACTIVE 30
#define SETTINGSINACTIVE 31
#define SETTINGSACTIVE 32
#define EMOTESINACTIVE 33
#define EMOTESACTIVE 34
#define MUSICINACTIVE 35
#define MUSICACTIVE 36

namespace widget
{
	class Widget
	{
	public:
		POINT tl;
		POINT br;
		std::string imgPth;
		Widget(POINT tl, POINT br, std::string imgPth);
		bool isVisible(float minCertainty = 0.95f);
		void captureWdgt();
		void showWdgt();
		void click();
		friend std::ostream& operator<<(std::ostream& os, const Widget &wdgt);
	};

	extern std::vector<Widget> widgets;
	void populate();
}
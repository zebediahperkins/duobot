#include <player.h>
#include <widget.h>
#include <screen.h>

namespace player
{
	void selectWorldMenu(int worldIndex)
	{
		Sleep(500);
		widget::widgets[WRLDSLCTBTN].click();
		Sleep(500);
		widget::widgets[WRLDCHSBTN].click();
		Sleep(500);
	}

	void login(const char* username, const char* password, int worldIndex)
	{
		while (getStatus() == Status::none);
		selectWorldMenu(worldIndex);
		while (getStatus() != Status::logged_in)
		{
			switch (getStatus())
			{
				case Status::login_screen:
					widget::widgets[LGNPRMPTBTN].click();
					break;
				case Status::info_prompt:
					screen::sendText(username);
					Sleep(100);
					screen::sendKey(VK_TAB);
					Sleep(100);
					screen::sendText(password);
					Sleep(100);
					widget::widgets[LGNBTN].click();
					break;
				case Status::splash_screen:
					widget::widgets[PLAYBTN].click();
					break;
				default:
					break;
			}
			Sleep(1500);
		}
	}

	Status getStatus()
	{
		if
		(
			(widget::widgets[COMBATINACTIVE].isVisible() || widget::widgets[COMBATACTIVE].isVisible()) &&
			(widget::widgets[SKILLSINACTIVE].isVisible() || widget::widgets[SKILLSACTIVE].isVisible()) &&
			(widget::widgets[QUESTSINACTIVE].isVisible() || widget::widgets[QUESTSACTIVE].isVisible()) &&
			(widget::widgets[INVENTORYINACTIVE].isVisible() || widget::widgets[INVENTORYACTIVE].isVisible()) &&
			(widget::widgets[EQUIPMENTINACTIVE].isVisible() || widget::widgets[EQUIPMENTACTIVE].isVisible()) &&
			(widget::widgets[PRAYERINACTIVE].isVisible() || widget::widgets[PRAYERACTIVE].isVisible()) &&
			(widget::widgets[MAGICINACTIVE].isVisible() || widget::widgets[MAGICACTIVE].isVisible()) &&
			(widget::widgets[GROUPINGINACTIVE].isVisible() || widget::widgets[GROUPINGACTIVE].isVisible()) &&
			(widget::widgets[FRIENDSINACTIVE].isVisible() || widget::widgets[FRIENDSACTIVE].isVisible()) &&
			(widget::widgets[ACCOUNTINACTIVE].isVisible() || widget::widgets[ACCOUNTACTIVE].isVisible()) &&
			(widget::widgets[LOGOUTINACTIVE].isVisible() || widget::widgets[LOGOUTACTIVE].isVisible()) &&
			(widget::widgets[SETTINGSINACTIVE].isVisible() || widget::widgets[SETTINGSACTIVE].isVisible()) &&
			(widget::widgets[EMOTESINACTIVE].isVisible() || widget::widgets[EMOTESACTIVE].isVisible()) &&
			(widget::widgets[MUSICINACTIVE].isVisible() || widget::widgets[MUSICACTIVE].isVisible())
		)
			return Status::logged_in;
		if (widget::widgets[LGNPRMPTBTN].isVisible() && widget::widgets[NEWUSRBTN].isVisible())
			return Status::login_screen;
		if (widget::widgets[LGNCNCLBTN].isVisible() && widget::widgets[LGNBTN].isVisible())
			return Status::info_prompt;
		if (widget::widgets[CNCTNGTXT].isVisible())
			return Status::connecting;
		if (widget::widgets[PLAYBTN].isVisible())
			return Status::splash_screen;
		return Status::none;
	}
}
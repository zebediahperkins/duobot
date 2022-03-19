#include <oswin.h>
#include <widget.h>

#include <processenv.h>
#include <iostream>
#include <chrono>

namespace oswin
{
	HWND osHandle;
	HWND hProc;
	std::string imgPth, jsonPth;

	PROCESS_INFORMATION startOSClient()
	{
#ifdef _DEBUG
		char pwd[128];
		GetCurrentDirectoryA(128, pwd);
		imgPth = std::string(pwd) + "\\x64\\Release\\Build\\ref\\images";
		jsonPth = std::string(pwd) + "\\x64\\Release\\Build\\ref\\json";
#else
		imgPth = "\\ref\\images";
		jsonPth = "\\ref\\json";
#endif
		widget::populate();
		char buf[128];
		GetEnvironmentVariableA("USERPROFILE", buf, 128);
		std::string userProfile(buf);
		std::string args = userProfile + "\\jagexcache\\jagexlauncher\\bin\\JagexLauncher.exe oldschool";
		STARTUPINFOA si = { sizeof(STARTUPINFO) };
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_HIDE;
		PROCESS_INFORMATION pi;
		CreateProcessA(NULL, (LPSTR)args.c_str(), NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi);
		return pi;
	}

	BOOL CALLBACK childProc(HWND hwnd, LPARAM lparam)
	{
		if ((*(LPARAM*)lparam) == 2)
		{
			RECT position;
			GetWindowRect(hwnd, &position);
			int horiz = position.right - position.left;
			int vert = position.bottom - position.top;
			if (horiz == 765 && vert == 503)
			{
				hProc = hwnd;
				return false;
			}
			std::cout << "Error: Client is not in fixed mode." << std::endl;
			hProc = 0;
		}
		++(*(LPARAM*)lparam);
		return true;
	}

	bool foundPID = false;

	BOOL CALLBACK winProc(HWND hwnd, LPARAM lparam)
	{
		DWORD outID;
		GetWindowThreadProcessId(hwnd, &outID);
		if (foundPID)
		{
			osHandle = hwnd;
			return false;
		}
		if (outID == lparam) foundPID = true;
		return true;
	}

	HWND updateHandle(int pid)
	{
		if (!pid) return 0;
		foundPID = false;
		EnumWindows(winProc, pid);
		if (osHandle)
		{
			LPARAM lparam = 0;
			EnumChildWindows(osHandle, childProc, (LPARAM)&lparam);
		}
		return hProc;
	}

	bool isProcActive(HANDLE pid)
	{
		DWORD status;
		GetExitCodeProcess(pid, &status);
		return status == STILL_ACTIVE;
	}

	bool waitFor(bool (*predicate)(), int timeoutMS, int intervalMS)
	{
		auto startTime = std::chrono::steady_clock::now();
		while (!predicate())
		{
			Sleep(intervalMS);
			auto endTime = std::chrono::steady_clock::now();
			auto timeSinceStart = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
			if (timeSinceStart >= timeoutMS) return false;
		}
		return true;
	}
}
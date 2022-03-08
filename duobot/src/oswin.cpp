#include <oswin.h>
#include <processenv.h>
#include <string>

namespace oswin
{
	HWND osHandle;
	HWND hProc;

	PROCESS_INFORMATION startOSClient()
	{
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
			hProc = hwnd;
			return false;
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

	HWND initHandle(int pid)
	{
		foundPID = false;
		EnumWindows(winProc, pid);
		if (osHandle)
		{
			LPARAM lparam = 0;
			EnumChildWindows(osHandle, childProc, (LPARAM)&lparam);
		}
		return hProc;
	}
}
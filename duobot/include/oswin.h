#pragma once

#include <Windows.h>
#include <string>

namespace oswin
{
	extern HWND hProc;
	extern std::string imgPth, jsonPth;
	PROCESS_INFORMATION startOSClient();
	BOOL CALLBACK childProc(HWND hwnd, LPARAM lparam);
	BOOL CALLBACK winProc(HWND hwnd, LPARAM lparam);
	HWND updateHandle(int pid);
	bool isProcActive(HANDLE pid);
}
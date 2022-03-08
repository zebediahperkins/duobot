#pragma once

#include <Windows.h>

namespace oswin
{
	extern HWND hProc;
	PROCESS_INFORMATION startOSClient();
	BOOL CALLBACK childProc(HWND hwnd, LPARAM lparam);
	BOOL CALLBACK winProc(HWND hwnd, LPARAM lparam);
	HWND initHandle(int pid);
}
#include <Windows.h>
#include <locale>
#include <string>
#include "Console.h"
#include <iostream>

namespace Utils
{
	void hideConsoleCursor()
	{
		void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO structCursorInfo;
		GetConsoleCursorInfo(handle, &structCursorInfo);
		structCursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(handle, &structCursorInfo);
		ShowCursor(FALSE);
	}

	void setCorrectEncoding()
	{
		setlocale(LC_ALL, "rus");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
	}
}

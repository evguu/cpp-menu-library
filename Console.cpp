#include <Windows.h>
#include <locale>
#include <iostream>
#include "Console.h"


Console::Mode Console::standardMode{ 40, 128 };
std::string Console::goodbyeMessage = "Выход из программы...";


void Console::setMode(Mode mode)
{
	system(("MODE CON: COLS=" + std::to_string(mode.getColumns()) + " LINES=" + std::to_string(mode.getRows() + 1)).c_str());
	system("cls");
}

void Console::hideCursor()
{
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
	ShowCursor(FALSE);
}

void Console::fixEncoding()
{
	setlocale(LC_ALL, "rus");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
}

void Console::sayGoodbye()
{
	system("cls");
	std::cout << goodbyeMessage << std::endl;
}

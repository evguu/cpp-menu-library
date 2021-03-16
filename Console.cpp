#include <Windows.h>
#include <locale>
#include <string>
#include "Console.h"
#include <iostream>

const int COLUMNS = 128;
const int LINES = 40;

namespace Utils
{
	void setupResolution()
	{
		system(("MODE CON: COLS=" + to_string(COLUMNS) + " LINES=" + to_string(LINES + 1)).c_str());
		void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO structCursorInfo;
		GetConsoleCursorInfo(handle, &structCursorInfo);
		structCursorInfo.bVisible = FALSE;
		SetConsoleCursorInfo(handle, &structCursorInfo);
		ShowCursor(FALSE);
	}

	void setupEncoding()
	{
		setlocale(LC_ALL, "rus");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
	}

	void noBlinkOutput(string src)
	{
		char res[LINES][COLUMNS];
		int line = 0;
		int pos = 0;
		for (auto i : src)
		{
			if (i == '\n')
			{
				while (pos != COLUMNS - 1)
				{
					res[line][pos++] = ' ';
				}
				res[line][pos++] = '\n';
				++line;
				pos = 0;
			}
			else
			{
				res[line][pos++] = i;
				if (pos == COLUMNS - 1)
				{
					res[line][pos++] = '\n';
					++line;
					pos = 0;
				}
			}
		}
		while (line < LINES)
		{
			while (pos != COLUMNS - 1)
			{
				res[line][pos++] = ' ';
			}
			res[line][pos++] = '\n';
			++line;
			pos = 0;
		}
		res[LINES - 1][COLUMNS - 1] = 0;
		cout << (char *)res;
	};
}

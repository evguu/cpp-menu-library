#include "Display.h"
#include <iostream>

Display::Mode Display::modeMenu{ 40, 128 }, Display::modeDialog{ 200, 128 };

void Display::setMode(Mode mode)
{
	system(("MODE CON: COLS=" + std::to_string(mode.getColumns()) + " LINES=" + std::to_string(mode.getRows() + 1)).c_str());
	system("cls");
}

void Display::printStringWithoutBlinking(std::string src)
{
	char* res = new char[modeMenu.getRows()*modeMenu.getColumns()];
	int line = 0;
	int pos = 0;
	for (auto i : src)
	{
		if (i == '\n')
		{
			while (pos != modeMenu.getColumns() - 1)
			{
				res[line*modeMenu.getColumns() + pos++] = ' ';
			}
			res[line*modeMenu.getColumns() + pos++] = '\n';
			++line;
			pos = 0;
		}
		else
		{
			res[line*modeMenu.getColumns() + pos++] = i;
			if (pos == modeMenu.getColumns() - 1)
			{
				res[line*modeMenu.getColumns() + pos++] = '\n';
				++line;
				pos = 0;
			}
		}
	}
	while (line < modeMenu.getRows())
	{
		while (pos != modeMenu.getColumns() - 1)
		{
			res[line*modeMenu.getColumns() + pos++] = ' ';
		}
		res[line*modeMenu.getColumns() + pos++] = '\n';
		++line;
		pos = 0;
	}
	res[(modeMenu.getRows() - 1) * modeMenu.getColumns() + modeMenu.getColumns() - 1] = 0;
	std::cout << (char *)res;
};

#include "Display.h"
#include <iostream>

Display::Mode Display::standardMode{ 40, 128 };

void Display::setMode(Mode mode)
{
	system(("MODE CON: COLS=" + std::to_string(mode.getColumns()) + " LINES=" + std::to_string(mode.getRows() + 1)).c_str());
	system("cls");
}

void Display::printStringWithoutBlinking(std::string src)
{
	char* res = new char[standardMode.getRows()*standardMode.getColumns()];
	int line = 0;
	int pos = 0;
	for (auto i : src)
	{
		if (i == '\n')
		{
			while (pos != standardMode.getColumns() - 1)
			{
				res[line*standardMode.getColumns() + pos++] = ' ';
			}
			res[line*standardMode.getColumns() + pos++] = '\n';
			++line;
			pos = 0;
		}
		else
		{
			res[line*standardMode.getColumns() + pos++] = i;
			if (pos == standardMode.getColumns() - 1)
			{
				res[line*standardMode.getColumns() + pos++] = '\n';
				++line;
				pos = 0;
			}
		}
	}
	while (line < standardMode.getRows())
	{
		while (pos != standardMode.getColumns() - 1)
		{
			res[line*standardMode.getColumns() + pos++] = ' ';
		}
		res[line*standardMode.getColumns() + pos++] = '\n';
		++line;
		pos = 0;
	}
	res[(standardMode.getRows() - 1) * standardMode.getColumns() + standardMode.getColumns() - 1] = 0;
	std::cout << (char *)res;
};

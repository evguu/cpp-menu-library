#include "Display.h"
#include <iostream>

void Display::printStringWithoutBlinking(std::string src)
{
	int rows = Console::standardMode.getRows();
	int columns = Console::standardMode.getColumns();
	char* res = new char[rows*columns];
	int activeRow = 0;
	int activeColumn = 0;
	for (auto i : src)
	{
		if (i == '\n')
		{
			while (activeColumn != columns - 1)
			{
				res[activeRow*columns + activeColumn++] = ' ';
			}
			res[activeRow*columns + activeColumn++] = '\n';
			++activeRow;
			activeColumn = 0;
		}
		else
		{
			res[activeRow*columns + activeColumn++] = i;
			if (activeColumn == columns - 1)
			{
				res[activeRow*columns + activeColumn++] = '\n';
				++activeRow;
				activeColumn = 0;
			}
		}
	}
	while (activeRow < rows)
	{
		while (activeColumn != columns - 1)
		{
			res[activeRow*columns + activeColumn++] = ' ';
		}
		res[activeRow*columns + activeColumn++] = '\n';
		++activeRow;
		activeColumn = 0;
	}
	res[rows * columns - 1] = 0;
	std::cout << (char *)res;
};

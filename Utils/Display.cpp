#include "Display.h"
#include <iostream>

char* Display::buffer = new char[Console::standardMode.getColumns()*Console::standardMode.getRows()];

void Display::printStringWithoutBlinking(std::string src)
{
	int rows = Console::standardMode.getRows();
	int columns = Console::standardMode.getColumns();

	int activeRow = 0;
	int activeColumn = 0;
	for (auto i : src)
	{
		if (i == '\n')
		{
			while (activeColumn != columns - 1)
			{
				buffer[activeRow*columns + activeColumn++] = ' ';
			}
			buffer[activeRow*columns + activeColumn++] = '\n';
			++activeRow;
			activeColumn = 0;
		}
		else
		{
			buffer[activeRow*columns + activeColumn++] = i;
			if (activeColumn == columns - 1)
			{
				buffer[activeRow*columns + activeColumn++] = '\n';
				++activeRow;
				activeColumn = 0;
			}
		}
	}
	while (activeRow < rows)
	{
		while (activeColumn != columns - 1)
		{
			buffer[activeRow*columns + activeColumn++] = ' ';
		}
		buffer[activeRow*columns + activeColumn++] = '\n';
		++activeRow;
		activeColumn = 0;
	}
	buffer[rows * columns - 1] = 0;
	std::cout << (char *)buffer;
}

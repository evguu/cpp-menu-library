#pragma once
#include <string>

class Display
{
public:

	static class Mode
	{
	public:
		Mode(int rows, int columns) : rows(rows), columns(columns) {};
		int getRows() const { return rows; }
		int getColumns() const { return columns; }
	private:
		int rows;
		int columns;
	} standardMode;

	static void setMode(Mode mode);
	static void printStringWithoutBlinking(std::string src);
private:
	Display() = delete;
};

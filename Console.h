#pragma once
#include <string>

class Console
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
	static void hideCursor();
	static void fixEncoding();
	static void sayGoodbye();
private:
	Console() = delete;
	static std::string goodbyeMessage;
};

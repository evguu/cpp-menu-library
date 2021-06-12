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
	} modeMenu, modeDialog;

	static void setMode(Mode mode);
	static void printStringWithoutBlinking(std::string src);

	static void startDialog() { Display::setMode(Display::modeDialog); }
	static void endDialog() { system("pause"); Display::setMode(Display::modeMenu); }
	static auto dialog(void(*wrapped)()) { return [wrapped]() { startDialog(); wrapped(); endDialog(); }; };
private:
	Display() = delete;
};

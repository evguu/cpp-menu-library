#include <Windows.h>
#include <mutex>
#include "Console.h"
#include "MenuManager.h"

stack<Menu *> MenuManager::menuStack = stack<Menu *>();
bool MenuManager::areLoopsRunning = true;
mutex MenuManager::loopLock;

const int COLUMNS = 128;
const int LINES = 40;
const int FRAME_DELAY = 50;


void MenuManager::logicLoop()
{
	KeyEvent keyEvent;

	while (areLoopsRunning)
	{
		keyEvent = getKeyEvent();
		getActiveMenu()->processKeyEvent(keyEvent);
		loopLock.lock();
		loopLock.unlock();
	}
}

void MenuManager::renderLoop()
{
	COORD coord;
	coord.X = 0;
	coord.Y = 0;

	while (areLoopsRunning)
	{
		string contentToPrint;
		try
		{
			contentToPrint = getActiveMenu()->str();
		}
		catch (MenuIsEmpty)
		{
			printStringWithoutBlinking("Обнаружена попытка распечатать пустое меню.");
			system("pause");
			stopLoops();
		}
		catch (MenuHasNoChosenElement)
		{
			printStringWithoutBlinking("Обнаружена попытка распечатать меню без активных элементов.");
			system("pause");
			stopLoops();
		}

		loopLock.lock();
		Console::hideCursor();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		printStringWithoutBlinking(contentToPrint);
		loopLock.unlock();

		Sleep(FRAME_DELAY);
	}
}

void MenuManager::setConsoleResolution()
{
	system(("MODE CON: COLS=" + to_string(COLUMNS) + " LINES=" + to_string(LINES + 1)).c_str());
}

void MenuManager::printStringWithoutBlinking(string src)
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

void MenuManager::removeFromMenuStack(int popCount)
{
	// TODO: normal exception
	if (menuStack.size() < popCount + 1) throw(969);
	for (int i = 0; i < popCount; ++i)
	{
		menuStack.pop();
	}
}


void MenuManager::addToMenuStack(Menu* menu)
{
	menuStack.push(menu->getContentGenerator()());
}

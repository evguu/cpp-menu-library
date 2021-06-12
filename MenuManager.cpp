#include <Windows.h>
#include <mutex>
#include "Console.h"
#include "MenuManager.h"

stack<Menu *> MenuManager::menuStack = stack<Menu *>();
bool MenuManager::isLoopRunning = true;
mutex MenuManager::g_lock;

const int COLUMNS = 128;
const int LINES = 40;
const int FRAME_DELAY = 50;


void MenuManager::controlLoop()
{
	KeyEvent keyEvent;

	while (isLoopRunning)
	{
		keyEvent = getKeyEvent();
		getActive()->processKeyEvent(keyEvent);
		g_lock.lock();
		g_lock.unlock();
	}
}

void MenuManager::printLoop()
{
	COORD coord;
	coord.X = 0;
	coord.Y = 0;

	while (isLoopRunning)
	{
		string contentToPrint;
		try
		{
			contentToPrint = getActive()->str();
		}
		catch (MenuIsEmpty)
		{
			noBlinkOutput("Обнаружена попытка распечатать пустое меню.");
			system("pause");
			finish();
		}
		catch (MenuHasNoChosenElement)
		{
			noBlinkOutput("Обнаружена попытка распечатать меню без активных элементов.");
			system("pause");
			finish();
		}

		g_lock.lock();
		Console::hideCursor();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		noBlinkOutput(contentToPrint);
		g_lock.unlock();

		Sleep(FRAME_DELAY);
	}
}

void MenuManager::setConsoleResolution()
{
	system(("MODE CON: COLS=" + to_string(COLUMNS) + " LINES=" + to_string(LINES + 1)).c_str());
}

void MenuManager::noBlinkOutput(string src)
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

void MenuManager::popStack(int popCount)
{
	// TODO: normal exception
	if (menuStack.size() < popCount + 1) throw(969);
	for (int i = 0; i < popCount; ++i)
	{
		menuStack.pop();
	}
}


void MenuManager::addToStack(Menu* menu)
{
	menuStack.push(menu->getContentGenerator()());
}

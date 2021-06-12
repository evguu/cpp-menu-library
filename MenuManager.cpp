#include <Windows.h>
#include <mutex>
#include "Console.h"
#include "MenuManager.h"

stack<Menu *> MenuManager::menuStack = stack<Menu *>();
bool MenuManager::isLoopRunning = true;
mutex MenuManager::g_lock;

const int columns = 128;
const int lines = 40;
const int frameDelayInMilliseconds = 50;
bool haveUnshownChangesToBufferBeenMade = true;


void MenuManager::controlLoop()
{
	KeyEvent keyEvent;
	while (isLoopRunning)
	{
		keyEvent = getKeyEvent();
		getActive()->processKeyEvent(keyEvent);
		g_lock.lock();
		haveUnshownChangesToBufferBeenMade = true;
		g_lock.unlock();
	}
}

void MenuManager::printLoop()
{
	while (isLoopRunning)
	{
		if (haveUnshownChangesToBufferBeenMade)
		{
			g_lock.lock();
			haveUnshownChangesToBufferBeenMade = false;
			COORD coord;
			coord.X = 0;
			coord.Y = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			try
			{
				noBlinkOutput(getActive()->str());
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
			g_lock.unlock();
		}
		Sleep(frameDelayInMilliseconds);
	}
}

void MenuManager::setConsoleResolution()
{
	system(("MODE CON: COLS=" + to_string(columns) + " LINES=" + to_string(lines + 1)).c_str());
}

void MenuManager::noBlinkOutput(string src)
{
	char res[lines][columns];
	int line = 0;
	int pos = 0;
	for (auto i : src)
	{
		if (i == '\n')
		{
			while (pos != columns - 1)
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
			if (pos == columns - 1)
			{
				res[line][pos++] = '\n';
				++line;
				pos = 0;
			}
		}
	}
	while (line < lines)
	{
		while (pos != columns - 1)
		{
			res[line][pos++] = ' ';
		}
		res[line][pos++] = '\n';
		++line;
		pos = 0;
	}
	res[lines - 1][columns - 1] = 0;
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

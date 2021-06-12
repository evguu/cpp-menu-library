#include <Windows.h>
#include <mutex>
#include "Console.h"
#include "MenuManager.h"
#include "Display.h"

stack<Menu *> MenuManager::menuStack = stack<Menu *>();
bool MenuManager::areLoopsRunning = true;
mutex MenuManager::loopLock;

const int FRAME_DELAY = 50;


void MenuManager::logicLoop()
{
	KeyEvent keyEvent;

	while (areLoopsRunning)
	{
		keyEvent = getKeyEvent();
		loopLock.lock();
		getActiveMenu()->processKeyEvent(keyEvent);
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
			Display::printStringWithoutBlinking("Обнаружена попытка распечатать пустое меню.");
			system("pause");
			stopLoops();
		}
		catch (MenuHasNoChosenElement)
		{
			Display::printStringWithoutBlinking("Обнаружена попытка распечатать меню без активных элементов.");
			system("pause");
			stopLoops();
		}

		loopLock.lock();
		Console::hideCursor();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
		Display::printStringWithoutBlinking(contentToPrint);
		loopLock.unlock();

		Sleep(FRAME_DELAY);
	}
}


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

#include <Windows.h>
#include <mutex>
#include "../Utils/Console.h"
#include "MenuManager.h"
#include "../Utils/Display.h"
#include "../Utils/Exceptions.h"

std::stack<std::shared_ptr<Menu>> MenuManager::menuStack = std::stack<std::shared_ptr<Menu>>();
bool MenuManager::areLoopsRunning = true;
std::mutex MenuManager::loopLock;

const int FRAME_DELAY = 50;


void MenuManager::logicLoop()
{
	KeyEvent keyEvent;

	while (areLoopsRunning)
	{
		keyEvent = getKeyEvent();
		loopLock.lock();

		try 
		{
			getActiveMenu()->processKeyEvent(keyEvent);
		}
		catch (ManipulativeException e)
		{
			/* Ignore */
		}

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
		std::string contentToPrint;
		try
		{
			contentToPrint = getActiveMenu()->str();
		}
		catch (MenuIsEmpty)
		{
			Display::printStringWithoutBlinking("���������� ������� ����������� ������ ����.");
			system("pause");
			stopLoops();
		}
		catch (MenuHasNoChosenElement)
		{
			Display::printStringWithoutBlinking("���������� ������� ����������� ���� ��� �������� ���������.");
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


void MenuManager::addToMenuStack(std::shared_ptr<Menu> menu)
{
	menu->getElements().clear();
	menu->getContentGenerator()(menu);
	menuStack.push(menu);
}

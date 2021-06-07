#include <cassert>
#include "Input.h"
#include <sstream>
#include <Windows.h>
#include <mutex>
#include "Console.h"
#include "Menu.h"

stack<Menu *> Menu::menuStack = stack<Menu *>();
bool Menu::isLoopRunning = true;
mutex Menu::g_lock;
const int Menu::viewField = 12;

const int columns = 128;
const int lines = 40;

const int frameDelayInMilliseconds = 50;

bool haveUnshownChangesToBufferBeenMade = true;

void Menu::controlLoop()
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

void Menu::printLoop()
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

void Menu::setConsoleResolution()
{
	system(("MODE CON: COLS=" + to_string(columns) + " LINES=" + to_string(lines + 1)).c_str());
}

void Menu::noBlinkOutput(string src)
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

string Menu::str() const
{
	if (!elements.size())
	{
		throw(MenuIsEmpty());
	}
	if (chosenElementIndex == -1)
	{
		throw(MenuHasNoChosenElement());
	}

	stringstream ss;

	bool tmp;
	int index = -1;
	for (int metaIndex = 0; metaIndex < ((elements.size() <= (1 + 2 * viewField)) ? (elements.size()) : (1 + 2 * viewField)); ++metaIndex)
	{
		int offset = chosenElementIndex - viewField;
		if ((offset + 2 * viewField + 1) > elements.size()) offset = elements.size() - 1 - 2 * viewField;
		if (offset < 0) offset = 0;
		index = metaIndex + offset;
		if (metaIndex == 0 && index != 0)
		{
			ss << "/\\/\\/\\/\\/\\ /\\/\\/\\/\\/\\ /\\/\\/\\/\\/\\ /\\/\\/\\/\\/\\ /\\/\\/\\/\\/\\" << endl;
		}
		tmp = elements[index]->isChoosable();
		if (tmp)
		{
			if (chosenElementIndex == index)
			{
				ss << ">>";
			}
			else
			{
				ss << " +";
			}
		}
		ss << elements[index]->str();
		string additionalText = elements[index]->getAdditionalText();
		if ((additionalText != "") && (index == chosenElementIndex))
		{
			ss << additionalText << endl;
		}
	}
	if (index < elements.size() - 1)
	{
		ss << "\\/\\/\\/\\/\\/ \\/\\/\\/\\/\\/ \\/\\/\\/\\/\\/ \\/\\/\\/\\/\\/ \\/\\/\\/\\/\\/" << endl;
	}
	return ss.str();
}

void Menu::processKeyEvent(KeyEvent keyEvent)
{
	if (keyEvent.isUpDown())
	{
		int oldChosenElementIndex = chosenElementIndex;
		bool hasTriedToLeaveFolder = false;

		try
		{
			elements[chosenElementIndex]->processKeyEvent(keyEvent);
		}
		catch (FolderLeaveAttempt)
		{
			hasTriedToLeaveFolder = true;
		}
		catch (FolderProcessedUpDownKeyEvent)
		{
			return;
		}

		if (keyEvent.code == KC_DOWN)
		{
			chosenElementIndex = findNextActiveElementIndex(this->elements, this->chosenElementIndex);
		}
		else if (keyEvent.code == KC_UP)
		{
			chosenElementIndex = findPrevActiveElementIndex(this->elements, this->chosenElementIndex);
		}

		if (hasTriedToLeaveFolder && (oldChosenElementIndex != chosenElementIndex))
		{
			((MenuElementFolder*)(elements[oldChosenElementIndex]))->getIsActive() = false;
		}
	}
	else
	{
		elements[chosenElementIndex]->processKeyEvent(keyEvent);
	}
}

Menu* Menu::addElement(MenuElement * ref)
{
	elements.push_back(ref);
	return this;
}

void Menu::addToStack()
{
	menuStack.push(this->contentGenerator());
}

Menu* Menu::initChosenElementIndex()
{
	int index = 0;
	bool tmp;
	for (const auto& it : elements)
	{
		tmp = it->isChoosable();
		if (tmp)
		{
			chosenElementIndex = index;
			return this;
		}
		++index;
	}
	chosenElementIndex = -1;
	return this;
}

void Menu::popStack(int popCount)
{
	// TODO: normal exception
	if (menuStack.size() < popCount + 1) throw(969);
	for (int i = 0; i < popCount; ++i)
	{
		menuStack.pop();
	}
}

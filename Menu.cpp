#include <cassert>
#include "Input.h"
#include <sstream>
#include <Windows.h>
#include <mutex>
#include "Console.h"
#include "Menu.h"

stack<Menu *> Menu::menuStack = stack<Menu *>();
bool Menu::isLoopRunning = true;
bool Menu::hasMenuChanged = true;
mutex Menu::g_lock;
const int Menu::viewField = 12;

void Menu::controlLoop()
{
	int keyEvent;
	while (isLoopRunning)
	{
		keyEvent = Utils::inputKeyEvent();
		bool hasReacted = getActive()->recvCommand(keyEvent);
		if (hasReacted)
		{
			g_lock.lock();
			hasMenuChanged = true;
			g_lock.unlock();
		}
	}
}

void Menu::printLoop()
{
	while (isLoopRunning)
	{
		g_lock.lock();
		if (hasMenuChanged)
		{
			hasMenuChanged = false;
			COORD coord;
			coord.X = 0;
			coord.Y = 0;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
			try
			{
				Utils::noBlinkOutput(getActive()->str());
			}
			catch (int e)
			{
				if (e == 234)
				{
					Utils::noBlinkOutput("Обнаружена попытка распечатать пустое меню.");
					system("pause");
					terminate();
				}
				if (e == 235)
				{
					Utils::noBlinkOutput("Обнаружена попытка распечатать меню без активных элементов.");
					system("pause");
					terminate();
				}
			}
		}
		g_lock.unlock();
		Sleep(100);
	}
}

string Menu::str() const
{
	if (!elements.size()) // Меню не должно быть пустым
	{
		throw(234);
	}
	if (chosenElementIndex == -1) // Активный элемент должен быть установлен
	{
		throw(235);
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

bool Menu::recvCommand(int keyEvent)
{
	int index;
	bool tmp;
	int temporaryIndexBuffer;
	bool is77excCalled = false;
	vector<MenuElement *>::iterator lim;
	switch (keyEvent)
	{
		// При ловле клавиши вниз или вверх шлем их внутрь элемента. Если тот их обработает, швырнет исключение.
	case -KC_DOWN:
		try {
			elements[chosenElementIndex]->recvCommand(keyEvent);
		}
		catch(int exc)
		{
			if (exc == 666)
			{
				return true;
			}
			if (exc == 778)
			{
				is77excCalled = true;
			}
		}
		index = chosenElementIndex + 1;
		lim = elements.end();
		temporaryIndexBuffer = chosenElementIndex;
		for (auto it = elements.begin() + chosenElementIndex + 1; it != lim; ++it)
		{
			tmp = (*it)->isChoosable();
			if (tmp)
			{
				chosenElementIndex = index;
				break;
			}
			++index;
		}
		if (is77excCalled)
		{
			if (temporaryIndexBuffer != chosenElementIndex)
			{
				((MenuElementFolder*)(elements[temporaryIndexBuffer]))->getIsActive() = false;
			}
			else
			{
				return false;
			}
		}
		return true;
	case -KC_UP:
		try {
			elements[chosenElementIndex]->recvCommand(keyEvent);
		}
		catch (int exc)
		{
			if (exc == 666)
			{
				return true;
			}
			if (exc == 776)
			{
				is77excCalled = true;
			}
		}
		index = 0;
		lim = elements.begin() + chosenElementIndex;
		temporaryIndexBuffer = chosenElementIndex;
		for (auto it = elements.begin(); it != lim; ++it)
		{
			tmp = (*it)->isChoosable();
			if (tmp)
			{
				chosenElementIndex = index;
			}
			++index;
		}
		if (is77excCalled)
		{
			if (temporaryIndexBuffer != chosenElementIndex)
			{
				((MenuElementFolder*)(elements[temporaryIndexBuffer]))->getIsActive() = false;
			}
			else
			{
				return false;
			}
		}
		return true;
	default:
		return (*(elements.begin() + chosenElementIndex))->recvCommand(keyEvent);
	}
}

void Menu::addElement(MenuElement * ref)
{
	elements.push_back(ref);
}

void Menu::addToStack()
{
	menuStack.push(this);
}

void Menu::initChosenElementIndex()
{
	int index = 0;
	bool tmp;
	for (const auto& it : elements)
	{
		tmp = it->isChoosable();
		if (tmp)
		{
			chosenElementIndex = index;
			return;
		}
		++index;
	}
	chosenElementIndex = -1;
}

void Menu::reset()
{
	for (const auto& it : elements)
	{
		it->reset();
	}
	initChosenElementIndex();
}

void Menu::popStack(int popCount)
{
	if (menuStack.size() < popCount + 1) throw(969);
	for (int i = 0; i < popCount; ++i)
	{
		menuStack.pop();
	}
}

ostream & operator<<(ostream &out, Menu &menu)
{
	out << menu.str();
	return out;
}

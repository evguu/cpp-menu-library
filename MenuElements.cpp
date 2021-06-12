#include "MenuElements.h"
#include "Input.h"
#include <ctime>
#include <sstream>

MenuElement::MenuElement(string text) : text(text)
{
};

MenuElement::~MenuElement()
{
};

string MenuElement::getAdditionalText()
{
	return "";
};

auto& MenuElement::getText()
{
	return this->text;
};




























string MenuElementFolder::str() const
{
	stringstream ss;
	if (isActive)
	{
		ss << "  <> " << text << " [Выйдите за границы папки для закрытия]" << endl;
		for (int i = 0; i < elements.size(); ++i)
		{
			if (chosenElementIndex == i)
			{
				ss << "     >>";
			}
			else
			{
				ss << "      +";
			}
			ss << elements[i]->str();
		}
	}
	else
	{
		ss << "  <> " << text << " [Enter чтобы открыть]" << endl;
	}
	return ss.str();
}

void MenuElementFolder::processKeyEvent(KeyEvent keyEvent)
{
	if (keyEvent.isUpDown())
	{
		if (isActive)
		{
			// TODO: check choosability
			if ((chosenElementIndex + 1 != elements.size()) && (keyEvent.code == KC_DOWN))
			{
				chosenElementIndex++;
			}
			else if (chosenElementIndex && (keyEvent.code == KC_UP))
			{
				chosenElementIndex--;
			}
			else
			{
				throw(FolderLeaveAttempt());
			}
			throw(FolderProcessedUpDownKeyEvent());
		}
	}
	else if (keyEvent.isSpecial && keyEvent.code == KC_ENTER)
	{
		if (!isActive)
		{
			chosenElementIndex = 0;
			isActive = true;
		}
		else
		{
			elements[chosenElementIndex]->processKeyEvent(keyEvent);
		}
	}
	else
	{
		if (isActive)
		{
			return elements[chosenElementIndex]->processKeyEvent(keyEvent);
		}
	}
}

int findNextActiveElementIndex(vector<MenuElement*> elements, int chosenElementIndex)
{
	int result = chosenElementIndex;
	int index = chosenElementIndex + 1;
	vector<MenuElement *>::iterator lim = elements.end();
	bool tmp;

	for (auto it = elements.begin() + chosenElementIndex + 1; it != lim; ++it)
	{
		tmp = (*it)->isChoosable();
		if (tmp)
		{
			result = index;
			break;
		}
		++index;
	}
	return result;
}

int findPrevActiveElementIndex(vector<MenuElement*> elements, int chosenElementIndex)
{
	int result = chosenElementIndex;
	int index = 0;
	vector<MenuElement *>::iterator lim = elements.begin() + chosenElementIndex;
	bool tmp;

	for (auto it = elements.begin(); it != lim; ++it)
	{
		tmp = (*it)->isChoosable();
		if (tmp)
		{
			result = index;
		}
		++index;
	}
	return result;
}
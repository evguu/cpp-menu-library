#include <cassert>
#include <sstream>
#include "Menu.h"


int findNextActiveElementIndex(std::vector<std::shared_ptr<Component>> elements, int chosenElementIndex)
{
	int result = chosenElementIndex;
	int index = chosenElementIndex + 1;
	std::vector<std::shared_ptr<Component>>::iterator lim = elements.end();
	bool tmp;

	for (auto it = elements.begin() + chosenElementIndex + 1; it != lim; ++it)
	{
		tmp = (*it)->getIsFocusable();
		if (tmp)
		{
			result = index;
			break;
		}
		++index;
	}
	return result;
}

int findPrevActiveElementIndex(std::vector<std::shared_ptr<Component>> elements, int chosenElementIndex)
{
	int result = chosenElementIndex;
	int index = 0;
	std::vector<std::shared_ptr<Component>>::iterator lim = elements.begin() + chosenElementIndex;
	bool tmp;

	for (auto it = elements.begin(); it != lim; ++it)
	{
		tmp = (*it)->getIsFocusable();
		if (tmp)
		{
			result = index;
		}
		++index;
	}
	return result;
}













const int VIEW_FIELD = 12;

std::string Menu::str() const
{
	if (!elements.size())
	{
		throw(MenuIsEmpty());
	}
	if (chosenElementIndex == -1)
	{
		throw(MenuHasNoChosenElement());
	}

	std::stringstream ss;

	bool tmp;
	int index = -1;
	for (int metaIndex = 0; metaIndex < ((elements.size() <= (1 + 2 * VIEW_FIELD)) ? (elements.size()) : (1 + 2 * VIEW_FIELD)); ++metaIndex)
	{
		int offset = chosenElementIndex - VIEW_FIELD;
		if ((offset + 2 * VIEW_FIELD + 1) > elements.size()) offset = elements.size() - 1 - 2 * VIEW_FIELD;
		if (offset < 0) offset = 0;
		index = metaIndex + offset;
		if (metaIndex == 0 && index != 0)
		{
			ss << "/\\/\\/\\/\\/\\ /\\/\\/\\/\\/\\ /\\/\\/\\/\\/\\ /\\/\\/\\/\\/\\ /\\/\\/\\/\\/\\" << std::endl;
		}
		tmp = elements[index]->getIsFocusable();
		if (tmp)
		{
			if (chosenElementIndex == index)
			{
				ss << ">> ";
			}
			else
			{
				ss << " + ";
			}
		}
		ss << elements[index]->str() << std::endl;
		std::string additionalText = elements[index]->getAdditionalText();
		if ((additionalText != "") && (index == chosenElementIndex))
		{
			ss << additionalText << std::endl;
		}
	}
	if (index < elements.size() - 1)
	{
		ss << "\\/\\/\\/\\/\\/ \\/\\/\\/\\/\\/ \\/\\/\\/\\/\\/ \\/\\/\\/\\/\\/ \\/\\/\\/\\/\\/" << std::endl;
	}
	return ss.str();
}

void Menu::processKeyEvent(KeyEvent keyEvent)
{
	if (keyEvent.isUpDown())
	{
		elements[chosenElementIndex]->processKeyEvent(keyEvent);

		if (keyEvent.code == KC_DOWN)
		{
			chosenElementIndex = findNextActiveElementIndex(this->elements, this->chosenElementIndex);
		}
		else if (keyEvent.code == KC_UP)
		{
			chosenElementIndex = findPrevActiveElementIndex(this->elements, this->chosenElementIndex);
		}
	}
	else
	{
		elements[chosenElementIndex]->processKeyEvent(keyEvent);
	}
	std::cout << this << " processed " << keyEvent.code << std::endl;
}

void Menu::addElement(std::shared_ptr<Component> ref)
{
	elements.push_back(ref);
}

void Menu::initChosenElementIndex()
{
	int index = 0;
	bool tmp;
	for (const auto& it : elements)
	{
		tmp = it->getIsFocusable();
		if (tmp)
		{
			chosenElementIndex = index;
			return;
		}
		++index;
	}
	chosenElementIndex = -1;
}


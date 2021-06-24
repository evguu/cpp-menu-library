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
const std::string UP_LEAVE = "U";
const std::string DOWN_LEAVE = "D";
const std::string CAUGHT_YA = "C";

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

		for (int i = 0; i < tabOffset*(!!index); i++)
		{
			ss << "    ";
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
			for (int i = 0; i < tabOffset*(!!index); i++)
			{
				ss << "    ";
			}
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
		try
		{
			elements[chosenElementIndex]->processKeyEvent(keyEvent);
		}
		catch (ManipulativeException e)
		{
			std::string content = e.what();
			if (content == DOWN_LEAVE)
			{
				keyEvent = KeyEvent(KC_DOWN, true);
			}
			else if (content == UP_LEAVE)
			{
				keyEvent = KeyEvent(KC_UP, true);
			}
			else if (content == CAUGHT_YA)
			{
				throw;
			}
			else throw new std::exception("BRUH");
		}

		int oldElementIndex = chosenElementIndex;

		if (keyEvent.code == KC_DOWN)
		{
			chosenElementIndex = findNextActiveElementIndex(this->elements, this->chosenElementIndex);
			if (chosenElementIndex == oldElementIndex)
			{
				throw ManipulativeException(DOWN_LEAVE);
			}
		}
		else if (keyEvent.code == KC_UP)
		{
			chosenElementIndex = findPrevActiveElementIndex(this->elements, this->chosenElementIndex);
			if (chosenElementIndex == oldElementIndex)
			{
				throw ManipulativeException(UP_LEAVE);
			}
		}
		throw ManipulativeException(CAUGHT_YA);
	}
	else
	{
		elements[chosenElementIndex]->processKeyEvent(keyEvent);
	}
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


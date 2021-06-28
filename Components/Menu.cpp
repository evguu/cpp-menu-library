#include <cassert>
#include <sstream>
#include <string>
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













const int VIEW_FIELD = 9;
const std::string UP_LEAVE = "U";
const std::string DOWN_LEAVE = "D";
const std::string CAUGHT_YA = "C";


const std::string UPPER_BOUND_TEXT = "/\\/\\/\\/\\/\\ /\\/\\/\\/\\/\\ /\\/\\/\\/\\/\\ /\\/\\/\\/\\/\\ /\\/\\/\\/\\/\\";
const std::string LOWER_BOUND_TEXT = "\\/\\/\\/\\/\\/ \\/\\/\\/\\/\\/ \\/\\/\\/\\/\\/ \\/\\/\\/\\/\\/ \\/\\/\\/\\/\\/";

const std::string ACTIVE_SEQUENCE_START = "!@#$%^%$#@#$%^%$#";
const std::string ACTIVE_SEQUENCE_END =   "!@#$%$@#$#$@#$@#$";

std::pair<int, int> fit(int overallCount, int visibleCount, std::pair<int, int> shouldBeIncluded)
{
	return std::make_pair(0, overallCount);
}

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

	int c = 0;
	for (auto it : elements)
	{
		if (c == chosenElementIndex)
		{ 
			ss << ACTIVE_SEQUENCE_START << std::endl;
			ss << " >> " << it->str() << std::endl;
			if (it->getAdditionalText() != "")
			{
				ss << it->getAdditionalText() << std::endl;
			}
			ss << ACTIVE_SEQUENCE_END << std::endl;
		}
		else
		{
			ss << (it->getIsFocusable()?" -- ":"") << it->str() << std::endl;
		}
		c++;
	}

	std::string segment;
	std::vector<std::string> seglist;

	std::pair<int, int> shouldBeIncluded{ 0, 0 };
	c = 0;
	while (std::getline(ss, segment, '\n'))
	{
		if (segment == ACTIVE_SEQUENCE_START)
		{
			shouldBeIncluded.first = c;
			continue;
		}
		if (segment == ACTIVE_SEQUENCE_END)
		{
			shouldBeIncluded.second = c;
			continue;
		}
		seglist.push_back(segment);
		c++;
	}

	std::pair<int, int> linesToInclude = fit(seglist.size(), VIEW_FIELD - tabOffset, shouldBeIncluded);

	ss = std::stringstream();

	ss << "Segment count: " << seglist.size() << "; Display storage: " << VIEW_FIELD - tabOffset << "; Needs [" <<
		shouldBeIncluded.first << "; " << shouldBeIncluded.second << "); Result: [" <<
		linesToInclude.first << "; " << linesToInclude.second << ")." << std::endl;

	for (int i = linesToInclude.first; i < linesToInclude.second; ++i)
	{
		ss << seglist[i] << std::endl;
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


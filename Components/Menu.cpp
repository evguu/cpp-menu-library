#include <cassert>
#include <sstream>
#include <string>
#include "Menu.h"
#include "../Utils/Console.h"

#define DEBUG

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






const std::string UP_LEAVE = "U";
const std::string DOWN_LEAVE = "D";
const std::string CAUGHT_YA = "C";

std::pair<int, int> fit(int overallCount, int visibleCount, std::pair<int, int> shouldBeIncluded)
{
	int requiredCount = shouldBeIncluded.second - shouldBeIncluded.first;

	// Если нельзя вместить запрошенные строки на экран, вмещаем сколько можем.
	// Если влезает идеально, тоже обрабатывается здесь.
	if (requiredCount >= visibleCount) return std::make_pair(shouldBeIncluded.first, shouldBeIncluded.first + visibleCount);

	int availableSpace = visibleCount - requiredCount;
	int upperSpace = availableSpace / 2;

	// Необходимо предусмотреть граничные случаи.
	if (shouldBeIncluded.first < upperSpace)
	{
		upperSpace = shouldBeIncluded.first;
	}
	if (overallCount - 1 < shouldBeIncluded.second + availableSpace - upperSpace)
	{
		upperSpace = shouldBeIncluded.second + availableSpace - overallCount;
	}

	int start = shouldBeIncluded.first - upperSpace;
	int end = shouldBeIncluded.second + availableSpace - upperSpace;

	if (start < 0) start = 0;
	if (end > overallCount) end = overallCount;

	return std::make_pair(start, end);
}

void offsetBy(std::stringstream& ss, int tabOffset)
{
	for (int i = 0; i < tabOffset; ++i)
	{
		ss << "    ";
	}
}

std::string Menu::str() const
{
	const int VIEW_FIELD = 38;
	const std::string ACTIVE_SEQUENCE_START = "!~ACTIVE_SEQUENCE_START~!";
	const std::string ACTIVE_SEQUENCE_END = "!~ACTIVE_SEQUENCE_END~!";

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
			offsetBy(ss, tabOffset);
			ss << " >> " << it->str() << std::endl;
			if (it->getAdditionalText() != "")
			{
				offsetBy(ss, tabOffset);
				ss << it->getAdditionalText() << std::endl;
			}
			ss << ACTIVE_SEQUENCE_END << std::endl;
		}
		else
		{
			offsetBy(ss, tabOffset);
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

		int lineWidth = Console::standardMode.getColumns() - 2;
		if (segment.length() > lineWidth)
		{
			int i;
			for (i = 0; i < segment.length() / lineWidth; ++i)
			{
				seglist.push_back(segment.substr(i * lineWidth, lineWidth));
				c++;
			}
			
			int remainder = segment.length() % lineWidth;
			if (remainder)
			{
				seglist.push_back(segment.substr(i * lineWidth, remainder));
				c++;
			}
		}
		else
		{
			seglist.push_back(segment);
			c++;
		}
	}

	std::pair<int, int> linesToInclude = fit(seglist.size(), VIEW_FIELD, shouldBeIncluded);

	ss = std::stringstream();

	ss << "---- ---- Меню ";
#ifdef DEBUG
	ss << this << " " << seglist.size() << "s; " << VIEW_FIELD - tabOffset << "sp; [" <<
		shouldBeIncluded.first << "; " << shouldBeIncluded.second << ") -> [" <<
		linesToInclude.first << "; " << linesToInclude.second << ").";
#endif // DEBUG

	ss << " ---- ----" << std::endl;
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


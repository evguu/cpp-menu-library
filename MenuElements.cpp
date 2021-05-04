#include "MenuElements.h"
#include "Input.h"
#include <ctime>
#include <sstream>

//

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

//

string MenuElementTitle::str() const
{
	stringstream ss;
	ss << "-< " << text << " >- " << endl;
	return ss.str();
}

string MenuElementSubtitle::str() const
{
	stringstream ss;
	ss << endl << "      [ " << text << " ]" << endl;
	return ss.str();
}

string MenuElementFunctionButton::str() const
{
	stringstream ss;
	ss << "  " << text << endl;
	return ss.str();
}

bool MenuElementFunctionButton::recvCommand(KeyEvent keyEvent)
{
	if(keyEvent.isSpecial && keyEvent.code == KC_ENTER)
	{
		func();
		return true;
	}
	return false;
}

string MenuElementEditField::str() const
{
	stringstream ss;
	if (isTextHidden)
	{
		ss << "  " << text << ": ";
		for (int i = 0; i < (int)input.length(); i++)
		{
			ss << "*";
		}
		ss << endl;
	}
	else
	{
		ss << "  " << text << ": " << input << endl;
	}
	return ss.str();
}

string& MenuElementEditField::getInput()
{
	return input;
}

bool MenuElementEditField::recvCommand(KeyEvent keyEvent)
{
	if (!keyEvent.isSpecial)
	{
		if (((allowedSymbols.length() == 0) || (allowedSymbols.find((char)keyEvent.code) != string::npos)) && ((maxLength == 0) || (input.length() < maxLength)))
		{
			input += (char)keyEvent.code;
			return true;
		}
	}
	else if (keyEvent.code == KC_DELETE || keyEvent.code == KC_BACKSPACE)
	{
		if (input.length()) input.pop_back();
		return true;
	}
	return false;
}

const string MenuElementChoice::noChoicesFoundMessage = "LML_RESERVED_MESSAGE::NO_CHOICES_FOUND";

string MenuElementChoice::str() const
{
	stringstream ss;
	int len = options.size();
	if (len == 0)
	{
		ss << "  " << text << ": -- СПИСОК ВЫБОРА ПУСТ! --" << endl;
	}
	else if (len == 1)
	{
		ss << "  " << text << ": --" << options[activeOption] << "--" << endl;
	}
	else
	{
		ss << "  " << text << ": <-" << options[activeOption] << "->" << endl;
	}
	return ss.str();
}

clock_t _lastClock = 0;
bool _wasPreviousDirectionRight = false;
int _timeCounter = 0;
const int _maximalComboInterval = 200;
const int _maxTrueSpeed = 64;
const int _doublingTime = 3000;

bool MenuElementChoice::recvCommand(KeyEvent keyEvent)
{
	if (keyEvent.isLeftRight())
	{
		bool isRight = (keyEvent.code == KC_RIGHT);
		if (options.size() > 1)
		{
			int timeElapsed = (long)(((double)clock() - _lastClock) / CLOCKS_PER_SEC * 1000);
			if ((timeElapsed < _maximalComboInterval) && !(_wasPreviousDirectionRight^isRight))
			{
				_timeCounter += timeElapsed;
			}
			else
			{
				_timeCounter = 0;
				_wasPreviousDirectionRight = isRight;
			}
			int trueSpeed = 1 << (2 * _timeCounter / _doublingTime);
			if (trueSpeed > _maxTrueSpeed)
			{
				trueSpeed = _maxTrueSpeed;
			}
			activeOption = (options.size() + (isRight?(1):(-1)) * trueSpeed + activeOption) % options.size();
		}
		_lastClock = clock();
		return true;
	}
	return false;
}

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

bool MenuElementFolder::recvCommand(KeyEvent keyEvent)
{
	if (keyEvent.isUpDown())
	{
		if (isActive)
		{
			// TODO: check choosability
			if (chosenElementIndex + 1 != elements.size())
			{
				chosenElementIndex++;
			}
			else
			{
				throw(FolderLeaveAttempt());
			}
			throw(FolderProcessedUpDownKeyEvent());
		}
		if (isActive)
		{
			// TODO: check choosability
			if (chosenElementIndex)
			{
				chosenElementIndex--;
			}
			else
			{
				throw(FolderLeaveAttempt());
			}
			throw(FolderProcessedUpDownKeyEvent());
		}
		return false; // Чтобы варнинги не кидало
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
			elements[chosenElementIndex]->recvCommand(keyEvent);
		}
		return true;
	}
	else
	{
		if (isActive)
		{
			return elements[chosenElementIndex]->recvCommand(keyEvent);
		}
		return false;
	}
}

#include "Field.h"

std::string& Field::getInput()
{
	return input;
}

bool Field::hasFreeSpace()
{
	return (!maxLength || (input.length() < maxLength));
}

bool Field::isCharAllowed(char ch)
{
	return (!allowedSymbols.length() || (allowedSymbols.find(ch) != std::string::npos));
}

void Field::processKeyEvent(KeyEvent keyEvent)
{
	if (!keyEvent.isSpecial)
	{
		if (this->isCharAllowed(keyEvent.code) && this->hasFreeSpace())
		{
			input += keyEvent.code;
		}
	}
	else if (keyEvent.code == KC_DELETE || keyEvent.code == KC_BACKSPACE)
	{
		if (input.length()) input.pop_back();
	}
}

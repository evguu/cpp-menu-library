#pragma once
#include <string>
#include "MenuElements.h"

class Field : public MenuElement
{
private:
	string input;
	bool isTextHidden;
	string allowedSymbols;
	int maxLength;
	int minLength;
public:
	Field(string text, bool isTextHidden = false, string allowedSymbols = "", int minLength = 0, int maxLength = 0) :
		MenuElement(text), input(""), isTextHidden(isTextHidden), allowedSymbols(allowedSymbols), minLength(minLength), maxLength(maxLength) {};
	~Field() {};

	string str() const { return "placeholder"; };
	string& getInput();
	bool hasFreeSpace();
	bool isCharAllowed(char ch);
	void processKeyEvent(KeyEvent keyEvent);
	bool isChoosable() { return true; };
	string getAdditionalText() override
	{
		return "        Не менее " + to_string(minLength) + " символов.\n"
			"        Доступные символы: " + allowedSymbols;
	}
};


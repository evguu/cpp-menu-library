#pragma once
#include <string>
#include "Component.h"

class Field : public Component
{
private:
	std::string input;
	bool isTextHidden;
	std::string allowedSymbols;
	int maxLength;
	int minLength;
public:
	Field(std::string text, bool isTextHidden = false, std::string allowedSymbols = "", int minLength = 0, int maxLength = 0) :
		Component(text, true), input(""), isTextHidden(isTextHidden), allowedSymbols(allowedSymbols), minLength(minLength), maxLength(maxLength) {};
	~Field() {};

	std::string str() const { return "placeholder"; };
	std::string& getInput();
	bool hasFreeSpace();
	bool isCharAllowed(char ch);
	void processKeyEvent(KeyEvent keyEvent);
	std::string getAdditionalText() override
	{
		return "        Не менее " + std::to_string(minLength) + " символов.\n"
			"        Доступные символы: " + allowedSymbols;
	}
};


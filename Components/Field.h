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

	std::string str() const override { return text+": "+input; };
	std::string& getInput();
	bool hasFreeSpace();
	bool isCharAllowed(char ch);
	void processKeyEvent(KeyEvent keyEvent);
	std::string getAdditionalText() const override
	{
		return "�� ����� " + std::to_string(minLength) + " ��������.\n��������� �������: " + allowedSymbols;
	}
};


#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Input.h"

using namespace std;

class MenuElement;

class MenuElement
{
protected:
	string text;
	bool isFocusable;
public:
	MenuElement(string text, bool isFocusable);
	virtual ~MenuElement();

	virtual string str() const = 0;
	virtual void processKeyEvent(KeyEvent keyEvent) = 0;
	bool getIsFocusable() const { return isFocusable; };
	virtual string getAdditionalText();
	auto& getText();
};

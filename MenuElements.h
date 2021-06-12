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
public:
	MenuElement(string text);
	virtual ~MenuElement();

	virtual string str() const = 0;
	virtual void processKeyEvent(KeyEvent keyEvent) = 0;
	virtual bool isChoosable() = 0;
	virtual string getAdditionalText();
	auto& getText();
};

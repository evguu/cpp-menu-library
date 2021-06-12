#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Input.h"

using namespace std;

class Component
{
protected:
	string text;
	bool isFocusable;
public:
	Component(string text, bool isFocusable);
	virtual ~Component();

	virtual string str() const = 0;
	virtual void processKeyEvent(KeyEvent keyEvent) = 0;
	virtual string getAdditionalText();

	string getText() const;	
	bool getIsFocusable() const;
};

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "../Utils/Input.h"

class Component
{
protected:
	std::string text;
	bool isFocusable;
public:
	Component(std::string text, bool isFocusable);
	virtual ~Component();

	virtual std::string str() const = 0;
	virtual void processKeyEvent(KeyEvent keyEvent) = 0;
	virtual std::string getAdditionalText();

	std::string getText() const;
	bool getIsFocusable() const;
};

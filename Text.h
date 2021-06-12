#pragma once
#include <string>
#include "MenuElements.h"

class Text : public MenuElement
{
public:
	Text(std::string text) : MenuElement(text, false) {};
	~Text() {};

	std::string str() const { return "placeholder"; };
	void processKeyEvent(KeyEvent keyEvent) {};
};


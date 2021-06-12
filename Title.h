#pragma once
#include <string>
#include "MenuElements.h"

class Title : public MenuElement
{
public:
	Title(std::string text);
	~Title() {};

	std::string str() const;
	void processKeyEvent(KeyEvent keyEvent);
	bool isChoosable();
};


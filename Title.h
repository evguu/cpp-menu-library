#pragma once
#include <string>
#include "Component.h"

class Title : public Component
{
public:
	Title(std::string text);
	~Title() {};

	std::string str() const;
	void processKeyEvent(KeyEvent keyEvent);
};


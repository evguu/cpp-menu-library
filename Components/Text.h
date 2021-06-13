#pragma once
#include <string>
#include "Component.h"

class Text : public Component
{
public:
	Text(std::string text) : Component(text, false) {};
	~Text() {};

	std::string str() const { return text; };
	void processKeyEvent(KeyEvent keyEvent) {};
};


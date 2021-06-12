#pragma once
#include <string>
#include "MenuElements.h"

class Button : public MenuElement
{
private:
	void(*buttonPressHandler)();
public:
	Button(std::string text, void(*buttonPressHandler)()) : MenuElement(text, true), buttonPressHandler(buttonPressHandler) {};
	~Button() {};
	string str() const { return "placeholder"; };
	void processKeyEvent(KeyEvent keyEvent);
	auto& getButtonPressHandler() { return buttonPressHandler; };
};


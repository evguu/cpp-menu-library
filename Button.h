#pragma once
#include <string>
#include "Component.h"

class Button : public Component
{
private:
	void(*buttonPressHandler)();
public:
	Button(std::string text, void(*buttonPressHandler)()) : Component(text, true), buttonPressHandler(buttonPressHandler) {};
	~Button() {};
	string str() const { return "placeholder"; };
	void processKeyEvent(KeyEvent keyEvent);
	auto& getButtonPressHandler() { return buttonPressHandler; };
};


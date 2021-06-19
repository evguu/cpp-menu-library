#pragma once
#include <string>
#include "Component.h"
#include <functional>

class Button : public Component
{
private:
	std::function<void()> buttonPressHandler;
public:
	Button(std::string text, std::function<void()> buttonPressHandler) : Component(text, true), buttonPressHandler(buttonPressHandler) {};
	std::string str() const { return text; };
	void processKeyEvent(KeyEvent keyEvent)
	{
		if (keyEvent.isSpecial && keyEvent.code == KC_ENTER)
		{
			buttonPressHandler();
		}
	}

	std::function<void()>& getButtonPressHandler() { return buttonPressHandler; };
};

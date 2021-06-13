#pragma once
#include <string>
#include "Component.h"
#include "Display.h"
#include "Executable.h"

class Button : public Component
{
private:
	Executable* buttonPressHandler;
public:
	Button(std::string text, Executable* buttonPressHandler) : Component(text, true), buttonPressHandler(buttonPressHandler) {};
	~Button() { delete buttonPressHandler; };
	std::string str() const { return text; };
	void processKeyEvent(KeyEvent keyEvent)
	{
		if (keyEvent.isSpecial && keyEvent.code == KC_ENTER)
		{
			buttonPressHandler->execute();
		}
	}

	Executable*& getButtonPressHandler() { return buttonPressHandler; };
};

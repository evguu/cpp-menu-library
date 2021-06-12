#pragma once
#include <string>
#include "Component.h"
#include "Display.h"

template <class T>
class BasicButton : public Component
{
private:
	T buttonPressHandler;
public:
	BasicButton(std::string text, T buttonPressHandler) : Component(text, true), buttonPressHandler(buttonPressHandler) {};
	~BasicButton() {};
	std::string str() const { return text; };
	void processKeyEvent(KeyEvent keyEvent)
	{
		if (keyEvent.isSpecial && keyEvent.code == KC_ENTER)
		{
			buttonPressHandler();
		}
	}

	T& getButtonPressHandler() { return buttonPressHandler; };
};

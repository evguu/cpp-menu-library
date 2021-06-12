#include "Button.h"

void Button::processKeyEvent(KeyEvent keyEvent)
{
	if (keyEvent.isSpecial && keyEvent.code == KC_ENTER)
	{
		buttonPressHandler();
	}
}

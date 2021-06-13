#pragma once
#include "Display.h"
#include "Executable.h"

class DialogDecorator
{
public:
	static Display::Mode dialogMode;

	static Executable* apply(Executable* wrappee)
	{
		return Executable::from([wrappee]() {
			Display::setMode(dialogMode);
			wrappee->execute();
			system("pause");
			Display::setMode(Display::standardMode);
		});
	}
};

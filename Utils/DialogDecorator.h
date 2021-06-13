#pragma once
#include "Console.h"
#include "Executable.h"

class DialogDecorator
{
public:
	static Console::Mode dialogMode;

	static Executable* apply(Executable* wrappee)
	{
		return Executable::from([wrappee]() {
			Console::setMode(dialogMode);
			wrappee->execute();
			system("pause");
			Console::setMode(Console::standardMode);
		});
	}
};

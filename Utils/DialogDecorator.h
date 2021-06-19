#pragma once
#include "Console.h"
#include <functional>

class DialogDecorator
{
public:
	static Console::Mode dialogMode;

	static std::function<void()> apply(std::function<void()> wrappee)
	{
		return [wrappee]() {
			Console::setMode(dialogMode);
			wrappee();
			system("pause");
			Console::setMode(Console::standardMode);
		};
	}
};

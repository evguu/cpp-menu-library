#pragma once
#include "Button.h"

class Dialog
{
public:
	static void start() { Display::setMode(Display::modeDialog); }
	static void end() { system("pause"); Display::setMode(Display::modeMenu); }
	static auto fromVoid(void(*wrapped)()) { return [wrapped]() { start(); wrapped(); end(); }; };
};

static auto __dialogExample = Dialog::fromVoid([]() {});;

typedef BasicButton<void(*)()> Button;
typedef BasicButton<decltype(__dialogExample)> DialogButton;

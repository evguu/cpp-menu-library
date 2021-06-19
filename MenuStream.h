#pragma once
#include "Components/Menu.h"

class MenuStream
{
public:
	MenuStream(Menu* menu) : menu(menu) {};
	MenuStream& operator()(std::shared_ptr<Component> cmp)
	{
		menu->addElement(cmp);
		return *this;
	}
	Menu* init() {
		menu->initChosenElementIndex();
		return menu;
	}
private:
	Menu* menu;
};

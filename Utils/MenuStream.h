#pragma once
#include "../Core/MenuAggregator.h"

class MenuStream
{
public:
	MenuStream(std::string menu) : menu(getMenuForGenerator(menu)) {};
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

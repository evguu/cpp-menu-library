#pragma once
#include "../Core/MenuAggregator.h"

class MenuStream
{
public:
	MenuStream(std::string menu) : menu(getMenu(menu)) {};
	MenuStream(std::shared_ptr<Menu> menu) : menu(menu) {};
	MenuStream& operator()(std::shared_ptr<Component> cmp)
	{
		menu->addElement(cmp);
		return *this;
	}
	std::shared_ptr<Menu> init() {
		menu->initChosenElementIndex();
		return menu;
	}
private:
	std::shared_ptr<Menu> menu;
};

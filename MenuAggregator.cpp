#include "MenuAggregator.h"

std::map<std::string, Menu *> menuAggregator;

Menu* newMenu(std::string str)
{
	Menu* menu = new Menu();
	menuAggregator[str] = menu;
	return menu;
}

Menu* getMenu(std::string str)
{
	if (menuAggregator.find(str) == menuAggregator.end()) throw(unknownKeyException());
	return menuAggregator[str];
}

Menu* getMenuForGenerator(std::string str)
{
	Menu *menu, *buf;
	try { menu = getMenu(str); }
	catch (unknownKeyException) { menu = nullptr; };
	buf = newMenu(str);
	if (menu)
	{
		buf->getContentGenerator() = menu->getContentGenerator();
		delete menu;
	};
	menu = buf;
	return menu;
}

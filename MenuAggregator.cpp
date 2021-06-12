#include "MenuAggregator.h"

map<string, Menu *> menuAggregator;

Menu* newMenu(string str)
{
	Menu* menu = new Menu();
	menuAggregator[str] = menu;
	return menu;
}

Menu* getMenu(string str)
{
	if (menuAggregator.find(str) == menuAggregator.end()) throw(unknownKeyException());
	return menuAggregator[str];
}

Menu* getMenuForGenerator(string str)
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

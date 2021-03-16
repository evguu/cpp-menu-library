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
	return menuAggregator[str];
}

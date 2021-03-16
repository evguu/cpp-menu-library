#include "MenuAggregator.h"

map<string, Menu *> menuAggregator;
map<string, MenuElementFolder *> FDAggregator;

Menu* newMenu(string str)
{
	Menu* menu = new Menu();
	menuAggregator[str] = menu;
	return menu;
}

Menu* getMenu(string str)
{
	if (menuAggregator.find(str) == menuAggregator.end()) throw(unknownMenuIdentifierException());
	return menuAggregator[str];
}

MenuElementFolder * newFD(string str, string text)
{
	MenuElementFolder* menu = new MenuElementFolder(text);
	FDAggregator[str] = menu;
	return menu;
}

MenuElementFolder * getFD(string str)
{
	if (FDAggregator.find(str) == FDAggregator.end()) throw(unknownMenuIdentifierException());
	return FDAggregator[str];
}

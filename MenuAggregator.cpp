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
	if (menuAggregator.find(str) == menuAggregator.end()) throw(unknownKeyException());
	return menuAggregator[str];
}

Menu* getMenuWithGeneratorMigration(string str)
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



MenuElementFolder * newFD(string str, string text)
{
	MenuElementFolder* menu = new MenuElementFolder(text);
	FDAggregator[str] = menu;
	return menu;
}

MenuElementFolder * getFD(string str)
{
	if (FDAggregator.find(str) == FDAggregator.end()) throw(unknownKeyException());
	return FDAggregator[str];
}

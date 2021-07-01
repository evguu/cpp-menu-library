#include "MenuAggregator.h"

std::map<std::string, std::shared_ptr<Menu>> menuAggregator;

std::shared_ptr<Menu> newMenu(std::string text, std::string key, int tabOffset)
{
	std::shared_ptr<Menu> menu = std::make_shared<Menu>(text, tabOffset);
	menuAggregator[key] = menu;
	return menu;
}

std::shared_ptr<Menu> getMenu(std::string str)
{
	if (menuAggregator.find(str) == menuAggregator.end()) throw(unknownKeyException());
	return menuAggregator[str];
}

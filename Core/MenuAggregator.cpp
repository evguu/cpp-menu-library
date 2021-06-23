#include "MenuAggregator.h"

std::map<std::string, std::shared_ptr<Menu>> menuAggregator;

std::shared_ptr<Menu> newMenu(std::string str)
{
	std::shared_ptr<Menu> menu = std::make_shared<Menu>();
	menuAggregator[str] = menu;
	return menu;
}

std::shared_ptr<Menu> getMenu(std::string str)
{
	if (menuAggregator.find(str) == menuAggregator.end()) throw(unknownKeyException());
	return menuAggregator[str];
}

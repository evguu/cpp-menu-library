#pragma once
#include "Menu.h"
#include "Component.h"
#include <map>
#include <string>

class unknownKeyException : std::exception {};

Menu* newMenu(std::string str);
Menu* getMenu(std::string str);
Menu* getMenuForGenerator(std::string str);

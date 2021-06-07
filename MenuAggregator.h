#pragma once
#include "Menu.h"
#include "MenuElements.h"
#include <map>
#include <string>
using namespace std;

class unknownKeyException : exception {};

Menu* newMenu(string str);
Menu* getMenu(string str);
Menu* getMenuWithGeneratorMigration(string str);

MenuElementFolder* newFD(string str, string text);
MenuElementFolder* getFD(string str);

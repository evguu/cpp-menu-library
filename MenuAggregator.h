#pragma once
#include "Menu.h"
#include <map>
#include <string>

using namespace std;

class unknownMenuIdentifierException : exception {};

Menu* newMenu(string str);

Menu* getMenu(string str);
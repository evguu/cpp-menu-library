#pragma once
#include "../Components/Menu.h"
#include "../Components/Component.h"
#include <map>
#include <string>

// Вспомогательные макросы
#define MD_START(mid) newMenu(mid)->getContentGenerator() = [](){return getMenuForGenerator(mid)
#define MD_END ->initChosenElementIndex();};
#define ADD(type, ...) ->addElement([](){auto e = new type(__VA_ARGS__);
#define $ return e;}())
#define AS(type, expr) ((type*)(expr))


class unknownKeyException : std::exception {};

Menu* newMenu(std::string str);
Menu* getMenu(std::string str);
Menu* getMenuForGenerator(std::string str);

#pragma once
#include "../Components/Menu.h"
#include "../Components/Component.h"
#include "../MenuStream.h"
#include <map>
#include <string>

// Вспомогательные макросы
#define MD_START(mid) newMenu(mid)->getContentGenerator() = [](){return MenuStream(getMenuForGenerator(mid))
#define MD_END .init();};
#define ADD(type, ...) ([](){auto e = std::make_shared<type>(__VA_ARGS__);
#define $ return e;}())
#define AS(type, expr) ((type*)(expr))


class unknownKeyException : std::exception {};

Menu* newMenu(std::string str);
Menu* getMenu(std::string str);
Menu* getMenuForGenerator(std::string str);

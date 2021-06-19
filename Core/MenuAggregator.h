#pragma once
#include "../Components/Menu.h"
#include "../Components/Component.h"
#include "../Utils/MenuStream.h"
#include <map>
#include <string>

// Вспомогательные макросы
#define ADD(type, ...) ([](){auto e = std::make_shared<type>(__VA_ARGS__);
#define $ return e;}())
#define AS(type, expr) ((type*)(expr))


class unknownKeyException : std::exception {};

Menu* newMenu(std::string str);
Menu* getMenu(std::string str);
Menu* getMenuForGenerator(std::string str);

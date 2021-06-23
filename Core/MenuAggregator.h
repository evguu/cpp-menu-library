#pragma once
#include "../Components/Menu.h"
#include "../Components/Component.h"
#include <map>
#include <string>

// Вспомогательные макросы
#define ADD(type, ...) ([](){auto e = std::make_shared<type>(__VA_ARGS__);
#define $ return e;}())
#define AS(type, expr) ((type*)(expr))


class unknownKeyException : std::exception {};

std::shared_ptr<Menu> newMenu(std::string str);
std::shared_ptr<Menu> getMenu(std::string str);
std::shared_ptr<Menu> getMenuForGenerator(std::string str);

#pragma once
#include "../Components/Menu.h"
#include "../Components/Component.h"
#include <map>
#include <string>

// Вспомогательные макросы
#define ADD(shp, ...) ([](){auto e = shp;{__VA_ARGS__;}return e;}())
#define MSH(type, ...) std::make_shared<type>(__VA_ARGS__)
#define AS(type, expr) (std::reinterpret_pointer_cast<type>(expr))

class unknownKeyException : std::exception {};

std::shared_ptr<Menu> newMenu(std::string text, std::string key, int tabOffset=0);
std::shared_ptr<Menu> getMenu(std::string str);

#pragma once
#include "Console.h"
#include <string>

class Display
{
public:
	static void printStringWithoutBlinking(std::string src);
private:
	Display() = delete;
};

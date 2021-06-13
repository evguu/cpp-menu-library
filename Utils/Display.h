#pragma once
#include "Console.h"
#include <string>

class Display
{
public:
	static void printStringWithoutBlinking(std::string src);
	static void setBuffer(char* buffer);
private:
	Display() = delete;
	static char* buffer;
};

#pragma once
#include <string>

class Console
{
public:
	static void hideCursor();
	static void fixEncoding();
	static void sayGoodbye();
private:
	Console() = delete;
	static std::string goodbyeMessage;
};

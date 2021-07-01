#pragma once
#include <string>

class Option
{
public:
	Option(std::string text, bool isCorrect) : text(text), isCorrect(isCorrect) {};
	auto& getText() const { return text; }
	auto& getIsCorrect() { return isCorrect; }
private:
	std::string text;
	bool isCorrect;
};


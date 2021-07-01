#pragma once
#include <string>
#include <vector>
#include "Option.h"

class Question
{
public:
	Question(std::string text, std::vector<Option> options) : text(text), options(options) {};
	auto& getText() { return text; }
	auto& getOptions() { return options; }
private:
	std::string text;
	std::vector<Option> options;
};


#pragma once
#include <string>
#include "Component.h"

class Choice : public Component
{
public:
	static const std::string noChoicesFoundMessage;
private:
	std::vector<std::string> options;
	int activeOption = 0;
public:
	Choice(std::string text, std::vector<std::string> options) : Component(text, true), options(options) {};
	Choice(std::string text, int rangeStart, int rangeEnd, int rangeStep = 1) : Component(text, true)
	{
		for (int i = rangeStart; i < rangeEnd; i += rangeStep)
		{
			options.push_back(std::to_string(i));
		}
	};

	~Choice() {};

	std::string str() const;

	// TODO: кидать исключение
	// ≈сли ничего не выбрано (вектор выбора пуст), возвращает MenuElementChoice::noChoicesFoundMessage.
	std::string getChoice()
	{
		if (options.size())
		{
			return options[activeOption];
		}
		else
		{
			return noChoicesFoundMessage;
		}
	};
	auto& getOptions() { return options; };
	auto& getActiveOption() { return activeOption; };
	void processKeyEvent(KeyEvent keyEvent);
};


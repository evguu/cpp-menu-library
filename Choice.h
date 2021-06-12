#pragma once
#include <string>
#include "Component.h"

class Choice : public Component
{
public:
	static const string noChoicesFoundMessage;
private:
	vector<string> options;
	int activeOption = 0;
public:
	Choice(string text, vector<string> options) : Component(text, true), options(options) {};
	Choice(string text, int rangeStart, int rangeEnd, int rangeStep = 1) : Component(text, true)
	{
		for (int i = rangeStart; i < rangeEnd; i += rangeStep)
		{
			options.push_back(to_string(i));
		}
	};

	~Choice() {};

	string str() const { return "placeholder"; };

	// TODO: кидать исключение
	// ≈сли ничего не выбрано (вектор выбора пуст), возвращает MenuElementChoice::noChoicesFoundMessage.
	string getChoice()
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


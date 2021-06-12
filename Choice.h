#pragma once
#include <string>
#include "MenuElements.h"

class Choice : public MenuElement
{
public:
	static const string noChoicesFoundMessage;
private:
	vector<string> options;
	int activeOption = 0;
public:
	Choice(string text, vector<string> options) : MenuElement(text), options(options) {};
	Choice(string text, int rangeStart, int rangeEnd, int rangeStep = 1) : MenuElement(text)
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
	bool isChoosable() { return true; };
};


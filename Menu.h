#pragma once
#include <stack>
#include <vector>
#include <mutex>
#include "Component.h"

class Menu;

class MenuIsEmpty : public std::exception {};
class MenuHasNoChosenElement : public std::exception {};

class Menu : Component
{
private:
	std::vector<Component *> elements;
	int chosenElementIndex;
	Menu* (*contentGenerator)();
public:
	// По умолчанию индекс выбранного элемента -1, что приведет к падению программы при некорректной инициализации меню
	Menu() : Component("", true), chosenElementIndex(-1) {};
	~Menu()
	{
		for (auto it : elements)
		{
			delete it;
		}
	};
	std::string str() const;
	void processKeyEvent(KeyEvent keyEvent);
	Menu* addElement(Component* ref);
	auto& getElements() { return elements; }
	Menu* initChosenElementIndex();
	int getChosenElementIndex() { return chosenElementIndex; };
	auto& getContentGenerator() { return contentGenerator; }
};

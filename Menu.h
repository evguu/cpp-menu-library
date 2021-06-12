#pragma once
#include <stack>
#include <vector>
#include <mutex>
#include "Component.h"

using namespace std;

class Menu;

class MenuIsEmpty : public exception {};
class MenuHasNoChosenElement : public exception {};

class Menu : Component
{
private:
	vector<Component *> elements;
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
	string str() const;
	void processKeyEvent(KeyEvent keyEvent);
	Menu* addElement(Component* ref);
	auto& getElements() { return elements; }
	Menu* initChosenElementIndex();
	int getChosenElementIndex() { return chosenElementIndex; };
	auto& getContentGenerator() { return contentGenerator; }
};

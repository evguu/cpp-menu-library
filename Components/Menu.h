#pragma once
#include <stack>
#include <vector>
#include <mutex>
#include <memory>
#include <functional>
#include "Component.h"

class Menu;

class MenuIsEmpty : public std::exception {};
class MenuHasNoChosenElement : public std::exception {};

class Menu : Component
{
private:
	std::vector<std::shared_ptr<Component>> elements;
	int chosenElementIndex;
	std::function<void(Menu*)> contentGenerator;
public:
	// По умолчанию индекс выбранного элемента -1, что приведет к падению программы при некорректной инициализации меню
	Menu() : Component("", true), chosenElementIndex(-1) {};
	std::string str() const;
	void processKeyEvent(KeyEvent keyEvent);
	void addElement(std::shared_ptr<Component> ref);
	auto& getElements() { return elements; }
	void initChosenElementIndex();
	int getChosenElementIndex() { return chosenElementIndex; };
	auto& getContentGenerator() { return contentGenerator; }
};

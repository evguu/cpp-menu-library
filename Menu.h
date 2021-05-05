#pragma once
#include <stack>
#include <vector>
#include <mutex>
#include "MenuElements.h"

using namespace std;

class Menu;

class MenuIsEmpty : public exception {};
class MenuHasNoChosenElement : public exception {};

class Menu
{
private:
	static stack<Menu *> menuStack;
	static bool isLoopRunning;
	static mutex g_lock;
	static const int viewField;
	vector<MenuElement *> elements;
	int chosenElementIndex;
	static void controlLoop();
	static void printLoop();
	Menu* (*contentGenerator)();
public:
	// По умолчанию индекс выбранного элемента -1, что приведет к падению программы при некорректной инициализации меню
	Menu() : chosenElementIndex(-1) {};
	~Menu()
	{
		for (auto it : elements)
		{
			delete it;
		}
	};
	string str() const;
	void processKeyEvent(KeyEvent keyEvent);
	void addElement(MenuElement* ref);
	void addToStack();
	auto& getElements() { return elements; }
	// Вычисляет индекс первого элемента, который можно выбрать и выбирает его
	void initChosenElementIndex();
	int getChosenElementIndex() { return chosenElementIndex; };
	static Menu* getActive() { return menuStack.top(); };
	static void popStack(int popCount = 1);
	static void run()
	{
		thread t1(controlLoop);
		thread t2(printLoop);
		t1.join();
		t2.join();
	}
	static void finish() { isLoopRunning = false; };
	static auto& getMutex() { return g_lock; };
	friend ostream &operator << (ostream &, Menu &);

	auto& getContentGenerator() { return contentGenerator; }
};

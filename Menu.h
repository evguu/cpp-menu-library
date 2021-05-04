#pragma once
#include <stack>
#include <vector>
#include <mutex>
#include "MenuElements.h"

using namespace std;

class Menu;

class Menu
{
private:
	static stack<Menu *> menuStack;
	static bool isLoopRunning;
	static bool hasMenuChanged;
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
	bool recvCommand(KeyEvent keyEvent);
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

	// TODO: Move these 2 methods to MenuElement

	int getNextChoosableElementIndex()
	{
		int result = chosenElementIndex;
		int index = chosenElementIndex + 1;
		vector<MenuElement *>::iterator lim = elements.end();
		bool tmp;

		for (auto it = elements.begin() + chosenElementIndex + 1; it != lim; ++it)
		{
			tmp = (*it)->isChoosable();
			if (tmp)
			{
				result = index;
				break;
			}
			++index;
		}
		return result;
	}

	int getPrevChoosableElementIndex()
	{
		int result = chosenElementIndex;
		int index = 0;
		vector<MenuElement *>::iterator lim = elements.begin() + chosenElementIndex;
		bool tmp;

		for (auto it = elements.begin(); it != lim; ++it)
		{
			tmp = (*it)->isChoosable();
			if (tmp)
			{
				result = index;
			}
			++index;
		}
		return result;
	}
	auto& getContentGenerator() { return contentGenerator; }
};

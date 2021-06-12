#pragma once
#include <stack>
#include <vector>
#include <mutex>
#include "MenuElements.h"

using namespace std;

class Menu;

class MenuIsEmpty : public exception {};
class MenuHasNoChosenElement : public exception {};

class Menu : MenuElement
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
	static void noBlinkOutput(string src);
	Menu* (*contentGenerator)();
public:
	// �� ��������� ������ ���������� �������� -1, ��� �������� � ������� ��������� ��� ������������ ������������� ����
	Menu() : MenuElement(""), chosenElementIndex(-1) {};
	~Menu()
	{
		for (auto it : elements)
		{
			delete it;
		}
	};
	string str() const;
	void processKeyEvent(KeyEvent keyEvent);
	bool isChoosable() { return true; };
	Menu* addElement(MenuElement* ref);
	void addToStack();
	auto& getElements() { return elements; }
	// ��������� ������ ������� ��������, ������� ����� ������� � �������� ���
	Menu* initChosenElementIndex();
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
	static void setConsoleResolution();

	auto& getContentGenerator() { return contentGenerator; }
};

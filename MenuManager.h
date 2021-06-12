#pragma once
#include "Menu.h"

class MenuManager 
{
private:
	static stack<Menu *> menuStack;
	static bool isLoopRunning;
	static mutex g_lock;
	static void controlLoop();
	static void printLoop();
	static void noBlinkOutput(string src);
public:
	static Menu* getActive() { return menuStack.top(); };
	static void popStack(int popCount = 1);
	static void addToStack(Menu* menu);
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
};

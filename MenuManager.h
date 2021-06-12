#pragma once
#include "Menu.h"

class MenuManager 
{
private:
	MenuManager() = delete;
	static stack<Menu *> menuStack;
	static bool areLoopsRunning;
	static mutex loopLock;
	static void logicLoop();
	static void renderLoop();
public:
	static Menu* getActiveMenu() { return menuStack.top(); };
	static void removeFromMenuStack(int popCount = 1);
	static void addToMenuStack(Menu* menu);
	static void runLoops()
	{
		thread t1(logicLoop);
		thread t2(renderLoop);
		t1.join();
		t2.join();
	}
	static void stopLoops() { areLoopsRunning = false; };
	static auto& getLoopLock() { return loopLock; };
};

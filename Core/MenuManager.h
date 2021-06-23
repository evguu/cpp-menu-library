#pragma once
#include "../Components/Menu.h"

class MenuManager 
{
private:
	MenuManager() = delete;
	static std::stack<std::shared_ptr<Menu>> menuStack;
	static bool areLoopsRunning;
	static std::mutex loopLock;
	static void logicLoop();
	static void renderLoop();
public:
	static std::shared_ptr<Menu> getActiveMenu() { return menuStack.top(); };
	static void removeFromMenuStack(int popCount = 1);
	static void addToMenuStack(std::shared_ptr<Menu> menu);
	static void runLoops()
	{
		std::thread t1(logicLoop);
		std::thread t2(renderLoop);
		t1.join();
		t2.join();
	}
	static void stopLoops() { areLoopsRunning = false; };
	static auto& getLoopLock() { return loopLock; };
};

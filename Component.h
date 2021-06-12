#pragma once
#include <string>
#include "StringTree.h"
#include "KeyEvent.h"

class Component
{
public:
	virtual StringTree render() = 0;
	virtual void processKeyEvent(KeyEvent keyEvent) = 0;
protected:
	std::string name;
	bool isFocusable;
};


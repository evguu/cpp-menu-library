#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include "Input.h"

using namespace std;

class MenuElement;

class MenuElement
{
protected:
	string text;
public:
	MenuElement(string text);
	virtual ~MenuElement();

	virtual string str() const = 0;
	virtual void processKeyEvent(KeyEvent keyEvent) = 0;
	virtual bool isChoosable() = 0;
	virtual string getAdditionalText();
	auto& getText();
};



class FolderLeaveAttempt : public exception {};
class FolderProcessedUpDownKeyEvent : public exception {};


class MenuElementFolder : public MenuElement
{
private:
	vector<MenuElement *> elements;
	int chosenElementIndex;
	bool isActive;
public:
	MenuElementFolder(string text) : chosenElementIndex(0), isActive(false), MenuElement(text) {};
	~MenuElementFolder() {
		for (auto it : elements)
		{
			delete it;
		}
	};

	string str() const;
	void processKeyEvent(KeyEvent keyEvent);
	bool isChoosable() { return true; };
	auto& getElements() { return elements; };
	auto& getIsActive() { return isActive; };

	MenuElementFolder* addElement(MenuElement * ref)
	{
		elements.push_back(ref);
		return this;
	}
};

int findNextActiveElementIndex(vector<MenuElement*> elements, int chosenElementIndex);
int findPrevActiveElementIndex(vector<MenuElement*> elements, int chosenElementIndex);

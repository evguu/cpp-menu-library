#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Input.h"

using namespace std;

class MenuElement;
class MenuElementTitle;
class MenuElementSubtitle;
class MenuElementFunctionButton;
class MenuElementEditField;
class MenuElementChoice;

class FolderLeaveAttempt : public exception {};
class FolderProcessedUpDownKeyEvent : public exception {};

/*
	����� ��������� ��� ���� ��������� ����.
*/
class MenuElement
{
protected:
	string text;
public:
	// �������� � ����������
	MenuElement(string text);
	virtual ~MenuElement();

	// ���������
	virtual string str() const = 0;
	virtual bool recvCommand(KeyEvent keyEvent) = 0;
	virtual bool isChoosable() = 0;
	virtual string getAdditionalText();
	auto& getText();
};

class MenuElementTitle : public MenuElement
{
public:
	// �������� � ����������
	MenuElementTitle(string text) : MenuElement(text) {};
	~MenuElementTitle() {};

	// ���������
	string str() const;
	bool recvCommand(KeyEvent keyEvent) { return false; };
	bool isChoosable() { return false; };
};

class MenuElementSubtitle : public MenuElement
{
public:
	// �������� � ����������
	MenuElementSubtitle(string text) : MenuElement(text) {};
	~MenuElementSubtitle() {};

	// ���������
	string str() const;
	bool recvCommand(KeyEvent keyEvent) { return false; };
	bool isChoosable() { return false; };
};

class MenuElementFunctionButton : public MenuElement
{
private:
	void(*func)();
public:
	// �������� � ����������
	MenuElementFunctionButton(string text, void(*func)()) : MenuElement(text), func(func) {};
	~MenuElementFunctionButton() {};

	// ���������
	string str() const;
	bool recvCommand(KeyEvent keyEvent);
	bool isChoosable() { return true; };
	auto& getFunc() { return func; };
};

class MenuElementEditField : public MenuElement
{
private:
	string input;
	bool isTextHidden;
	string allowedSymbols;
	int maxLength;
	int minLength;
public:
	// �������� � ����������
	MenuElementEditField(string text, bool isTextHidden = false, string allowedSymbols = "", int minLength = 0, int maxLength = 0) :
		MenuElement(text), input(""), isTextHidden(isTextHidden), allowedSymbols(allowedSymbols), minLength(minLength), maxLength(maxLength) {};
	~MenuElementEditField() {};

	// ���������
	string str() const;
	string& getInput();
	bool recvCommand(KeyEvent keyEvent);
	bool isChoosable() { return true; };
	string getAdditionalText() override
	{
		return "        �� ����� " + to_string(minLength) + " ��������.\n"
			"        ��������� �������: " + allowedSymbols;
	}
};

class MenuElementChoice : public MenuElement
{
public:
	static const string noChoicesFoundMessage;
private:
	vector<string> options;
	int activeOption = 0;
public:
	MenuElementChoice(string text, vector<string> options) : MenuElement(text), options(options) {};
	MenuElementChoice(string text, int rangeStart, int rangeEnd, int rangeStep = 1) : MenuElement(text)
	{
		for (int i = rangeStart; i < rangeEnd; i += rangeStep)
		{
			options.push_back(to_string(i));
		}
	};

	~MenuElementChoice() {};

	string str() const;

	// ���� ������ �� ������� (������ ������ ����), ���������� MenuElementChoice::noChoicesFoundMessage.
	string getChoice()
	{
		if (options.size())
		{
			return options[activeOption];
		}
		else
		{
			return noChoicesFoundMessage;
		}
	};
	auto& getOptions() { return options; };
	auto& getActiveOption() { return activeOption; };
	bool recvCommand(KeyEvent keyEvent);
	bool isChoosable() { return true; };
};

class MenuElementFolder : public MenuElement
{
private:
	vector<MenuElement *> elements;
	int chosenElementIndex;
	bool isActive;
public:
	// �������� � ����������
	MenuElementFolder(string text) : chosenElementIndex(0), isActive(false), MenuElement(text) {};
	~MenuElementFolder() {
		for (auto it : elements)
		{
			delete it;
		}
	};

	// ���������
	string str() const;
	bool recvCommand(KeyEvent keyEvent);
	bool isChoosable() { return true; };
	auto& getElements() { return elements; };
	auto& getIsActive() { return isActive; };
};
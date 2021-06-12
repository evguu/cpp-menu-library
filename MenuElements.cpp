#include "MenuElements.h"
#include "Input.h"
#include <ctime>
#include <sstream>

MenuElement::MenuElement(string text) : text(text)
{
};

MenuElement::~MenuElement()
{
};

string MenuElement::getAdditionalText()
{
	return "";
};

auto& MenuElement::getText()
{
	return this->text;
};

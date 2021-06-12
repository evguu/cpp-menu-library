#include "Component.h"
#include "Input.h"
#include <ctime>
#include <sstream>

Component::Component(string text, bool isFocusable) : text(text), isFocusable(isFocusable)
{
};

Component::~Component()
{
};

string Component::getAdditionalText()
{
	return "";
};

string Component::getText() const
{
	return text;
};

bool Component::getIsFocusable() const
{
	return isFocusable;
};

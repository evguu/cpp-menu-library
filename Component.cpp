#include "Component.h"
#include "Input.h"
#include <ctime>
#include <sstream>

Component::Component(std::string text, bool isFocusable) : text(text), isFocusable(isFocusable)
{
};

Component::~Component()
{
};

std::string Component::getAdditionalText()
{
	return "";
};

std::string Component::getText() const
{
	return text;
};

bool Component::getIsFocusable() const
{
	return isFocusable;
};

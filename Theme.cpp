#include "Theme.h"
std::vector<std::string> Theme::themes = { "0F", "07", "87", "78", "70", "F0" };
int Theme::currentIndex = 4;

void Theme::applyNext()
{
	advanceCurrentIndex();
	applyCurrent();
}

void Theme::advanceCurrentIndex()
{
	++currentIndex;
	currentIndex %= themes.size();
}

void Theme::applyCurrent()
{
	apply(getCurrent());

}

void Theme::apply(std::string theme)
{
	std::string command = "color ";
	command += theme;
	system(command.c_str());
}

std::string Theme::getCurrent()
{
	return themes[currentIndex];
}
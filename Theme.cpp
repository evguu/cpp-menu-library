#include "Theme.h"
std::vector<std::string> themes = { "0F", "07", "87", "78", "70", "F0" };
int currentThemeIndex = 4;

void applyNextAvailableTheme()
{
	advanceCurrentThemeIndex();
	applyCurrentTheme();
}

void advanceCurrentThemeIndex()
{
	++currentThemeIndex;
	currentThemeIndex %= themes.size();
}

void applyCurrentTheme()
{
	applyTheme(getCurrentTheme());
}

void applyTheme(std::string theme)
{
	std::string command = "color ";
	command += theme;
	system(command.c_str());
}

std::string getCurrentTheme()
{
	return themes[currentThemeIndex];
}
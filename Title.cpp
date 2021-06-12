#include "Title.h"

Title::Title(std::string text) : Component(text, false)
{
};

std::string Title::str() const
{
	std::stringstream ss;
	ss << "-< " << text << " >- " << std::endl;
	return ss.str();
}

void Title::processKeyEvent(KeyEvent keyEvent)
{
};


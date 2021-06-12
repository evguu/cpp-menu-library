#include "Title.h"

Title::Title(std::string text) : MenuElement(text, false)
{
};

std::string Title::str() const
{
	std::stringstream ss;
	ss << "-< " << text << " >- " << endl;
	return ss.str();
}

void Title::processKeyEvent(KeyEvent keyEvent)
{
};


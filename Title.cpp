#include "Title.h"

Title::Title(std::string text) : MenuElement(text)
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

bool Title::isChoosable()
{
	return false;
};

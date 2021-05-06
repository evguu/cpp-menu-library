#include "LML.h"
#include "Theme.h"

int main()
{
	Console::hideCursor(); 
	Console::fixEncoding(); 
	Menu::setConsoleResolution();
	Theme::applyCurrent();

	START(#main);
	BUTTON("a", []() {});
	FOLDER(@main.misc, "Дополнительные функции");
	FOLDERED_BUTTON(@main.misc, "Сменить тему", Theme::applyNext);
	for (int i = 0; i < 10; i++)
	FOLDERED_BUTTON(@main.misc, "Выйти из программы", []() { Menu::finish(); });
	for (int i = 0; i < 50; i++)
	BUTTON("b", []() {});
	END(#main);
	MENU(#main)->addToStack();

	Menu::run(); 
	Console::sayGoodbye();
}
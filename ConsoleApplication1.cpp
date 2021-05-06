#include "LML.h"
#include "Theme.h"


int main()
{
	applyCurrentTheme();

	Utils::hideConsoleCursor(); 
	Utils::setCorrectEncoding(); 
	Menu::setConsoleResolution();

	LM_DECL_START(#main);
	LM_ADD_BUTTON("a", []() {});
	LM_ADD_FD(@main.misc, "Дополнительные функции");
	LM_FD_BUTTON(@main.misc, "Сменить тему", applyNextAvailableTheme);
	for (int i = 0; i < 10; i++)
	LM_FD_BUTTON(@main.misc, "Выйти из программы", []() { Menu::finish(); });
	for (int i = 0; i < 50; i++)
	LM_ADD_BUTTON("b", []() {});
	LM_DECL_END(#main);
	LM_ID(#main)->addToStack();

	Menu::run(); 
	system("cls"); 
	cout << "Выход из программы..." << endl;
}
#include "LML.h"

vector<string> themes = { "0F", "07", "87", "78", "70", "F0" }; 
int activeTheme = 4; 

int main()
{
	system(("color "s + themes[activeTheme]).c_str());

	Utils::hideConsoleCursor(); 
	Utils::setCorrectEncoding(); 
	Menu::setConsoleResolution();

	LM_DECL_START(#main);
	LM_ADD_BUTTON("a", []() {});
	LM_ADD_FD(@main.misc, "Дополнительные функции");
	LM_FD_BUTTON(@main.misc, "Сменить тему", []() {
		system(("color "s + themes[(++activeTheme) % themes.size()]).c_str());
	});
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
#include "Fun.h"

vector<string> themes = { "0F", "07", "87", "78", "70", "F0" }; 
int activeTheme = 4; 

int main()
{
	system(("color "s + themes[activeTheme]).c_str());

	SETUP_START;

	LM_DECL_START(#main);
	LM_ADD_FD(@main.misc, "Дополнительные функции");
	LM_FD_BUTTON(@main.misc, "Сменить тему", []() {
		system(("color "s + themes[(++activeTheme) % themes.size()]).c_str());
	});
	LM_FD_BUTTON(@main.misc, "Выйти из программы", []() { Menu::finish(); });
	LM_DECL_END(#main);
	LM_ID(#main)->addToStack();

	SETUP_END;
}
#include "LML.h"
#include "Theme.h"

int main()
{
	Console::hideCursor();
	Console::fixEncoding();
	Menu::setConsoleResolution();
	Theme::applyCurrent();


	MD_START("#main")
		ADD(Title, "Проверка работы цепного добавления элементов")
		ADD(FunctionButton, "Добавить лекарство", []() { getMenu("#addMedicine")->addToStack(); })
		ADD(FunctionButton, "Выйти", []() { Menu::finish(); })
		MD_END;

	MD_START("#addMedicine")
		ADD(Title, "Добавить лекарство")
		ADD_FOLDER("@addMedicine.main", "Основные функции",
			ADD(EditField, "Имя")
			ADD(FunctionButton, "Назад", []() { Menu::popStack(); }))
		MD_END;

	getMenu("#main")->addToStack();

	Menu::run();
	Console::sayGoodbye();
}

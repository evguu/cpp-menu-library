#include "LML.h"
#include "Theme.h"

int main()
{
	Console::hideCursor();
	Console::fixEncoding();
	Menu::setConsoleResolution();
	Theme::applyCurrent();


	MD_START("#main")
		ADD(Title, "Проверка работы цепного добавления элементов")$
		ADD(FunctionButton, "Субменю", []() { getMenu("#sub")->addToStack(); })$
		ADD(FunctionButton, "Выйти", []() { Menu::finish(); })$
		MD_END;

	MD_START("#sub")
		ADD(Title, "Субменю")$
		ADD_FOLDER("@sub.main", "Основные функции",
			ADD(EditField, "Пустое поле")$
			ADD(EditField, "Заранее заполненное поле") e->getInput() = "Данные"; $
			ADD(FunctionButton, "Назад", []() { Menu::popStack(); })$)
		MD_END;

	getMenu("#main")->addToStack();

	Menu::run();
	Console::sayGoodbye();
}

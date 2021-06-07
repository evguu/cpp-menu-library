#include "LML.h"
#include "Theme.h"

#include "NewMenuMacros.h"

int main()
{
	Console::hideCursor();
	Console::fixEncoding();
	Menu::setConsoleResolution();
	Theme::applyCurrent();


	getMenuWithGeneratorMigration("#main")->getContentGenerator() = []()
	{
		return getMenuWithGeneratorMigration("#main")->
			addElement(new MenuElementTitle("Проверка работы цепного добавления элементов"))->
			addElement(new MenuElementFunctionButton("Тестовая кнопка", []() {}))->
			initChosenElementIndex();
	};
	getMenu("#main")->getContentGenerator()();
	getMenu("#main")->addToStack();

	START(#addMedicine);
	TITLE("Добавить лекарство");

	FOLDER(@addMedicine.main, "Основные функции");
	FOLDERED_FIELD(@addMedicine.main, "Имя");
	FOLDERED_BUTTON(@addMedicine.main, "Назад", []() {Menu::popStack(); });

	END(#addMedicine);


	START(#editMedicine);
	TITLE("Редактировать первое доступное лекарство");
	FOLDER(@editMedicine.main, "Основные функции");
	FOLDERED_BUTTON(@editMedicine.main, "Назад", []() {Menu::popStack(); });

	END(#editMedicine);


	Menu::run();
	Console::sayGoodbye();
}

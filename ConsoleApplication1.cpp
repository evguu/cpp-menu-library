#include "LML.h"
#include "Theme.h"

#include "NewMenuMacros.h"

int main()
{
	Console::hideCursor();
	Console::fixEncoding();
	Menu::setConsoleResolution();
	Theme::applyCurrent();


	newMenu("#main")->getContentGenerator() = []()
	{
		return getMenuForGenerator("#main")->
			addElement(new MenuElementTitle("Проверка работы цепного добавления элементов"))->
			addElement(new MenuElementFunctionButton("Добавить лекарство", []() { getMenu("#addMedicine")->addToStack(); }))->
			addElement(new MenuElementFunctionButton("Выйти", []() { Menu::finish(); }))->
			initChosenElementIndex();
	};
	getMenu("#main")->getContentGenerator()()->addToStack();

	newMenu("#addMedicine")->getContentGenerator() = []()
	{
		return getMenuForGenerator("#addMedicine")->
			addElement(new MenuElementTitle("Добавить лекарство"))->
			addElement(newFD("@addMedicine.main", "Основные функции")->
				addElement(new MenuElementEditField("Имя"))->
				addElement(new MenuElementFunctionButton("Назад", []() { Menu::popStack(); })))->
			initChosenElementIndex();
	};
	getMenu("#addMedicine")->getContentGenerator()();

	Menu::run();
	Console::sayGoodbye();
}

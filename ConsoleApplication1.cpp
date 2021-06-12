#include "LML.h"
#include "Theme.h"

#include "Title.h"
#include "Text.h"
#include "Button.h"
#include "Choice.h"
#include "Field.h"

int main()
{
	Console::hideCursor();
	Console::fixEncoding();
	Menu::setConsoleResolution();
	Theme::applyCurrent();


	MD_START("#main")
		->addElement(new Title("Проверка работы цепного добавления элементов"))
		->addElement(new Button("Субменю", []() { getMenu("#sub")->addToStack(); }))
		->addElement(new Button("Выйти", []() { Menu::finish(); }))
		MD_END;

	MD_START("#sub")
		->addElement(new Title("Субменю"))
		->addElement(new Field("Пустое поле"))
		->addElement([]() {auto e = new Field("Заранее заполненное поле"); e->getInput() = "Данные"; return e; }())
		->addElement(new Button("Назад", []() { Menu::popStack(); }))
		MD_END;

	getMenu("#main")->addToStack();

	Menu::run();
	Console::sayGoodbye();
}

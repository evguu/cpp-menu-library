#include "LML.h"
#include "MenuManager.h"
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
	MenuManager::setConsoleResolution();
	Theme::applyCurrent();


	MD_START("#main")
		->addElement(new Title("Проверка работы цепного добавления элементов"))
		->addElement(new Button("Субменю", []() { MenuManager::addToStack(getMenu("#sub")); }))
		->addElement(new Button("Выйти", []() { MenuManager::finish(); }))
		MD_END;

	MD_START("#sub")
		->addElement(new Title("Субменю"))
		->addElement(new Field("Пустое поле"))
		->addElement([]() {auto e = new Field("Заранее заполненное поле"); e->getInput() = "Данные"; return e; }())
		->addElement(new Button("Назад", []() { MenuManager::popStack(); }))
		MD_END;

	MenuManager::addToStack(getMenu("#main"));

	MenuManager::run();
	Console::sayGoodbye();
}

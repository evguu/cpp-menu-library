#include "LML.h"
#include "Theme.h"

int main()
{
	Console::fixEncoding();
	Display::setMode(Display::modeMenu);
	Theme::applyCurrent();

	MD_START("#main")
		ADD(Title, "Главное меню")$
		ADD(Button, "Субменю", []() { MenuManager::addToMenuStack(getMenu("#sub")); })$
		ADD(DialogButton, "Тестовый диалог", Dialog::fromVoid([]() {std::cout << "Все в порядке!\n"; }))$
		ADD(Button, "Выйти", []() { MenuManager::stopLoops(); })$
		MD_END;

	MD_START("#sub")
		ADD(Title, "Субменю")$
		ADD(Field, "Пустое поле")$
		ADD(Field, "Заранее заполненное поле") e->getInput() = "Данные"; $
		ADD(Button, "Назад", []() { MenuManager::removeFromMenuStack(); })$
		MD_END;

	MenuManager::addToMenuStack(getMenu("#main"));

	MenuManager::runLoops();
	Console::sayGoodbye();
}

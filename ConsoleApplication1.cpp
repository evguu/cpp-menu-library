#include "LML.h"
#include "Theme.h"

#include "Executable.h"

int main()
{
	Console::fixEncoding();
	Display::setMode(Display::standardMode);
	Theme::applyCurrent();

	MD_START("#main")
		ADD(Title, "Главное меню")$
		ADD(Button, "Субменю", Executable::from([]() { MenuManager::addToMenuStack(getMenu("#sub")); }))$
		//ADD(Button, "Тестовый диалог", DialogDecorator::apply(Executable::from([]() {std::cout << "Все в порядке!\n"; })))$
		//ADD(Button, "Выйти", Executable::from([]() { MenuManager::stopLoops(); }))$
		MD_END;

	MD_START("#sub")
		ADD(Title, "Субменю")$
		ADD(Field, "Пустое поле")$
		ADD(Field, "Заранее заполненное поле") e->getInput() = "Данные"; $
		//ADD(Button, "Назад", Executable::from([]() { MenuManager::removeFromMenuStack(); }))$
		MD_END;

	MenuManager::addToMenuStack(getMenu("#main"));

	MenuManager::runLoops();
	Console::sayGoodbye();
}

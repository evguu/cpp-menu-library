#include "LML.h"

Executable* contextDialog()
{
	static int context = 0;
	return DialogDecorator::apply(Executable::from([&]() {std::cout << "Ты нажал уже " << ++context << " раз. Остановись!" << std::endl; }));
}

int main()
{
	Console::fixEncoding();
	Console::setMode(Console::standardMode);
	Display::setBuffer(new char[Console::standardMode.getColumns()*Console::standardMode.getRows()]);
	Theme::applyCurrent();

	MD_START("#main")
		ADD(Title, "Главное меню")$
		ADD(Button, "Субменю", Executable::from([]() { MenuManager::addToMenuStack(getMenu("#sub")); }))$
		ADD(Button, "Простой диалог", DialogDecorator::apply(Executable::from([]() {std::cout << "Все в порядке!\n"; })))$
		ADD(Button, "Диалог с контекстом", contextDialog())$
		ADD(Button, "Выйти", Executable::from([]() { MenuManager::stopLoops(); }))$
		MD_END;

	MD_START("#sub")
		ADD(Title, "Субменю")$
		ADD(Field, "Пустое поле")$
		ADD(Field, "Заранее заполненное поле") e->getInput() = "Данные"; $
		ADD(Button, "Диалог с тем же контекстом", contextDialog())$
		ADD(Button, "Назад", Executable::from([]() { MenuManager::removeFromMenuStack(); }))$
		MD_END;

	MenuManager::addToMenuStack(getMenu("#main"));

	MenuManager::runLoops();
	Console::sayGoodbye();
}

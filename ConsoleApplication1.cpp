#include "LML.h"
#include <functional>

std::function<void()> contextDialog()
{
	static int context = 0;
	return DialogDecorator::apply([&]() {std::cout << "Ты нажал уже " << ++context << " раз. Остановись!" << std::endl; });
}

Menu* mainMenu()
{
	return MenuStream("#main")
		ADD(Title, "Главное меню")$
		ADD(Button, "Субменю", []() { MenuManager::addToMenuStack(getMenu("#sub")); })$
		ADD(Button, "Простой диалог", DialogDecorator::apply([]() {std::cout << "Все в порядке!\n"; }))$
		ADD(Button, "Диалог с контекстом", contextDialog())$
		ADD(Button, "Выйти", []() { MenuManager::stopLoops(); })$
		.init();
}

Menu* subMenu()
{
	return MenuStream("#sub")
		ADD(Title, "Субменю")$
		ADD(Field, "Пустое поле")$
		ADD(Field, "Заранее заполненное поле") e->getInput() = "Данные"; $
		ADD(Button, "Диалог с тем же контекстом", contextDialog())$
		ADD(Button, "Назад", []() { MenuManager::removeFromMenuStack(); })$
		.init();
}

int main()
{
	Console::fixEncoding();
	Console::setMode(Console::standardMode);
	Display::setBuffer(new char[Console::standardMode.getColumns()*Console::standardMode.getRows()]);
	Theme::applyCurrent();

	newMenu("#main")->getContentGenerator() = mainMenu;
	newMenu("#sub")->getContentGenerator() = subMenu;

	MenuManager::addToMenuStack(getMenu("#main"));

	MenuManager::runLoops();
	Console::sayGoodbye();
}

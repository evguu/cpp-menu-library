#include "LML.h"

std::function<void()> contextDialog()
{
	static int context = 0;
	return DialogDecorator::apply([&]() {std::cout << "Ты нажал уже " << ++context << " раз. Остановись!" << std::endl; });
}

void mainMenu(std::shared_ptr<Menu> m)
{
	MenuStream(m)
		ADD(Title, "Главное меню")$
		ADD(Button, "Субменю", []() { MenuManager::addToMenuStack(getMenu("#sub")); })$
		ADD(Button, "Простой диалог", DialogDecorator::apply([]() {std::cout << "Все в порядке!\n"; }))$
		ADD(Button, "Диалог с контекстом", contextDialog())$
		ADD(Button, "Выйти", []() { MenuManager::stopLoops(); })$
		.init();
}


void subMenu(std::shared_ptr<Menu> m)
{
	std::shared_ptr<Menu> m1 = std::make_shared<Menu>();
	[](std::shared_ptr<Menu> m)
	{
		MenuStream(m)
			ADD(Title, "Субменю")$
			ADD(Field, "Пустое поле")$
			ADD(Field, "Заранее заполненное поле") e->getInput() = "Данные"; $
			.init();
	}(m1);

	std::shared_ptr<Menu> m2 = std::make_shared<Menu>();
	[](std::shared_ptr<Menu> m)
	{
		MenuStream(m)
			ADD(Title, "Субменю")$
			ADD(Field, "Пустое поле")$
			ADD(Field, "Заранее заполненное поле") e->getInput() = "Данные"; $
			.init();
	}(m2);

	MenuStream(m)
		ADD(Title, "Субменю")$
		ADD(Field, "Пустое поле")$
		ADD(Field, "Заранее заполненное поле") e->getInput() = "Данные"; $
		ADD(Button, "Диалог с тем же контекстом", contextDialog())$
		ADD(Button, "Назад", []() { MenuManager::removeFromMenuStack(); })$
		(std::reinterpret_pointer_cast<Component>(m1))
		(std::reinterpret_pointer_cast<Component>(m2))
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

#include "LML.h"
#include "Transaction.h"

void mainMenu(std::shared_ptr<Menu> m)
{
	static Transaction<int> transaction{std::make_shared<int>(10)};

	MenuStream(m)
		ADD(Title, "Главное меню")$
		(std::make_shared<Button>("Текущее значение транзакции", DialogDecorator::apply([&]() { std::cout << *(transaction.getPtr()) << std::endl; })))
		(std::make_shared<Button>("Поднять значение транзакции", [&]() 
			{ 
				auto ptr = transaction.getPtr();
				++*(ptr);
				transaction.setPtr(ptr); 
			}
		))
		(std::make_shared<Button>("Опустить значение транзакции", [&]()
			{
				auto ptr = transaction.getPtr();
				--*(ptr);
				transaction.setPtr(ptr);
			}
		))
		(std::make_shared<Button>("Сохранить значение транзакции", [&]() { transaction.commit(); }))
		(std::make_shared<Button>("Откатить значение транзакции", [&]() { transaction.rollback(); }))
		ADD(Button, "Выйти", []() { MenuManager::stopLoops(); })$
		.init();
}

int main()
{
	Console::fixEncoding();
	Console::setMode(Console::standardMode);
	Theme::applyCurrent();

	newMenu("#main")->getContentGenerator() = mainMenu;

	MenuManager::addToMenuStack(getMenu("#main"));

	MenuManager::runLoops();
	Console::sayGoodbye();
}

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

	/*
	7. Разработать набор классов (минимум 5 классов) по теме «Тестирование
	знаний студентов», включающий обязательно следующие классы: 
	«Тест» (название теста, тема теста, перечень вопросов, перечень полученных ответов), 
	«Пользователь» (ФИО, факультет, номер группы), 
	«Ответ» (дата выполнения теста, ФИО выполнившего тест).

	Использовать smart-указатели для создания программы учета полученных ответов на тесты.
	
	Реализовать механизм транзакций, который позволит откатывать изменения, внесенные в ответ. 
	Все классы должны быть параметризированными и содержать функции получения и изменения всех полей.
	Программа должна обеспечивать вывод итоговой информации о выполнении тестов. 
	*/

	MenuManager::addToMenuStack(getMenu("#main"));

	MenuManager::runLoops();
	Console::sayGoodbye();
}

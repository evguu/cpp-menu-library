﻿#include "LML.h"
#include "Transaction.h"
#include "Student.h"

void refreshMenu(std::string str)
{
	auto menu = getMenu(str);
	int pos = menu->getChosenElementIndex();
	menu->getElements().clear();
	menu->getContentGenerator()(menu);
	if (pos != -1)
	menu->getChosenElementIndex() = pos;
}

void testMenu(std::shared_ptr<Menu> m)
{
	static Transaction<int> transaction{ std::make_shared<int>(10) };

	MenuStream(m)
		ADD(Title, "Транзакции")$
		(std::make_shared<Text>("Текущее значение транзакции: " + std::to_string(*(transaction.getPtr())) + 
			(( *(transaction.getPtr()) == *(transaction.getSafePtr()) )?"":"*")
		))
		(std::make_shared<Button>("Поднять значение транзакции", [&]() 
			{ 
				auto ptr = transaction.getPtr();
				++*(ptr);
				transaction.setPtr(ptr); 

				refreshMenu("#test");
			}
		))
		(std::make_shared<Button>("Опустить значение транзакции", [&]()
			{
				auto ptr = transaction.getPtr();
				--*(ptr);
				transaction.setPtr(ptr);

				refreshMenu("#test");
			}
		))
		(std::make_shared<Button>("Сохранить значение транзакции", [&]()
			{ 
				transaction.commit(); 

				refreshMenu("#test");
			}
		))
		(std::make_shared<Button>("Откатить значение транзакции", [&]() 
			{
				transaction.rollback(); 

				refreshMenu("#test");
			}
		))
		.init();
}


std::shared_ptr<Menu> m1 = std::make_shared<Menu>(1);

void mainMenu(std::shared_ptr<Menu> m)
{
	MenuStream(m)
		ADD(Title, "Главное меню")$
		(std::reinterpret_pointer_cast<Component>(getMenu("#test")))
		ADD(Button, "Выйти", []() { MenuManager::stopLoops(); })$
		.init();
}

int main()
{
	Console::fixEncoding();
	Console::setMode(Console::standardMode);
	Theme::applyCurrent();

	newMenu("#main")->getContentGenerator() = mainMenu;
	newMenu("#test")->getContentGenerator() = testMenu;
	refreshMenu("#test");
	getMenu("#test")->getTabOffset() = 1;

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

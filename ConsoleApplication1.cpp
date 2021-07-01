﻿#include "LML.h"
#include "Transaction.h"
#include "Test.h"
#include "Student.h"
#include <map>

void refreshMenu(std::string str);
void refreshMenu(std::shared_ptr<Menu> menu);

void refreshMenu(std::string str)
{
	auto menu = getMenu(str);
	refreshMenu(menu);
}
void refreshMenu(std::shared_ptr<Menu> menu)
{
	int pos = menu->getChosenElementIndex();
	menu->getElements().clear();
	menu->getContentGenerator()(menu);
	if (pos != -1)
		menu->getChosenElementIndex() = pos;
}


std::vector<Test> tests = {
	{
		"Тест по животным", "Биология", 
			{
				{
					"Кто из этих животных кукарекает?",
					{
						{"Петух", true},
						{"Коза", false},
						{"Корова", false}
					}
				},
				{
					"Кто из них относится к кошачьим?",
					{
						{"Кот", true},
						{"Кошка", true},
						{"Собака", false}
					}
				},
			}
	},
	{
		"Тест по числам", "Математика",
			{
				{
					"1+1?",
					{
						{"2", true},
						{"3", false},
						{"4", false}
					}
				},
				{
					"Выберите цифры.",
					{
						{"1", true},
						{"0", true},
						{"Буква", false}
					}
				},
			}
	}
};


void intTransactionMG(std::shared_ptr<Menu> m)
{
	static Transaction<int> transaction{ std::make_shared<int>(10) };

	MenuStream(m)
		(MSH(Text, "Текущее значение транзакции: " + std::to_string(*(transaction.getPtr())) +
			(( *(transaction.getPtr()) == *(transaction.getSafePtr()) )?"":"*")
		))
		(MSH(Button, "Поднять значение транзакции", [=]()
			{ 
				auto ptr = transaction.getPtr();
				++*(ptr);
				transaction.setPtr(ptr);

				refreshMenu(m);
			}
		))
		(MSH(Button, "Опустить значение транзакции", [=]()
			{
				auto ptr = transaction.getPtr();
				--*(ptr);
				transaction.setPtr(ptr);

				refreshMenu(m);
			}
		))
		(MSH(Button, "Сохранить значение транзакции", [=]()
			{ 
				transaction.commit(); 

				refreshMenu(m);
			}
		))
		(MSH(Button, "Откатить значение транзакции", [=]() 
			{
				transaction.rollback(); 
				
				refreshMenu(m);
			}
		))
		.init();
}

void mainMG(std::shared_ptr<Menu> m)
{
	std::shared_ptr<Menu> m1 = std::make_shared<Menu>("Транзакции над числом", 1);
	m1->getContentGenerator() = intTransactionMG;
	refreshMenu(m1);

	MenuStream(m)
		(std::reinterpret_pointer_cast<Component>(m1))
		(MSH(Button, "Выйти", []() { MenuManager::stopLoops(); }))
		.init();
}

int main()
{
	Console::fixEncoding();
	Console::setMode(Console::standardMode);
	Theme::applyCurrent();

	newMenu("Главное меню", "#main")->getContentGenerator() = mainMG;

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

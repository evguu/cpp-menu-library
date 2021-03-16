#include <iostream>
#include "CMMStack.h"
#include "Client.h"
#include "Contract.h"
#include "InsuranceService.h"

vector<string> themes = { "0F", "07", "87", "78", "70", "F0" };
int activeTheme = 4;

vector<Client> clients;
vector<InsuranceService> services;
vector<Contract> contracts;

int main()
{
	// Запланированные исключения для обработки:

	/*
		1. bad_alloc << DONE (см. макросы)
		2. Попытка запустить программу с меню без выбираемых элементов -- 235, с пустым меню -- 234  << DONE
		3. Обращение к несуществующему LM_ID -- unknownMenuIdentifierException << DONE

		4. Исключение в конструкторе договора, клиент не имеет права на получение услуги -- permCheckFailedException

		5. Попытка снять последнее меню со стека -- 969 << DONE

		! Идея: доделать папки, используя исключения для возврата сигнала! << DONE -- 666, 776, 778

		Не забыть собственную функцию завершения. << DONE
	*/

	Utils::setupResolution();
	Utils::setupEncoding();
	system(("color "s + themes[activeTheme]).c_str());

	set_terminate([]() { LM_CON_SHARE_START; cout << "Произошло аварийное завершение программы. Я тоже не знаю, почему. Отладчик в помощь!" << endl; LM_CON_SHARE_END; abort(); });

	LM_DECL_START(main);
	LM_ADD_TITLE("Лабораторная 2. Использование исключений.");
	LM_ADD_FD(USER, "Управление клиентами");
	LM_FD_BUTTON(USER, "Добавление клиентов", []() {LM_ID(add_user)->reset(); LM_ID(add_user)->addToStack(); });
	LM_FD_BUTTON(USER, "Просмотреть клиентов", []() {
		LM_CON_SHARE_START;
		if (!clients.size()) 
		{
			cout << "Список пуст, добавьте пользователя." << endl; 
		} 
		for (auto it : clients) 
		{ 
			cout << it.getName() << "[" << it.getTrustLevel() << "]" << endl;
		}
		LM_CON_SHARE_END; 
	});
	LM_ADD_FD(INSU, "Управление страховыми услугами");
	LM_FD_BUTTON(INSU, "Выбор страхового плана", []() {LM_ID(choose_insurance_service)->addToStack(); });
	LM_ADD_FD(ADDI, "Дополнительные функции");
	LM_FD_BUTTON(ADDI, "Сменить тему", []() {
		system(("color "s + themes[(++activeTheme)%themes.size()]).c_str()); 
	});
	LM_FD_BUTTON(ADDI, "Крашнуть программу", []() {/* Кастомный терминатор не работает, потому что VS -- ересь! */ terminate(); });
	LM_FD_BUTTON(ADDI, "Выйти из программы", []() {Menu::finish(); });
	LM_DECL_END;
	LM_ID(main)->addToStack();

	LM_DECL_START(add_user);
	LM_ADD_TITLE("Выбор пользователей");
	LM_ADD_FD(1, "Ввод данных");
	LM_FD_FIELD(1, "Имя клиента");
	LM_FD_CHOICE(1, "Уровень доверия", { "Низкий", "Средний", "Высокий" });
	/*LM_ADD_BUTTON("Добавить клиента", []() {
		clients.push_back({
			((MenuElementEditField*)LM_FD(1)[0])->getInput();
			}); 
	});*/
	LM_ADD_BUTTON("Отмена", []() {Menu::popStack(); });
	LM_DECL_END;
	
	LM_DECL_START(choose_insurance_service);
	LM_ADD_TITLE("Выбор страхового плана");
	LM_ADD_BUTTON("Назад", []() {Menu::popStack(); });
	LM_DECL_END;

	//LM_ID(nonexistent_id); // Раскомментировать для исключения 3.
	
	Menu::run();
	system("cls");
	cout << "Выход из программы..." << endl;
}
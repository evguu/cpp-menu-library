#include <iostream>
#include "CMMStack.h"
#include "Client.h"
#include "InsuranceService.h"

int main()
{
	// Запланированные исключения для обработки:

	/*
		1. bad_alloc
		2. Попытка запустить программу с меню без выбираемых элементов -- unusableMenuException
		3. Обращение к несуществующему LM_ID -- unknownMenuIdentifierException
		4. Исключение в конструкторе договора, клиент не имеет права на получение услуги -- permCheckFailedException
		5. Попытка снять последнее меню со стека -- emptyMenuStackException

		6, При добавлении папки в папку кидать badArchitechtureException

		! Идея: доделать папки, используя исключения для возврата сигнала! << DONE

		Не забыть собственную функцию завершения.
	*/

	Utils::setupResolution();
	Utils::setupEncoding();

	LM_DECL_START(main);
	LM_ADD_TITLE("Лабораторная 2. Использование исключений.");
	LM_ADD_BUTTON("Управление пользователями", []() {LM_ID(Client_DataControl)->addToStack(); });
	LM_ADD_BUTTON("Управление страховыми услугами", []() {LM_ID(InsuranceService_DataControl)->addToStack(); });

	LM_ADD_FD(TEST, "Авторизация");
	LM_FD_CHOICE(TEST, "Имя сотрудника", { "Пидор", "Лысый", "Рыжий" });
	LM_FD_CHOICE(TEST, "Выбор2", { "2", "3", "4" });

	LM_ADD_FD(TEST2, "Управление");
	LM_FD_CHOICE(TEST2, "Выбор1", { "2", "3", "4" });
	LM_FD_BUTTON(TEST2, "Кнопка", []() {LM_CON_SHARE_START; cout << "КНОПКА НАЖАТА!" << endl; LM_CON_SHARE_END; })
	LM_FD_CHOICE(TEST2, "Выбор2", { "2", "3", "4" });

	LM_ADD_TITLE("Конец меню");

	LM_DECL_END;
	LM_ID(main)->addToStack();
	
	AI::Client();
	AI::InsuranceService();

	Menu::run();
	system("cls");
	cout << "Выход из программы..." << endl;
	cout << getMenu("");
}
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

void MENU_make_deal()
{
	LM_DECL_START(make_deal);
	LM_ADD_TITLE("Заключение договора");
	LM_ADD_FD(3, "Ввод данных");
	vector <string> a, b;
	for (auto it : clients)
	{
		a.push_back(it.getName() + " [" + to_string(it.getTrustLevel()) + "]");
	}
	for (auto it : services)
	{
		b.push_back(it.getName() + " [" + to_string(it.getRequiredTrustLevel()) + "]");
	}
	LM_FD_CHOICE(3, "Клиент", a);
	LM_FD_CHOICE(3, "Договор", b);
	LM_ADD_BUTTON("Добавить договор", []() {
		try
		{
			// Здесь была бы проверка на то, что оба пункта существуют, но мне лень!
			contracts.push_back({
				clients[((MenuElementChoice*)LM_FD(3)[0])->getActiveOption()],
				services[((MenuElementChoice*)LM_FD(3)[1])->getActiveOption()]
				});
		}
		catch (notEnoughTrust)
		{
			LM_CON_SHARE_START;
			cout << "Недостаточно доверия!!!" << endl;
			LM_CON_SHARE_END;
		}
		Menu::popStack();
	});
	LM_ADD_BUTTON("Отмена", []() {Menu::popStack(); });
	LM_DECL_END;
}

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
	LM_FD_BUTTON(INSU, "Добавление страхового плана", []() {LM_ID(choose_insurance_service)->reset(); LM_ID(choose_insurance_service)->addToStack(); });
	LM_FD_BUTTON(INSU, "Просмотреть страховые планы", []() {
		LM_CON_SHARE_START;
		if (!services.size())
		{
			cout << "Список пуст, добавьте план." << endl;
		}
		for (auto it : services)
		{
			cout << it.getName() << "[" << it.getRequiredTrustLevel() << "] (" << it.getFee() << " -> " << it.getPay() << ")" << endl;
		}
		LM_CON_SHARE_END;
	});
	LM_ADD_FD(CONT, "Управление контрактами");
	LM_FD_BUTTON(CONT, "Заключить контракт", []() {
		MENU_make_deal();
		LM_ID(make_deal)->addToStack(); 
	})
	LM_FD_BUTTON(CONT, "Просмотреть контракты", []() {
		LM_CON_SHARE_START;
		if (!contracts.size())
		{
			cout << "Список пуст, добавьте контракт." << endl;
		}
		for (auto it : contracts)
		{
			cout << it.getClient().getName() << "[" << it.getClient().getTrustLevel() << "] купил план " << it.getInsuranceService().getName() << "[" << it.getInsuranceService().getRequiredTrustLevel() << "] (" << it.getInsuranceService().getFee() << " -> " << it.getInsuranceService().getPay() << ")" << endl;
		}
		LM_CON_SHARE_END;
	});

	LM_ADD_FD(ADDI, "Дополнительные функции");
	LM_FD_BUTTON(ADDI, "Сменить тему", []() {
		system(("color "s + themes[(++activeTheme)%themes.size()]).c_str()); 
	});
	LM_FD_BUTTON(ADDI, "Крашнуть программу", []() { terminate(); });
	LM_FD_BUTTON(ADDI, "Выйти из программы", []() { Menu::finish(); });
	LM_DECL_END;
	LM_ID(main)->addToStack();

	LM_DECL_START(add_user);
	LM_ADD_TITLE("Добавление пользователей");
	LM_ADD_FD(1, "Ввод данных");
	LM_FD_FIELD(1, "Имя клиента");
	LM_FD_CHOICE(1, "Уровень доверия", { "Низкий (0)", "Средний (1)", "Высокий (2)" });
	LM_ADD_BUTTON("Добавить клиента", []() {
		clients.push_back({
			((MenuElementEditField*)LM_FD(1)[0])->getInput(),
			((MenuElementChoice*)LM_FD(1)[1])->getActiveOption()
			}); 
		Menu::popStack();
	});
	LM_ADD_BUTTON("Отмена", []() {Menu::popStack(); });
	LM_DECL_END;
	
	LM_DECL_START(choose_insurance_service);
	LM_ADD_TITLE("Добавление страхового плана");
	LM_ADD_FD(2, "Ввод данных");
	LM_FD_FIELD(2, "Имя плана");
	LM_FD_CHOICE(2, "Взнос", { 
		"1",  "2",  "3",  "4",  "5",  "6",  "7",  "8",  "9",  "10",  "11",  "12",  "13",  "14",  "15",  "16",  "17",  "18",  "19",  "20",  "21",  "22",  "23",  "24",  "25",  "26",  "27",  "28",  "29",  "30",  "31",  "32",  "33",  "34",  "35",  "36",  "37",  "38",  "39",  "40",  "41",  "42",  "43",  "44",  "45",  "46",  "47",  "48",  "49" 
		});
	LM_FD_CHOICE(2, "Выпплаты", {
		"5",  "10",  "15",  "20",  "25",  "30",  "35",  "40",  "45",  "50",  "55",  "60",  "65",  "70",  "75",  "80",  "85",  "90",  "95",  "100",  "105",  "110",  "115",  "120",  "125",  "130",  "135",  "140",  "145",  "150",  "155",  "160",  "165",  "170",  "175",  "180",  "185",  "190",  "195",  "200",  "205",  "210",  "215",  "220",  "225",  "230",  "235",  "240",  "245"
		});
	LM_FD_CHOICE(2, "Требуемый уровень доверия", { "Низкий (0)", "Средний (1)", "Высокий (2)" });
	LM_ADD_BUTTON("Добавить план", []() {
		services.push_back({
			((MenuElementEditField*)LM_FD(2)[0])->getInput(),
			stoi(((MenuElementChoice*)LM_FD(2)[1])->getChoice()),
			stoi(((MenuElementChoice*)LM_FD(2)[2])->getChoice()),
			((MenuElementChoice*)LM_FD(2)[3])->getActiveOption()
			});
		Menu::popStack();
	});
	LM_ADD_BUTTON("Отмена", []() {Menu::popStack(); });
	LM_DECL_END;

	//LM_ID(nonexistent_id); // Раскомментировать для исключения 3.
	
	Menu::run();
	system("cls");
	cout << "Выход из программы..." << endl;
}
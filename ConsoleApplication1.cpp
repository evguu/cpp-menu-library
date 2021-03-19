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

void initContractAddMenu()
{
	LM_DECL_START(contract_add);
	LM_ADD_TITLE("Заключение договора");
	LM_ADD_FD(3a, "Ввод данных");
	vector <string> clientsParsed, servicesParsed;
	for (auto it : clients)
	{
		clientsParsed.push_back(it.getName() + " [" + to_string(it.getTrustLevel()) + "]");
	}
	for (auto it : services)
	{
		servicesParsed.push_back(it.getName() + " [" + to_string(it.getRequiredTrustLevel()) + "]");
	}
	LM_FD_CHOICE(3a, "Клиент", clientsParsed);
	LM_FD_CHOICE(3a, "Договор", servicesParsed);
	LM_ADD_BUTTON("Добавить договор", []() {
		try
		{
			// Здесь была бы проверка на то, что оба пункта существуют, но мне лень!
			int clientSize = ((MenuElementChoice*)LM_FD(3a)[0])->getOptions().size();
			int serviceSize = ((MenuElementChoice*)LM_FD(3a)[1])->getOptions().size();
			if (!clientSize || !serviceSize)
			{
				LM_CON_SHARE_START;
				cout << "Для заключения договора недостаточно сущностей." << endl;
				LM_CON_SHARE_END;
			}
			else
			{
				int clientIndex = ((MenuElementChoice*)LM_FD(3a)[0])->getActiveOption();
				int serviceIndex = ((MenuElementChoice*)LM_FD(3a)[1])->getActiveOption();
				Client client = clients[clientIndex];
				InsuranceService service = services[serviceIndex];
				contracts.push_back({ client, service });
			}
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
	LM_DECL_END(contract_add);
}

int main()
{
	/* 
		Запланированные исключения для обработки:
		1. bad_alloc << DONE (см. макросы)
		2. Попытка запустить программу с меню без выбираемых элементов -- 235, с пустым меню -- 234  << DONE
		3. Обращение к несуществующему LM_ID -- unknownMenuIdentifierException << DONE

		4. Исключение в конструкторе договора, клиент не имеет права на получение услуги -- notEnoughTrust << DONE

		5. Попытка снять последнее меню со стека -- 969 << DONE

		! Идея: доделать папки, используя исключения для возврата сигнала! << DONE -- 666, 776, 778

		Не забыть собственную функцию завершения. << DONE
	*/

	/*
		Идея: вся инициализация меню записывается как лямбда функция, которая записывается кк элемент класса меню.
		После чего при каждом добавлении меню на стек будет вызываться эта функция перегенерации. Это избавит от необходимости вручную писать reset где-либо.
		(Да и вообще уберет необходимость в функции ресет. Для этого создаю отдельный бранч.
	*/

	Utils::setupResolution();
	Utils::setupEncoding();
	system(("color "s + themes[activeTheme]).c_str());
	set_terminate([]() {
		LM_CON_SHARE_START; cout << "Произошло аварийное завершение программы. Я тоже не знаю, почему. Отладчик в помощь!" << endl; LM_CON_SHARE_END; abort(); 
	});

	LM_DECL_START(main);
	LM_ADD_TITLE("Лабораторная 2. Использование исключений.");
	LM_ADD_FD(USER, "Управление клиентами");
	LM_FD_BUTTON(USER, "Добавление клиентов", []() {LM_ID(user_add)->reset(); LM_ID(user_add)->addToStack(); });
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
	LM_FD_BUTTON(INSU, "Добавление страхового плана", []() {LM_ID(service_add)->reset(); LM_ID(service_add)->addToStack(); });
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
		initContractAddMenu();
		LM_ID(contract_add)->addToStack(); 
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
	LM_FD_BUTTON(ADDI, "Вопрос по теме", []() {
		LM_CON_SHARE_START;
		cout << "Можно ли использовать исключения в потоках? " << endl;
		string ans;
		cin >> ans;
		cout << "Ответ: можно, если обработчик находится в том же потоке. Иначе обработка исключения невозможна." << endl;
		LM_CON_SHARE_END; 
	});
	LM_DECL_END(main);
	LM_ID(main)->addToStack();

	LM_DECL_START(user_add);
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
	LM_DECL_END(user_add);
	
	LM_DECL_START(service_add);
	LM_ADD_TITLE("Добавление страхового плана");
	LM_ADD_FD(2, "Ввод данных");
	LM_FD_FIELD(2, "Имя плана");
	LM_FD_CHOICE(2, "Взнос", 1, 50, 1);
	LM_FD_CHOICE(2, "Выплаты", 5, 250, 5);
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
	LM_DECL_END(service_add);

	Menu::run();
	system("cls");
	cout << "Выход из программы..." << endl;
}
﻿#include "Fun.h"
#include "Client.h"
#include "Contract.h"
#include "InsuranceService.h"

#include <fstream>

vector<string> themes = { "0F", "07", "87", "78", "70", "F0" }; 
int activeTheme = 4; 
vector<Client> clients; vector<InsuranceService> services;
vector<Contract> contracts;

int main()
{
	system(("color "s + themes[activeTheme]).c_str());

	SETUP_START;

	LM_DECL_START(#main);
	LM_ADD_TITLE("Лабораторная 2. Использование исключений.");
	LM_ADD_FD(@main.user, "Управление клиентами");
	LM_FD_REDIR(@main.user, "Добавление клиентов", #user_add);
	LM_FD_BUTTON(@main.user, "Просмотреть клиентов", []() {
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
	LM_FD_BUTTON(@main.user, "Обновить файл клиентов", []() {
		ofstream fout;
		fout.open("clients.txt");
		for (auto it : clients)
		{
			fout << '$' << it.getName() << endl << it.getTrustLevel() << endl;
		}
		fout.close();
	});
	LM_FD_BUTTON(@main.user, "Загрузить файл клиентов", []() {
		ifstream fin;
		fin.open("clients.txt", ios::in);
		if (!fin)return;
		clients.clear();
		string name;
		int trustLevel;
		while (!fin.eof() && !fin.fail())
		{
			fin >> name >> trustLevel;
			if (fin.eof() || fin.fail()) return;
			name = name.substr(1);
			clients.push_back({name, trustLevel});
		}
		fin.close();
	});
	LM_FD_REDIR(@main.user, "Редактирование клиентов", #user_edit);
	LM_FD_REDIR(@main.user, "Удаление клиентов", #user_delete);
	LM_FD_REDIR(@main.user, "Поиск клиентов", #user_search);
	LM_ADD_FD(@main.insurance, "Управление страховыми услугами");
	LM_FD_REDIR(@main.insurance, "Добавление страхового плана", #service_add);
	LM_FD_BUTTON(@main.insurance, "Просмотреть страховые планы", []() {
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
	LM_ADD_FD(@main.contract, "Управление контрактами");
	LM_FD_REDIR(@main.contract, "Заключить контракт", #contract_add);
	LM_FD_BUTTON(@main.contract, "Просмотреть контракты", []() {
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
	LM_ADD_FD(@main.misc, "Дополнительные функции");
	LM_FD_BUTTON(@main.misc, "Сменить тему", []() {
		system(("color "s + themes[(++activeTheme) % themes.size()]).c_str());
	});
	LM_FD_BUTTON(@main.misc, "Крашнуть программу", []() { terminate(); });
	LM_FD_BUTTON(@main.misc, "Выйти из программы", []() { Menu::finish(); });
	LM_FD_BUTTON(@main.misc, "Вопрос по теме", []() {
		LM_CON_SHARE_START;
		cout << "Можно ли использовать исключения в потоках? " << endl;
		string ans;
		cin >> ans;
		cout << "Ответ: можно, если обработчик находится в том же потоке. Иначе обработка исключения невозможна." << endl;
		LM_CON_SHARE_END;
	});
	LM_DECL_END(#main);
	LM_ID(#main)->addToStack();

	LM_DECL_START(#user_add);
	LM_ADD_TITLE("Добавление пользователей");
	LM_ADD_FD(@user_add.input, "Ввод данных");
	LM_FD_FIELD(@user_add.input, "Имя клиента");
	LM_FD_CHOICE(@user_add.input, "Уровень доверия", { "Низкий (0)", "Средний (1)", "Высокий (2)" });
	LM_ADD_BUTTON("Добавить клиента", []() {
		clients.push_back({
			((MenuElementEditField*)LM_FD(@user_add.input)[0])->getInput(),
			((MenuElementChoice*)LM_FD(@user_add.input)[1])->getActiveOption()
			});
		Menu::popStack();
	});
	LM_ADD_BUTTON("Отмена", []() {Menu::popStack(); });
	LM_DECL_END(#user_add);

	LM_DECL_START(#user_edit);
	LM_ADD_TITLE("Редактирование клиентов");
	vector<string> clientsParsed;
	for (auto it : clients)
	{
		clientsParsed.push_back(it.getName() + " [" + to_string(it.getTrustLevel()) + "]");
	}
	LM_ADD_FD(@user_edit.input, "Выбор клиента");
	LM_FD_CHOICE(@user_edit.input, "Клиент", clientsParsed);
	LM_FD_REDIR(@user_edit.input, "Перейти к редактированию", #user_edit~);
	LM_ADD_BUTTON("Отмена", []() {Menu::popStack(); });
	LM_DECL_END(#user_edit);

	LM_DECL_START(#user_delete);
	LM_ADD_TITLE("Удаление клиентов");
	LM_ADD_FD(@user_delete.input, "Выбор удаляемых клиентов");
	for (auto it : clients)
	{
		LM_FD_CHOICE(@user_delete.input, it.getName() + " [" + to_string(it.getTrustLevel()) + "]", {"Не удалять", "Удалить"});
	}
	LM_ADD_BUTTON("Сохранить", []() {
		for (int i = clients.size() - 1; i >= 0; i--)
		{
			if (((MenuElementChoice*)(LM_FD(@user_delete.input)[i]))->getActiveOption())
			{
				auto it = clients.begin();
				advance(it, i);
				clients.erase(it);
			}
		}
		Menu::popStack(); 
	});
	LM_ADD_BUTTON("Отмена", []() {Menu::popStack(); });
	LM_DECL_END(#user_delete);


	LM_DECL_START(#user_search);
	LM_ADD_TITLE("Поиск клиентов");
	LM_ADD_FD(@user_search.input, "Критерии поиска");
	LM_FD_FIELD(@user_search.input, "Имя клиента");
	LM_FD_CHOICE(@user_search.input, "Уровень доверия", { "Низкий (0)", "Средний (1)", "Высокий (2)" });
	LM_ADD_BUTTON("Найти", []() {
		string result = "Результаты поиска: \n\n"s;
		bool isEmpty = true;
		string targetName = ((MenuElementEditField*)LM_FD(@user_search.input)[0])->getInput();
		TrustLevel targetTrustLevel = ((MenuElementChoice*)LM_FD(@user_search.input)[1])->getActiveOption();
		for (auto it : clients)
		{
			if ((it.getName().find(targetName) != string::npos) && (it.getTrustLevel() == targetTrustLevel))
			{
				isEmpty = false;
				result += (it.getName() + " [" + to_string(it.getTrustLevel()) + "]\n");
			}
		}
		if (isEmpty) { result += "Не найдено записей, удовлетворяющих критериям.\n"; }
		LM_CON_SHARE_START;
		cout << result;
		LM_CON_SHARE_END;
	});
	LM_ADD_BUTTON("Назад", []() {Menu::popStack(); });
	LM_DECL_END(#user_search);


	LM_DECL_START(#user_edit~);
	LM_ADD_TITLE("Подменю редактирования клиента");
	if (clients.size())
	{
		Client client = clients[((MenuElementChoice*)(LM_FD(@user_edit.input)[0]))->getActiveOption()];
		LM_ADD_FD(@user_edit~.input, "Ввод данных");
		LM_FD_FIELD(@user_edit~.input, "Имя клиента");
		((MenuElementEditField*)LM_FD(@user_edit~.input)[0])->getInput() = client.getName();
		LM_FD_CHOICE(@user_edit~.input, "Уровень доверия", { "Низкий (0)", "Средний (1)", "Высокий (2)" });
		((MenuElementChoice*)LM_FD(@user_edit~.input)[1])->getActiveOption() = client.getTrustLevel();
		LM_ADD_BUTTON("Сохранить", []() 
		{
			Client* client = &(clients[((MenuElementChoice*)(LM_FD(@user_edit.input)[0]))->getActiveOption()]);
			client->getName() = ((MenuElementEditField*)LM_FD(@user_edit~.input)[0])->getInput();
			client->getTrustLevel() = ((MenuElementChoice*)LM_FD(@user_edit~.input)[1])->getActiveOption();
			Menu::popStack(2);
		});
	}
	else
	{
		LM_ADD_SUBTITLE("Клиент не выбран, редактирование невозможно!");
	}
	LM_ADD_BUTTON("Отмена", []() {Menu::popStack(); });
	LM_DECL_END(#user_edit~);

	LM_DECL_START(#service_add);
	LM_ADD_TITLE("Добавление страхового плана");
	LM_ADD_FD(@service_add.input, "Ввод данных");
	LM_FD_FIELD(@service_add.input, "Имя плана");
	LM_FD_CHOICE(@service_add.input, "Взнос", 1, 50, 1);
	LM_FD_CHOICE(@service_add.input, "Выплаты", 5, 250, 5);
	LM_FD_CHOICE(@service_add.input, "Требуемый уровень доверия", { "Низкий (0)", "Средний (1)", "Высокий (2)" });
	LM_ADD_BUTTON("Добавить план", []() {
		services.push_back({
			((MenuElementEditField*)LM_FD(@service_add.input)[0])->getInput(),
			stoi(((MenuElementChoice*)LM_FD(@service_add.input)[1])->getChoice()),
			stoi(((MenuElementChoice*)LM_FD(@service_add.input)[2])->getChoice()),
			((MenuElementChoice*)LM_FD(@service_add.input)[3])->getActiveOption()
			});
		Menu::popStack();
	});
	LM_ADD_BUTTON("Отмена", []() {Menu::popStack(); });
	LM_DECL_END(#service_add);

	LM_DECL_START(#contract_add);
	LM_ADD_TITLE("Заключение договора");
	LM_ADD_FD(@contract_add.input, "Ввод данных");
	vector <string> clientsParsed, servicesParsed;
	for (auto it : clients)
	{
		clientsParsed.push_back(it.getName() + " [" + to_string(it.getTrustLevel()) + "]");
	}
	for (auto it : services)
	{
		servicesParsed.push_back(it.getName() + " [" + to_string(it.getRequiredTrustLevel()) + "]");
	}
	LM_FD_CHOICE(@contract_add.input, "Клиент", clientsParsed);
	LM_FD_CHOICE(@contract_add.input, "Договор", servicesParsed);
	LM_ADD_BUTTON("Добавить договор", []() {
		try
		{
			int clientSize = ((MenuElementChoice*)LM_FD(@contract_add.input)[0])->getOptions().size();
			int serviceSize = ((MenuElementChoice*)LM_FD(@contract_add.input)[1])->getOptions().size();
			if (!clientSize || !serviceSize)
			{
				LM_CON_SHARE_START; cout << "Для заключения договора недостаточно сущностей." << endl; LM_CON_SHARE_END;
			}
			else
			{
				int clientIndex = ((MenuElementChoice*)LM_FD(@contract_add.input)[0])->getActiveOption();
				int serviceIndex = ((MenuElementChoice*)LM_FD(@contract_add.input)[1])->getActiveOption();
				contracts.push_back({ clients[clientIndex], services[serviceIndex] });
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
	LM_DECL_END(#contract_add);

	SETUP_END;
}
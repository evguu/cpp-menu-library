#pragma once

// Этот файл подразумевает подключение MenuAggregator.h

// Элементы
#define LM_ADD_TITLE(...) menu->addElement(new MenuElementTitle(__VA_ARGS__))
#define LM_ADD_SUBTITLE(...) menu->addElement(new MenuElementSubtitle(__VA_ARGS__))
#define LM_ADD_BUTTON(...) menu->addElement(new MenuElementFunctionButton(__VA_ARGS__))
#define LM_ADD_FIELD(...) menu->addElement(new MenuElementEditField(__VA_ARGS__))
#define LM_ADD_CHOICE(...) menu->addElement(new MenuElementChoice(__VA_ARGS__))

#define LM_ADD_FD(id, ...) MenuElementFolder* MenuElementFolder__##id## = new MenuElementFolder(__VA_ARGS__);menu->addElement(MenuElementFolder__##id##);
#define LM_FD_TITLE(id, ...) MenuElementFolder__##id##->getElements().push_back(new MenuElementTitle(__VA_ARGS__));
#define LM_FD_SUBTITLE(id, ...) MenuElementFolder__##id##->getElements().push_back(new MenuElementSubtitle(__VA_ARGS__));
#define LM_FD_BUTTON(id, ...) MenuElementFolder__##id##->getElements().push_back(new MenuElementFunctionButton(__VA_ARGS__));
#define LM_FD_FIELD(id, ...) MenuElementFolder__##id##->getElements().push_back(new MenuElementEditField(__VA_ARGS__));
#define LM_FD_CHOICE(id, ...) MenuElementFolder__##id##->getElements().push_back(new MenuElementChoice(__VA_ARGS__));

// Добавление папок в папки настолько затруднительно, что я воздержусь.
// #define LM_FD_FD(pid, id, ...) MenuElementFolder* MenuElementFolder__##id## = new MenuElementFolder(__VA_ARGS__);MenuElementFolder__##pid##->getElements().push_back(MenuElementFolder__##id##);

// Объявления
#define LM_DECL_START(id) try{ Menu *menu; try{menu = getMenu(#id);}catch(unknownMenuIdentifierException){menu = nullptr;}; if (menu) { delete menu; }; menu = newMenu(#id);
#define LM_DECL_END menu->initChosenElementIndex(); }\
catch(bad_alloc){ string ans; LM_CON_SHARE_START;cout << "Смерть твоему компьютеру, оперативы ноль! Продолжить? Y/N" << endl; cin >> ans; if (ans != "Y") throw; else cout << "Корректная работа не гарантируется." << endl; LM_CON_SHARE_END;}\
catch(unknownMenuIdentifierException){ LM_CON_SHARE_START; cout << "Зафиксировано обращение к несуществующему меню." << endl; LM_CON_SHARE_END; throw;};

// Прочее
#define LM_GET_PREVIOUS_ELEMENT menu->getElements().back()
#define LM_ID(id) getMenu(#id)

// Управление мьютексом
#define LM_CON_SHARE_START Menu::getMutex().lock();system("MODE CON: COLS=128 LINES=200");system("cls");
#define LM_CON_SHARE_END system("pause");system("MODE CON: COLS=128 LINES=40");system("cls");Menu::getMutex().unlock();

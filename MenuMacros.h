#pragma once

// ���� ���� ������������� ����������� MenuAggregator.h

// ��������
#define LM_ADD_TITLE(...) menu->addElement(new MenuElementTitle(__VA_ARGS__))
#define LM_ADD_SUBTITLE(...) menu->addElement(new MenuElementSubtitle(__VA_ARGS__))
#define LM_ADD_BUTTON(...) menu->addElement(new MenuElementFunctionButton(__VA_ARGS__))
#define LM_ADD_FIELD(...) menu->addElement(new MenuElementEditField(__VA_ARGS__))
#define LM_ADD_CHOICE(...) menu->addElement(new MenuElementChoice(__VA_ARGS__))

// ����������
#define LM_DECL_START(id) { Menu *menu = getMenu(#id); if (menu) { delete menu; }; menu = newMenu(#id);
#define LM_DECL_END menu->initChosenElementIndex(); };

// ������
#define LM_GET_PREVIOUS_ELEMENT menu->getElements().back()
#define LM_ID(id) getMenu(#id)

// ���������� ���������
#define LM_CON_SHARE_START Menu::getMutex().lock();system("MODE CON: COLS=128 LINES=200");system("cls");
#define LM_CON_SHARE_END system("pause");system("MODE CON: COLS=128 LINES=40");system("cls");Menu::getMutex().unlock();

#pragma once

// ���� ���� ������������� ����������� MenuAggregator.h

// ��������
#define LM_ADD_TITLE(...) menu->addElement(new MenuElementTitle(__VA_ARGS__))
#define LM_ADD_SUBTITLE(...) menu->addElement(new MenuElementSubtitle(__VA_ARGS__))
#define LM_ADD_BUTTON(...) menu->addElement(new MenuElementFunctionButton(__VA_ARGS__))
#define LM_ADD_FIELD(...) menu->addElement(new MenuElementEditField(__VA_ARGS__))
#define LM_ADD_CHOICE(...) menu->addElement(new MenuElementChoice(__VA_ARGS__))

#define LM_ADD_FD(id, ...) newFD(#id, __VA_ARGS__); menu->addElement(getFD(#id));
#define LM_FD(id) getFD(#id)->getElements()
#define LM_FD_TITLE(id, ...) LM_FD(id).push_back(new MenuElementTitle(__VA_ARGS__));
#define LM_FD_SUBTITLE(id, ...) LM_FD(id).push_back(new MenuElementSubtitle(__VA_ARGS__));
#define LM_FD_BUTTON(id, ...) LM_FD(id).push_back(new MenuElementFunctionButton(__VA_ARGS__));
#define LM_FD_FIELD(id, ...) LM_FD(id).push_back(new MenuElementEditField(__VA_ARGS__));
#define LM_FD_CHOICE(id, ...) LM_FD(id).push_back(new MenuElementChoice(__VA_ARGS__));

// ���������� ����� � ����� ��������� ��������������, ��� � ����������.
// #define LM_FD_FD(pid, id, ...) MenuElementFolder* MenuElementFolder__##id## = new MenuElementFolder(__VA_ARGS__);MenuElementFolder__##pid##->getElements().push_back(MenuElementFolder__##id##);

// ����������
#define LM_DECL_START(id) {\
auto contentGenerator=[](){\
	try{\
		Menu *menu, *buf; \
		try{menu = getMenu(#id);}\
		catch(unknownMenuIdentifierException){menu = nullptr;};\
		buf = newMenu(#id);\
		if (menu) { \
			buf->getContentGenerator() = menu->getContentGenerator();\
			delete menu;\
		};\
		menu = buf;

#define LM_DECL_END(id) \
		menu->initChosenElementIndex(); return menu; }\
		catch(bad_alloc){ string ans; LM_CON_SHARE_START;cout << "������ ������ ����������, ��������� ����! ����������? Y/N" << endl; cin >> ans; if (ans != "Y") throw; else cout << "���������� ������ �� �������������." << endl; LM_CON_SHARE_END;}\
		catch(unknownMenuIdentifierException){ LM_CON_SHARE_START; cout << "������������� ��������� � ��������������� ����." << endl; LM_CON_SHARE_END; throw;};\
		return (Menu *)nullptr;\
	}; \
	contentGenerator(); \
	getMenu(#id)->getContentGenerator() = contentGenerator;\
}

// ������
#define LM_GET_PREVIOUS_ELEMENT menu->getElements().back()
#define LM_ID(id) getMenu(#id)

// ���������� ���������
#define LM_CON_SHARE_START Menu::getMutex().lock();system("MODE CON: COLS=128 LINES=200");system("cls");
#define LM_CON_SHARE_END system("pause");system("MODE CON: COLS=128 LINES=40");system("cls");Menu::getMutex().unlock();

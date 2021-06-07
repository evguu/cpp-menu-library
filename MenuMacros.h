#pragma once

// Этот файл подразумевает подключение MenuAggregator.h

// Элементы
#define TITLE(...) menu->addElement(new MenuElementTitle(__VA_ARGS__));
#define SUBTITLE(...) menu->addElement(new MenuElementSubtitle(__VA_ARGS__));
#define BUTTON(...) menu->addElement(new MenuElementFunctionButton(__VA_ARGS__));
#define REDIRECT(name, mid) menu->addElement(new MenuElementFunctionButton(name, [](){getMenu(#mid)->addToStack();}));
#define FIELD(...) menu->addElement(new MenuElementEditField(__VA_ARGS__));
#define CHOICE(...) menu->addElement(new MenuElementChoice(__VA_ARGS__));
#define FOLDER(id, ...) newFD(#id, __VA_ARGS__); menu->addElement(getFD(#id));

#define FOLDERED(id) getFD(#id)->getElements()
#define FOLDERED_TITLE(id, ...) FOLDERED(id).push_back(new MenuElementTitle(__VA_ARGS__));
#define FOLDERED_SUBTITLE(id, ...) FOLDERED(id).push_back(new MenuElementSubtitle(__VA_ARGS__));
#define FOLDERED_BUTTON(id, ...) FOLDERED(id).push_back(new MenuElementFunctionButton(__VA_ARGS__));
#define FOLDERED_REDIRECT(id, name, mid) FOLDERED(id).push_back(new MenuElementFunctionButton(name, [](){getMenu(#mid)->addToStack();}));
#define FOLDERED_FIELD(id, ...) FOLDERED(id).push_back(new MenuElementEditField(__VA_ARGS__));
#define FOLDERED_CHOICE(id, ...) FOLDERED(id).push_back(new MenuElementChoice(__VA_ARGS__));

#define AS(type, expr) ((type)(expr))
#define AS_TITLE(expr) AS(MenuElementTitle*, expr)
#define AS_SUBTITLE(expr) AS(MenuElementSubtitle*, expr)
#define AS_BUTTON(expr) AS(MenuElementFunctionButton*, expr)
#define AS_FIELD(expr) AS(MenuElementEditField*, expr)
#define AS_CHOICE(expr) AS(MenuElementChoice*, expr)
#define AS_FOLDER(expr) AS(MenuElementFolder*, expr)

// Объявления
#define START(id) {\
auto contentGenerator=[](){\
	try{\
		Menu *menu, *buf; \
		try{menu = getMenu(#id);}\
		catch(unknownKeyException){menu = nullptr;};\
		buf = newMenu(#id);\
		if (menu) { \
			buf->getContentGenerator() = menu->getContentGenerator();\
			delete menu;\
		};\
		menu = buf;

#define END(id) \
		menu->initChosenElementIndex(); return menu; }\
		catch(unknownKeyException){ CON_START; cout << "Зафиксировано обращение к несуществующему меню." << endl; CON_END; throw;};\
		return (Menu *)nullptr;\
	}; \
	contentGenerator(); \
	getMenu(#id)->getContentGenerator() = contentGenerator;\
}

// Прочее
#define PREVIOUS_ELEMENT menu->getElements().back()
#define MENU(id) getMenu(#id)

// Управление мьютексом
#define CON_START_NOLOCK system("MODE CON: COLS=128 LINES=200");system("cls");
#define CON_END_NOLOCK system("pause");Menu::setConsoleResolution();system("cls");
#define CON_START Menu::getMutex().lock();CON_START_NOLOCK;
#define CON_END CON_END_NOLOCK;Menu::getMutex().unlock();

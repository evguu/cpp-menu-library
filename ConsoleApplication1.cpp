#include "LML.h"
#include "Theme.h"

int main()
{
	Console::hideCursor();
	Console::fixEncoding();
	Menu::setConsoleResolution();
	Theme::applyCurrent();


	START(#main);
	TITLE("Лабораторная работа 6. Главное меню");

	FOLDER(@main.main, "Основные функции");
	FOLDERED_REDIRECT(@main.main, "Добавить лекарство в контейнер", #addMedicine);
	FOLDERED_REDIRECT(@main.main, "Редактировать первое доступное лекарство", #editMedicine);
	
	FOLDER(@main.misc, "Дополнительные функции");
	FOLDERED_BUTTON(@main.misc, "Сменить тему", Theme::applyNext);
	FOLDERED_BUTTON(@main.misc, "Выйти из программы", []() {
		Menu::finish();
	});

	END(#main);
	MENU(#main)->addToStack();

	
	START(#addMedicine);
	TITLE("Добавить лекарство");

	FOLDER(@addMedicine.main, "Основные функции");
	FOLDERED_FIELD(@addMedicine.main, "Имя");
	FOLDERED_BUTTON(@addMedicine.main, "Назад", []() {Menu::popStack(); });

	END(#addMedicine);


	START(#editMedicine);
	TITLE("Редактировать первое доступное лекарство");
	FOLDER(@editMedicine.main, "Основные функции");
	FOLDERED_BUTTON(@editMedicine.main, "Назад", []() {Menu::popStack(); });

	END(#editMedicine);


	Menu::run();
	Console::sayGoodbye();
}

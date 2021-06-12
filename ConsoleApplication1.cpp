﻿#include "Console.h"
#include "MenuAggregator.h"
#include "MenuMacros.h"
#include "MenuManager.h"
#include "Display.h"

#include "Title.h"
#include "Text.h"
#include "Button.h"
#include "Choice.h"
#include "Field.h"

#include "Theme.h"

auto exampleDialog = Display::dialog([]() {});
typedef BasicButton<decltype(exampleDialog)> Dialog;


// Управление мьютексом

int main()
{
	Console::fixEncoding();
	Display::setMode(Display::modeMenu);
	Theme::applyCurrent();

	MD_START("#main")
		->addElement(new Title("Проверка работы цепного добавления элементов"))
		->addElement(new Button("Субменю", []() { MenuManager::addToMenuStack(getMenu("#sub")); }))
		->addElement(new Button("Выйти", []() { MenuManager::stopLoops(); }))
		->addElement(new Dialog("everything is ok", Display::dialog([]() {cout << "everything is ok";})))
		MD_END;

	MD_START("#sub")
		->addElement(new Title("Субменю"))
		->addElement(new Field("Пустое поле"))
		->addElement([]() {auto e = new Field("Заранее заполненное поле"); e->getInput() = "Данные"; return e; }())
		->addElement(new Button("Назад", []() { MenuManager::removeFromMenuStack(); }))
		MD_END;

	MenuManager::addToMenuStack(getMenu("#main"));

	MenuManager::runLoops();
	Console::sayGoodbye();
}

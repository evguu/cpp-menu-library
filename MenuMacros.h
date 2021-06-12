#pragma once

// Ётот файл подразумевает подключение MenuAggregator.h

// Ёлементы
#define MD_START(mid) newMenu(mid)->getContentGenerator() = [](){return getMenuForGenerator(mid)
#define MD_END ->initChosenElementIndex();};

#define ADD(type, ...) ->addElement([](){auto e = new MenuElement##type(__VA_ARGS__);
#define $ return e;}())

#define AS(type, expr) ((MenuElement##type*)(expr))

// ”правление мьютексом
#define CON_START_NOLOCK system("MODE CON: COLS=128 LINES=200");system("cls");
#define CON_END_NOLOCK system("pause");Menu::setConsoleResolution();system("cls");
#define CON_START Menu::getMutex().lock();CON_START_NOLOCK;
#define CON_END CON_END_NOLOCK;Menu::getMutex().unlock();

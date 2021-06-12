#pragma once

// Ётот файл подразумевает подключение MenuAggregator.h

// Ёлементы
#define MD_START(mid) newMenu(mid)->getContentGenerator() = [](){return getMenuForGenerator(mid)
#define MD_END ->initChosenElementIndex();};

#define ADD(type, ...) ->addElement([](){auto e = new type(__VA_ARGS__);
#define $ return e;}())

#define AS(type, expr) ((type*)(expr))

// ”правление мьютексом
#define CON_START_NOLOCK system("MODE CON: COLS=128 LINES=200");system("cls");
#define CON_END_NOLOCK system("pause");MenuManager::setConsoleResolution();system("cls");
#define CON_START MenuManager::getMutex().lock();CON_START_NOLOCK;
#define CON_END CON_END_NOLOCK;MenuManager::getMutex().unlock();

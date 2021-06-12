#pragma once

// Этот файл подразумевает подключение MenuAggregator.h

// Элементы
#define MD_START(mid) newMenu(mid)->getContentGenerator() = [](){return getMenuForGenerator(mid)
#define MD_END ->initChosenElementIndex();};

#define ADD(type, ...) ->addElement([](){auto e = new type(__VA_ARGS__);
#define $ return e;}())

#define AS(type, expr) ((type*)(expr))

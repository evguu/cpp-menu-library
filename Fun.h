#pragma once
#include <iostream>
#include "CMMStack.h"
#define SETUP_START Utils::setupResolution();Utils::setupEncoding();set_terminate([]() {LM_CON_SHARE_START; cout << "Произошло аварийное завершение программы. Я тоже не знаю, почему. Отладчик в помощь!" << endl; LM_CON_SHARE_END; abort();});
#define SETUP_END Menu::run();system("cls");cout << "Выход из программы..." << endl;
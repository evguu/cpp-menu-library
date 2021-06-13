#pragma once
#include <string>
#include <locale>
#include "KeyEvent.h"

KeyEvent getKeyEvent();
char convertWideCharToChar(wchar_t w);

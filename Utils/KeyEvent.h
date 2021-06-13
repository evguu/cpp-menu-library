#pragma once
#define KC_ARROW_INCOMING 224
#define KC_UP 72
#define KC_DOWN 80
#define KC_LEFT 75
#define KC_RIGHT 77
#define KC_DELETE 83
#define KC_BACKSPACE 8
#define KC_TAB 9
#define KC_ENTER 13

struct KeyEvent
{
	int code;
	bool isSpecial;
	KeyEvent(int code = -1, bool isSpecial = false) : code(code), isSpecial(isSpecial) {};

	bool isUpDown() { return isSpecial && (code == KC_UP || code == KC_DOWN); }
	bool isLeftRight() { return isSpecial && (code == KC_LEFT || code == KC_RIGHT); }
};

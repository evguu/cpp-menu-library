#include <string>
#include <locale>
#include "Input.h"
#include <iostream>
using namespace std;

KeyEvent getKeyEvent()
{
	wchar_t rawKeyEvent = _getwch();

	switch (rawKeyEvent)
	{
	case KC_ARROW_INCOMING:
		return KeyEvent(_getwch(), true);
	case KC_TAB: case KC_DELETE: case KC_BACKSPACE: case KC_ENTER:
		return KeyEvent(rawKeyEvent, true);
	}

	unsigned char pressedSymbol = convertWideCharToChar(rawKeyEvent);
	return KeyEvent(pressedSymbol);
}

char convertWideCharToChar(wchar_t w)
{
	switch (w)
	{
	case L'q':
		return 'q';
	case L'w':
		return 'w';
	case L'e':
		return 'e';
	case L'r':
		return 'r';
	case L't':
		return 't';
	case L'y':
		return 'y';
	case L'u':
		return 'u';
	case L'i':
		return 'i';
	case L'o':
		return 'o';
	case L'p':
		return 'p';
	case L'a':
		return 'a';
	case L's':
		return 's';
	case L'd':
		return 'd';
	case L'f':
		return 'f';
	case L'g':
		return 'g';
	case L'h':
		return 'h';
	case L'j':
		return 'j';
	case L'k':
		return 'k';
	case L'l':
		return 'l';
	case L'z':
		return 'z';
	case L'x':
		return 'x';
	case L'c':
		return 'c';
	case L'v':
		return 'v';
	case L'b':
		return 'b';
	case L'n':
		return 'n';
	case L'm':
		return 'm';
	case L'Q':
		return 'Q';
	case L'W':
		return 'W';
	case L'E':
		return 'E';
	case L'R':
		return 'R';
	case L'T':
		return 'T';
	case L'Y':
		return 'Y';
	case L'U':
		return 'U';
	case L'I':
		return 'I';
	case L'O':
		return 'O';
	case L'P':
		return 'P';
	case L'A':
		return 'A';
	case L'S':
		return 'S';
	case L'D':
		return 'D';
	case L'F':
		return 'F';
	case L'G':
		return 'G';
	case L'H':
		return 'H';
	case L'J':
		return 'J';
	case L'K':
		return 'K';
	case L'L':
		return 'L';
	case L'Z':
		return 'Z';
	case L'X':
		return 'X';
	case L'C':
		return 'C';
	case L'V':
		return 'V';
	case L'B':
		return 'B';
	case L'N':
		return 'N';
	case L'M':
		return 'M';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'0':
		return '0';
	case L'1':
		return '1';
	case L'2':
		return '2';
	case L'3':
		return '3';
	case L'4':
		return '4';
	case L'5':
		return '5';
	case L'6':
		return '6';
	case L'7':
		return '7';
	case L'8':
		return '8';
	case L'9':
		return '9';
	case L'?':
		return '?';
	case L'?':
		return '?';
	case L'~':
		return '~';
	case L'!':
		return '!';
	case L'@':
		return '@';
	case L'#':
		return '#';
	case L'$':
		return '$';
	case L'%':
		return '%';
	case L'^':
		return '^';
	case L'&':
		return '&';
	case L'*':
		return '*';
	case L'(':
		return '(';
	case L')':
		return ')';
	case L'_':
		return '_';
	case L'+':
		return '+';
	case L'-':
		return '-';
	case L'=':
		return '=';
	case L'[':
		return '[';
	case L']':
		return ']';
	case L'{':
		return '{';
	case L'}':
		return '}';
	case L';':
		return ';';
	case L':':
		return ':';
	case L'\'':
		return '\'';
	case L'"':
		return '"';
	case L',':
		return ',';
	case L'.':
		return '.';
	case L'/':
		return '/';
	case L'?':
		return '?';
	case L' ':
		return ' ';
	default:
		return '?';
	}
}
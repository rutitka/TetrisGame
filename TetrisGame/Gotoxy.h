#pragma once

#include <iostream>
#include <windows.h>
#include <process.h>
#include <string>
#include <conio.h>
using namespace std;
enum Color
{
	BLACK = 0,
	BLUE = 1,
	GREEN = 2,
	CYAN = 3,
	RED = 4,
	MAGENTA = 5,
	BROWN = 6,
	LIGHTGREY = 7,
	DARKGREY = 8,
	LIGHTBLUE = 9,
	LIGHTGREEN = 10,
	LIGHTCYAN = 11,
	LIGHTRED = 12,
	LIGHTMAGENTA = 13,
	YELLOW = 14,
	WHITE = 15,
};
enum BODY { bodySize = 4 };
enum DIRECTIONKEYS { LEFT_KEY = 'a', RIGHT_KEY = 'd', DOWN_KEY = 'x', ROTATE_KEY = 'w', DROPDOWN_KEY = ' ', STOPJOKER_KEY = 's' };
enum ScreenLimits { SCREENWIDTH = 12, SCREENLENGTH = 17 };
enum Direction { LEFT, RIGHT, DOWN, ROTATE, DROPDOWN };
void gotoxy(int, int); // prototype
void clrscr(); // prototype
void setTextColor(Color);


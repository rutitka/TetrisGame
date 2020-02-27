
#include "TetrisGame.h"
#include "windows.h"
void ShowConsoleCursor(bool showFlag);

int main()
{
	ShowConsoleCursor(false);
	TetrisGame game;
	game.run();

}

void ShowConsoleCursor(bool showFlag)
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO     cursorInfo;

	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
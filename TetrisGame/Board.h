#pragma once

#include"Bomb.h"
#include"Square.h"
#include"El.h"
#include"Joker.h"
#include"Plus.h"
#include"Line.h"
#include"Zed.h"

enum { SINGLELINECLEAR = 100, DOUBLELINECLEAR = 300, TRIPLELINECLEAR = 500, TETRISLINECLEAR = 800, JOKERLINECLEAR = 50 };

class Board {
	bool board[SCREENWIDTH][SCREENLENGTH];

public:
	Board();
	void drawBoard();
	void updateBooleanBoard(Shape *piece);
	void eraseFullLines(int & score, Shape *shape);
	bool blowUp(int x, int y, int & score);
	void eraseAndUpdateAfterBomb(int x, int y);
	bool isBoardFull();
	int getLowestAvailableLine(Shape *piece);
	int calculateScoreFullLines(int fullLinesNum, Shape *shape);
	bool getValue(int x, int y);
	void eraseAndInitializeBoard();
};

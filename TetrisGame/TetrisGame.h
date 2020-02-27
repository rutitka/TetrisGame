#pragma once

#include"Board.h"

enum KEYS { START = '1', PAUSEORCONTINUE = '2', SPEEDUP = '3', SPEEDDOWN = '4', ESC = '9' };
enum GAMESPEED { FASTER = 300, SLOWER = 500, NEWGAME = 1000, GAMEOVER = 5000 };

class TetrisGame {
	Board boardGame;
public:
	TetrisGame() {};
	int score = 0;
	void run();
	void printMenu();
	void printNumOfPieces(int count);
	bool pauseAndContinueOrStart(char &keyPressed);
	void checkValidKey(char &key, Shape *shape);
	void updateSpeed(int & changeSpeed, char &key);
	void printScore(int & score);
	void hardDrop(int & score, Shape * piece);
	Shape * chooseShape();
	void printGameOver();
	void NewGame(int &score, int & countPieces, int & gameSpeed);
};

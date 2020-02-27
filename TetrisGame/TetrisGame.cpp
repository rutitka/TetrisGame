#include "TetrisGame.h"

void TetrisGame::printMenu()
{
	setTextColor(Color::WHITE);
	gotoxy(20, 7);
	cout << "MENU:";
	gotoxy(20, 8);
	cout << "Press 1 to begin game";
	gotoxy(20, 9);
	cout << "Press 2 to pause / continue";
	gotoxy(20, 10);
	cout << "Press 3 to enhance speed";
	gotoxy(20, 11);
	cout << "Press 4 to declarate speed";
	gotoxy(20, 12);
	cout << "Press 9 to exit";
	gotoxy(52, 7);
	cout << "KEYS:";
	gotoxy(52, 8);
	cout << "a - LEFT";
	gotoxy(52, 9);
	cout << "d - RIGHT";
	gotoxy(52, 10);
	cout << "w - ROTATE";
	gotoxy(52, 11);
	cout << "s - STOP SHAPE (joker only)";
	gotoxy(52, 12);
	cout << "x - SOFT DROP";
	gotoxy(52, 13);
	cout << "space - HARD DROP";
}

void TetrisGame::run()
{
	int gameSpeed = 0;
	int countPieces = 0, countPause = 0, score = 0;
	int pointsFromExplosion = 0;
	char keyPressed;
	bool gameOver = false, stop = false, startNewGame = false;
	bool isKeyPressedDown = false;
	const Point head(4, 1);
	Shape *piece;

	printMenu();
	boardGame.drawBoard();
	gotoxy(20, 0);
	cout << "PIECES FALLEN: ";
	gotoxy(20, 2);
	cout << "SCORE: ";
	printNumOfPieces(countPieces);
	printScore(score);
	keyPressed = _getch();

	if (keyPressed == KEYS::START)
	{
		while (gameOver == false)
		{
			stop = false;
			piece = chooseShape(); // the next shape is chosen randomly
			piece->setShape(head);
			piece->draw(piece->ch);

			countPieces++;
			printNumOfPieces(countPieces);

			while (!stop) // the shape hasn't stopped yet
			{
				if (_kbhit()) // checking if the user pressed any key
				{
					keyPressed = _getch();
					startNewGame = pauseAndContinueOrStart(keyPressed);
					if (startNewGame)
					{
						if (keyPressed == KEYS::START)  // the user chose to start a new game
						{
							stop = true;
							NewGame(score, countPieces, gameSpeed);
							break;
						}
					}

					if (keyPressed == DOWN_KEY) // checking if the user pressed 'x' = DOWN
					{
						isKeyPressedDown = true;
						score += 1;
						printScore(score);
					}

					else if (keyPressed == KEYS::SPEEDDOWN || keyPressed == KEYS::SPEEDUP)
						updateSpeed(gameSpeed, keyPressed);

					else if (keyPressed == KEYS::ESC) // quit game
					{
						gameOver = true;
						break;
					}
					else
						checkValidKey(keyPressed, piece);
				}

				else // if the user didn't press any key, the shape will continue to go down
				{
					keyPressed = DOWN_KEY; // DOWN
				}

				if (piece->checkAvailability(boardGame, keyPressed))
				{   // the shape can move according to the chosen direction

					if (keyPressed == DROPDOWN_KEY)
					{
						int lowestLine = piece->getLowestAvailableLine(boardGame); // checking what is the lowest line available
						hardDrop(score, piece); // updating the score according to hardDrop rules
						piece->dropDown(lowestLine); // getting the piece to it's new  and final location
						boardGame.updateBooleanBoard(piece);
						string shapeName = piece->type();

						if (shapeName == "Bomb")
						{
							boardGame.blowUp(piece->getx(0), piece->gety(0), score);
							score += 50;
							printScore(score);
						}
						stop = true;
					}

					else if (keyPressed == ROTATE_KEY) // ROTATE
					{
							piece->rotate();
					}
				
					else if (keyPressed == STOPJOKER_KEY)
					{
						string shapeName = piece->type();
						if (shapeName == "Joker")
						{
							stop = true;
							boardGame.updateBooleanBoard(piece);
						}
					}
					else // move DOWN/ LEFT/ RIGHT
						piece->move(keyPressed, boardGame.getValue(piece->getx(0), piece->gety(0)));
				}

				else // the shape can't move according to the chosen direction
				{
					if (keyPressed == DOWN_KEY) // the shape can't go down, so it will stop
					{
						string shapeName = piece->type();
						stop = true;
						boardGame.updateBooleanBoard(piece);

						if (shapeName == "Bomb")// once the bomb stopped, it will explode
						{
							boardGame.blowUp(piece->getx(0), piece->gety(0), score);
							score += 50;
							printScore(score);
						}
					}

					else if (keyPressed == LEFT_KEY || keyPressed == RIGHT_KEY) // the shape can't move left or right
					{
						string shapeName = piece->type();
						if (shapeName == "Bomb") // the bomb clashed a shape on the board
						{
							if (boardGame.blowUp(piece->getx(0), piece->gety(0), score)) // explosion
							{
								stop = true;
								score += 50;
								printScore(score);
							}
						}
						else // the shape is not a bomb
						{
							keyPressed = DOWN_KEY;
							if (piece->checkAvailability(boardGame, keyPressed))
								// checking if the shape can move down insted of left or right */													    								   
							{
								piece->move(keyPressed, boardGame.getValue(piece->getx(0), piece->gety(0)));
							}

							else // the shape can't go down - it has to stop
							{
								stop = true;
								boardGame.updateBooleanBoard(piece);
								string shapeName = piece->type();

								if (shapeName == "Bomb")
								{
									boardGame.blowUp(piece->getx(0), piece->gety(0), score);
									score += 50;
									printScore(score);
								}
							}
						}
					}
				}
				if (isKeyPressedDown) // checking if the user chose SOT DROP 
					Sleep(FASTER + gameSpeed);
				else
					Sleep(SLOWER + gameSpeed);

				if (stop) // checking if the piece stopped moving 
				{
					boardGame.eraseFullLines(score, piece);
					printScore(score);
					while (_kbhit()) // clean buffer
					{
						_getch();
					}
					delete piece;
				}

				if (boardGame.isBoardFull()) // checking if the shapes are touching the top wall - if they are - GAME OVER
				{
					gameOver = true;
					printGameOver();
					Sleep(GAMEOVER);
				}

				isKeyPressedDown = false;

			}
		}
	}
}

void TetrisGame::printNumOfPieces(int count)
{
	for (int i = 0; i < 15; i++) // assuming the score won't be longer than 15 digits
	{
		gotoxy(35 + i, 0);
		cout << " ";
	}

	gotoxy(35, 0);
	cout << count;
}

bool TetrisGame::pauseAndContinueOrStart(char &keyPressed)
{
	if (keyPressed == KEYS::PAUSEORCONTINUE)
	{
		keyPressed = _getch();
		if (keyPressed == KEYS::START)
			return true;

		while (keyPressed != KEYS::PAUSEORCONTINUE && keyPressed != KEYS::START && keyPressed != KEYS::ESC)
		{
			keyPressed = _getch();
		}
	}
	if (keyPressed == KEYS::START)
		return true;
	else
		return false;
}

void  TetrisGame ::checkValidKey(char &key, Shape *shape)
{
	string shapeName = shape->type();

	if ((key != LEFT_KEY && key != ROTATE_KEY && key != RIGHT_KEY && key != DOWN_KEY && key != DROPDOWN_KEY && key != STOPJOKER_KEY) || (key == STOPJOKER_KEY && shapeName != "Joker" ) || (key == ROTATE_KEY && shape->isRotatable == false))
		key = DOWN_KEY;
}

void TetrisGame::updateSpeed(int & changeSpeed, char &key)
{
	int temp = changeSpeed;

	if (key == KEYS::SPEEDDOWN)
		changeSpeed += 30;

	else
	{
		changeSpeed -= 30;
		if (300 + changeSpeed < 0)
			changeSpeed = temp;
	}

	key = DOWN_KEY;
}

void TetrisGame::printScore(int & score)
{
	for (int i = 0; i < 15; i++) // assuming the score won't be longer than 15 digits
	{
		gotoxy(27 + i, 2);
		cout << " ";
	}

	gotoxy(27, 2);
	cout << score;
}

void TetrisGame::hardDrop(int & score, Shape * piece)
{
	int y = piece->gety(3); // the third (last) cell of each shape represent the lowest location of the shape
						   // at the moment
	score += 2 * (SCREENLENGTH - 2 - y);
}

Shape * TetrisGame::chooseShape()
{
	Shape * res;

	int type = rand() % 24;

	if (type == 0 || type == 1)
	{// in 1 out of 9 of the cases the chosen shape will be a BOMB
		res = new Bomb;
		return res;
	}

	else if (type == 2 || type == 3)
	{// in 2 out of 9 of the cases the chosen shape will be a JOKER
		res = new Joker;
		return res;
	}

	else if (type >= 4 && type <= 7)
	{// in 3 out of 9 of the cases the chosen shape will be a LINE
		res = new Line;
		return res;
	}

	else if (type >= 8 && type <= 11)
	{// in 1 out of 9 of the cases the chosen shape will be a SQUARE
		res = new Square;
		return res;
	}

	else if (type >= 12 && type <= 15)
	{
		res = new Zed;
		return res;
	}

	else if (type >= 16 && type <= 19)
	{
		res = new El;
		return res;
	}
	else
	{
		res = new Plus;
		return res;
	}

}

void TetrisGame::printGameOver()
{
	// clearing the board
	for (int i = 1; i < SCREENWIDTH - 1; i++)
		for (int j = 1; j < SCREENLENGTH - 1; j++)
		{
			gotoxy(i, j);
			cout << " ";
		}
	gotoxy(3, 5);
	cout << "G A M E";
	gotoxy(3, 7);
	cout << "O V E R";
	gotoxy(5, 9);
	cout << ":(";
}

void TetrisGame::NewGame(int &score, int & countPieces, int & gameSpeed)
{
	// initializing all variables to zero
	boardGame.eraseAndInitializeBoard();
	countPieces = 0;
	score = 0;
	printNumOfPieces(countPieces);
	printScore(score);
	gameSpeed = 0;
	Sleep(NEWGAME);
}



#include "Board.h"

Board::Board() // initialize the board to false
{
	for (int i = 0; i < SCREENWIDTH; i++)
		for (int j = 0; j < SCREENLENGTH; j++)
		{
			if ((i == 0) || (j == 0) || (j == SCREENLENGTH - 1) || (i == SCREENWIDTH - 1))
				board[i][j] = false;
			else
				board[i][j] = true;
		}
}

void Board::drawBoard()
{
	for (int i = 0; i < SCREENWIDTH; i++) // draws top limit of the board
	{
		gotoxy(i, 0);
		cout << "#";
	}

	for (int i = 1; i < SCREENLENGTH - 1; i++) // draws side limits
	{
		gotoxy(0, i);
		cout << "#";
		gotoxy(11, i);
		cout << "#";
	}

	for (int i = 0; i < SCREENWIDTH; i++) // draws bottom limit of the board
	{
		gotoxy(i, 16);
		cout << "#";
	}
}

void Board::updateBooleanBoard(Shape *piece)
{
	for (int i = 0; i < bodySize; i++)
	{
		board[piece->getx(i)][piece->gety(i)] = false;
	}
}

void Board::eraseFullLines(int & score, Shape *shape)
{
	int countFullLines = 0, SaveNumFullLines = 0;
	bool lastLineErased = false;

	for (int i = SCREENLENGTH - 2; i > 0; i--)
	{
		int countCells = 0;
		for (int j = 1; j < SCREENWIDTH - 1; j++)// the bottom wall is in line 16, so the last line of the board is 15
		{
			if (board[j][i] == false)
				countCells++;

			if ((j == SCREENWIDTH - 2) && (countCells == SCREENWIDTH - 2))
				lastLineErased = true;
			else
				lastLineErased = false;
		}

		if (lastLineErased)// the i line is full
		{
			countFullLines++;
			for (int k = 1; k < SCREENWIDTH - 1; k++)
			{
				board[k][i] = true;
				gotoxy(k, i);
				cout << " ";
			}
		}

		else if ((countFullLines > 0) && (!lastLineErased))// the i line isn't full
		{
			for (int k = i; k >= 1; k--)
			{
				for (int j = 1; j < SCREENWIDTH - 1; j++)
				{
					board[j][k + countFullLines] = board[j][k];
					if (board[j][k] == false)
					{
						gotoxy(j, k + countFullLines);
						cout << "*";
						board[j][k] = true;
						gotoxy(j, k);
						cout << " ";
					}
				}
			}
			SaveNumFullLines += countFullLines;
			countFullLines = 0;
			i = SCREENLENGTH - 2;
		}
	}

	score += calculateScoreFullLines(SaveNumFullLines, shape);

	if (countFullLines != 0)
		Sleep(200);
}

bool Board::blowUp(int x, int y, int & score)
{
	int temp = score;

	if (x != 1 && x != SCREENWIDTH - 2 && y != 1 && y != SCREENLENGTH - 2)//the bomb is not located near a wall
	{
		for (int i = x - 1; i <= x + 1; i++)
			for (int j = y - 1; j <= y + 1; j++)
			{
				if (board[i][j] == false)
					score -= 50;
				eraseAndUpdateAfterBomb(i, j);
			}
	}

	else if (x == 1 && y == 1) // top left corner
	{
		if (board[x + 1][y] == false || board[x][y + 1] == false || board[x + 1][y + 1] == false)
			// checking if the bomb clashed a shape and not just a wall 
		{
			for (int i = x; i <= x + 1; i++)
				for (int j = y; j <= y + 1; j++)
				{
					if (board[i][j] == false)
						score -= 50;
					eraseAndUpdateAfterBomb(i, j);
				}
		}
	}

	else if (x == SCREENWIDTH - 2 && y == 1) // top right corner
	{
		if (board[x - 1][y] == false || board[x][y + 1] == false || board[x - 1][y + 1] == false)
			// checking if the bomb clashed a shape and not just a wall 
		{
			for (int i = x; i <= x; i++)
				for (int j = y; j <= y + 1; j++)
				{
					if (board[i][j] == false)
						score -= 50;
					eraseAndUpdateAfterBomb(i, j);
				}
		}
	}

	else if (x == 1 && y == SCREENLENGTH - 2) // bottom left corner
	{
		{
			for (int i = x; i <= x; i++)
				for (int j = y - 1; j <= y; j++)
				{
					if (board[i][j] == false)
						score -= 50;
					eraseAndUpdateAfterBomb(i, j);
				}
		}
	}

	else if (x == SCREENWIDTH - 2 && y == SCREENLENGTH - 2) // bottom right corner
	{
		{
			for (int i = x - 1; i <= x; i++)
				for (int j = y - 1; j <= y; j++)
				{
					if (board[i][j] == false)
						score -= 50;
					eraseAndUpdateAfterBomb(i, j);
				}
		}
	}

	else if (x == 1) // located next to the left wall
	{
		if (board[x][y - 1] == false || board[x + 1][y - 1] == false || board[x + 1][y] == false || board[x + 1][y + 1] == false || board[x][y + 1] == false)
		{
			for (int i = x; i <= x + 1; i++)
				for (int j = y - 1; j <= y + 1; j++)
				{
					if (board[i][j] == false)
						score -= 50;
					eraseAndUpdateAfterBomb(i, j);
				}
		}
	}

	else if (x == SCREENWIDTH - 2)// located next to the right wall
	{
		if (board[x][y - 1] == false || board[x - 1][y - 1] == false || board[x - 1][y] == false || board[x - 1][y + 1] == false || board[x][y + 1] == false)
		{
			for (int i = x - 1; i <= x; i++)
				for (int j = y - 1; j <= y + 1; j++)
				{
					if (board[i][j] == false)
						score -= 50;
					eraseAndUpdateAfterBomb(i, j);
				}
		}
	}

	else if (y == 1) // located next to the top wall
	{
		if (board[x - 1][y] == false || board[x - 1][y + 1] == false || board[x][y + 1] == false || board[x + 1][y + 1] == false || board[x + 1][y] == false)
		{
			for (int i = x - 1; i <= x + 1; i++)
				for (int j = y; j <= y + 1; j++)
				{
					if (board[i][j] == false)
						score -= 50;
					eraseAndUpdateAfterBomb(i, j);
				}
		}
	}

	else if (y == SCREENLENGTH - 2) // located next to the bottom wall
	{
		{
			for (int i = x - 1; i <= x + 1; i++)
				for (int j = y - 1; j <= y; j++)
				{
					if (board[i][j] == false)
						score -= 50;
					eraseAndUpdateAfterBomb(i, j);
				}
		}
	}

	if (score == temp)
		return false;
	else
		return true;
}

void Board::eraseAndUpdateAfterBomb(int x, int y)
{
	board[x][y] = true;
	gotoxy(x, y);
	cout << " ";
}

bool Board::isBoardFull()
{
	for (int i = 1; i < SCREENWIDTH - 1; i++) // cols 0 and 11 represent the side walls of the board
		if (board[i][1] == false)
			return true;

	return false;
}

int Board::getLowestAvailableLine(Shape * piece)
{
	int lowestLine = piece->gety(3);

	while (lowestLine < SCREENLENGTH - 1) // the bottom wall is in line 16, so the last line of the board is 15
	{
		for (int i = 0; i < bodySize; i++)
		{
			if (board[piece->getx(i)][lowestLine] == false)
			{
				return lowestLine - 1;
			}
		}
		lowestLine++;
	}

	return lowestLine - 1;
}

bool Board::getValue(int x, int y) 
{
	return board[x][y];
}

void Board::eraseAndInitializeBoard()
{
	for (int i = 1; i < SCREENWIDTH - 1; i++)// cols 0 and 11 represent the side walls of the board
		for (int j = 1; j < SCREENLENGTH - 1; j++) // the bottom wall is in line 16, so the last line of the board is 15
		{
			board[i][j] = true;
			gotoxy(i, j);
			cout << " ";
		}
}

int Board::calculateScoreFullLines(int fullLinesNum, Shape *shape)
{
	if (fullLinesNum == 1)
	{
		string shapeName = shape->type();
		if (shapeName == "Joker")
			return 50;
		else
			return SINGLELINECLEAR;
	}

	else if (fullLinesNum == 2)
		return DOUBLELINECLEAR;

	else if (fullLinesNum == 3)
		return TRIPLELINECLEAR;

	else if (fullLinesNum == 4)
		return TETRISLINECLEAR;

	else
		return JOKERLINECLEAR;
}
#include "Zed.h"
#include "Board.h" 

void Zed:: setShape(const Point& head)
{
	body[0] = head;
	body[1] = body[0].right();
	body[2] = body[1].down();
	body[3] = body[2].right();

	dirKeys[0] = LEFT_KEY;
	dirKeys[1] = RIGHT_KEY;
	dirKeys[2] = DOWN_KEY;
	dirKeys[3] = ROTATE_KEY;
	dirKeys[4] = DROPDOWN_KEY;

	ch = '*';
	isRotatable = true;
	setColor(Color::LIGHTCYAN);
}

void Zed:: dropDown(int lowestLine)
{
	int cellZeroY = body[0].gety();
	int cellOneY = body[1].gety();
	int cellTwoY = body[2].gety();
	int cellThreeY = body[3].gety();

	eraseShape();

	if (cellOneY < cellTwoY)
	{
		for (int i = 2; i < bodySize; i++)
			body[i].set(body[i].getx(), lowestLine);
		lowestLine--;
		for (int i = 0; i < 2; i++)
			body[i].set(body[i].getx(), lowestLine);
	}

	else if (cellOneY == cellTwoY && cellZeroY < cellThreeY)
	{
		body[3].set(body[3].getx(), lowestLine);
		lowestLine--;
		body[2].set(body[2].getx(), lowestLine);
		body[1].set(body[1].getx(), lowestLine);
		lowestLine--;
		body[0].set(body[0].getx(), lowestLine);
	}

	else if (cellOneY > cellTwoY)
	{
		for (int i = 0; i < 2; i++)
			body[i].set(body[i].getx(), lowestLine);
		lowestLine--;
		for (int i = 2; i < bodySize; i++)
			body[i].set(body[i].getx(), lowestLine);
	}

	else
	{
		body[0].set(body[0].getx(), lowestLine);
		lowestLine--;
		body[2].set(body[2].getx(), lowestLine);
		body[1].set(body[1].getx(), lowestLine);
		lowestLine--;
		body[3].set(body[3].getx(), lowestLine);
	}

	draw(ch);
}

string Zed::type()
{
	return "Zed";
}

int Zed::getLowestAvailableLine(Board & board)
{
	int lowestLine;
	int cellZeroY = body[0].gety();
	int cellOneY = body[1].gety();
	int cellTwoY = body[2].gety();
	int cellThreeY = body[3].gety();

	if (cellZeroY < cellThreeY && cellOneY < cellTwoY)
	{
		lowestLine = cellThreeY;
		while (lowestLine < SCREENLENGTH - 1) // the bottom wall is in line 16, so the last line of the board is 15
		{
			for (int i = 0; i < 2; i++)
			{
				if (board.getValue(getx(i), lowestLine) == false)
				{
					return lowestLine;
				}
			}

			lowestLine++;

			for (int i = 2; i < bodySize; i++)
			{
				if (board.getValue(getx(i), lowestLine) == false)
				{
					return lowestLine-1;
				}
			}  
		}

		return lowestLine - 1;
	}

	else if (cellZeroY < cellThreeY && cellTwoY == cellOneY)
	{
		lowestLine = cellThreeY;
		while (lowestLine < SCREENLENGTH - 1) // the bottom wall is in line 16, so the last line of the board is 15
		{
			if (board.getValue(getx(0), lowestLine-1) == false)
				return lowestLine;

			if(board.getValue(getx(1), lowestLine) == false)
				return lowestLine;

			if(board.getValue(getx(2), lowestLine) == false)
				return lowestLine;

			if (board.getValue(getx(3), lowestLine+1) == false)
				return lowestLine;
			
			lowestLine++;
		}

		return lowestLine-1;
	}

	else if (cellThreeY < cellZeroY && cellTwoY < cellOneY)
	{
		lowestLine = cellZeroY;
		while (lowestLine < SCREENLENGTH - 1) // the bottom wall is in line 16, so the last line of the board is 15
		{
			for (int i = 2; i < bodySize; i++)
			{
				if (board.getValue(getx(i), lowestLine) == false)
				{
					return lowestLine;
				}
			}

			lowestLine++;

			for (int i = 0; i < 2; i++)
			{
				if (board.getValue(getx(i), lowestLine) == false)
				{
					return lowestLine-1;
				}
			}
		}
		return lowestLine-1;
	}

	else
	{
		lowestLine = cellZeroY;
		while (lowestLine < SCREENLENGTH - 1) // the bottom wall is in line 16, so the last line of the board is 15
		{
			if (board.getValue(getx(3), lowestLine - 1) == false)
				return lowestLine;

			if (board.getValue(getx(1), lowestLine) == false)
				return lowestLine;

			if (board.getValue(getx(2), lowestLine) == false)
				return lowestLine;

			if (board.getValue(getx(0), lowestLine + 1) == false)
				return lowestLine;

			lowestLine++;
		}
		return lowestLine;
	}
}
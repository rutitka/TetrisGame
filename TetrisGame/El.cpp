#include "El.h"
#include "Board.h"

void El::setShape(const Point& head)
{
	body[0] = head;
	body[1] = body[0].down();
	body[2] = body[1].right();
	body[3] = body[2].right();

	dirKeys[0] = LEFT_KEY;
	dirKeys[1] = RIGHT_KEY;
	dirKeys[2] = DOWN_KEY;
	dirKeys[3] = ROTATE_KEY;
	dirKeys[4] = DROPDOWN_KEY;

	ch = '*';
	isRotatable = true;
	setColor(Color::LIGHTMAGENTA);
}

void El::dropDown(int lowestLine)
{
	eraseShape();

	int cellZeroY = body[0].gety();
	int cellOneY = body[1].gety();
	int cellThreeY = body[3].gety();

	if (cellOneY == cellThreeY && cellOneY > cellZeroY)
	{
		for (int i = 1; i < bodySize; i++)
			body[i].set(body[i].getx(), lowestLine);

		lowestLine--;
		body[0].set(body[0].getx(), lowestLine);
	}

	else if (cellOneY < cellThreeY)
	{
		body[3].set(body[3].getx(), lowestLine);
		lowestLine--;
		body[2].set(body[2].getx(), lowestLine);
		lowestLine--;
		body[1].set(body[1].getx(), lowestLine);
		body[0].set(body[0].getx(), lowestLine);
	}

	else if (cellOneY == cellThreeY && cellOneY < cellZeroY)
	{
		body[0].set(body[0].getx(), lowestLine);
		lowestLine--;

		for (int i = 1; i < bodySize; i++)
			body[i].set(body[i].getx(), lowestLine);
	}

	else
	{
		body[1].set(body[1].getx(), lowestLine);
		body[0].set(body[0].getx(), lowestLine);
		lowestLine--;
		body[2].set(body[2].getx(), lowestLine);
		lowestLine--;
		body[3].set(body[3].getx(), lowestLine);
	}

	draw(ch);
}

string El::type()
{
	return "El";
}

int El::getLowestAvailableLine(Board & board)
{
	int lowestLine;
	int cellZeroY = body[0].gety();
	int cellOneY = body[1].gety();
	int cellTwoY = body[2].gety();
	int cellThreeY = body[3].gety();

	if (cellZeroY < cellThreeY && cellOneY == cellTwoY)
	{
		lowestLine = cellThreeY;
		while (lowestLine < SCREENLENGTH - 1) // the bottom wall is in line 16, so the last line of the board is 15
		{
			if (board.getValue(getx(0), lowestLine) == false)
				return lowestLine;

			for (int i = 1; i < bodySize; i++)
			{
				if (board.getValue(getx(i), lowestLine+1) == false)
					return lowestLine;
			}

			lowestLine++;
		}
		return lowestLine - 1;
	}

	else if (cellZeroY == cellOneY && cellZeroY < cellThreeY)
	{
		lowestLine = cellThreeY;
		while (lowestLine < SCREENLENGTH - 1) // the bottom wall is in line 16, so the last line of the board is 15
		{
			if (board.getValue(getx(0), lowestLine -1) == false)
				return lowestLine;

			if (board.getValue(getx(1), lowestLine - 1) == false)
				return lowestLine;

			if (board.getValue(getx(2), lowestLine) == false)
				return lowestLine;

			if (board.getValue(getx(3), lowestLine + 1) == false)
				return lowestLine;

			lowestLine++;
		}

		return lowestLine - 1;
	}

	else if (cellThreeY < cellZeroY && cellTwoY == cellThreeY)
	{
		lowestLine = cellZeroY;
		while (lowestLine < SCREENLENGTH - 1) // the bottom wall is in line 16, so the last line of the board is 15
		{
			for (int i = 1; i < bodySize; i++)
			{
				if (board.getValue(getx(i), lowestLine) == false)
					return lowestLine;
			}

			if(board.getValue(getx(0), lowestLine+1) == false)
				return lowestLine;

			lowestLine++;
		}

		return lowestLine - 1;
	}

	else
	{
		lowestLine = cellZeroY;
		while (lowestLine < SCREENLENGTH - 1) // the bottom wall is in line 16, so the last line of the board is 15
		{
			if (board.getValue(getx(3), lowestLine - 1) == false)
				return lowestLine;

			if (board.getValue(getx(2), lowestLine) == false)
				return lowestLine;

			if (board.getValue(getx(1), lowestLine+1) == false)
				return lowestLine;

			if (board.getValue(getx(0), lowestLine + 1) == false)
				return lowestLine;
			lowestLine++;
		}

		return lowestLine - 1;
	}

}
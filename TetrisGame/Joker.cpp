#include "Joker.h"
#include "Board.h"
void Joker::setShape(const Point& head)
{
	for (int i = 0; i < bodySize; i++)
		body[i] = head;

	dirKeys[0] = LEFT_KEY;
	dirKeys[1] = RIGHT_KEY;
	dirKeys[2] = DOWN_KEY;
	dirKeys[3] = STOPJOKER_KEY;
	dirKeys[4] = DROPDOWN_KEY;

	ch = '*';
	isRotatable = false;
	setColor(Color::YELLOW);
}

void Joker::move(char keypressed, bool erase)
{
	Direction dir = getDir(keypressed);
	setTextColor(color);

	if (erase == false)
	{
		for (int i = 0; i < bodySize; i++)
			body[i].move(getDir(keypressed));
	}
	else
	{
		draw(' ');
		for (int i = 0; i < bodySize; i++)
			body[i].move(getDir(keypressed));
	}
	draw(ch);
}

void Joker::dropDown(int lowestLine)
{
	eraseShape();

	for (int i = 0; i < bodySize; i++)
		body[i].set(body[i].getx(), SCREENLENGTH - 2);

	draw(ch);
}

bool Joker::checkAvailability(Board &board, char keyPressed)
{
	switch (keyPressed)
	{
	case LEFT_KEY: // left
		if (getx(0) - 1 == 0)
			return false;
	
		return true;

	case RIGHT_KEY: // right
		if (getx(0) + 1 == SCREENWIDTH - 1)
			return false;
	
		return true;

	case DOWN_KEY: // down
		if (gety(0) + 1 == SCREENLENGTH - 1)
			return false;
		
		return true;

	case ROTATE_KEY: // rotate
		for (int i = 0; i < bodySize; i++)
		{
			Point p;
			p = getLocationAfterRotation(i, getx(2), gety(2));
			if (board.getValue(p.getx(),p.gety()) == false)
				return false;
		}
	}
	return true;
}

string Joker::type()
{
	return "Joker";
}

void Joker:: rotate() {}
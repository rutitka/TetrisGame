#include "Shape.h"
#include "Board.h"

int Shape::getx(int i)
{
	Point p;
	int x;
	p = this->body[i];
	x = p.getx();
	return x;
}

int Shape::gety(int i)
{
	Point p;
	int y;
	p = this->body[i];
	y = p.gety();
	return y;
}

void Shape::draw(char ch)
{
	for (int i = 0; i < bodySize; i++)
	{
		body[i].draw(ch, color);
	}
}

void Shape :: move(char keypressed, bool erase) 
{
	draw(' ');

	for (int i = 0; i < bodySize; i++)
		body[i].move(getDir(keypressed));

	draw(ch);
}

Direction Shape::getDir(char keyPressed)
{
	for (int i = 0; i < bodySize; i++)
	{
		if (keyPressed == dirKeys[i])
		{
			return (Direction)(i);
		}
	}
	return Direction::DOWN;
}

void Shape::setColor(Color c) {
	color = c;
}


void Shape::eraseShape()
{
	for (int i = 0; i < bodySize; i++)
	{
		gotoxy(this->getx(i), this->gety(i));
		cout << " ";
	}
}

Point Shape::getLocationAfterRotation(int i, int pivX, int pivY)
{
	Point p;
	int x, y, rX, rY;
	int tmp;

	x = body[i].getx();
	y = body[i].gety();
	rX = x - pivX;
	rY = -y + pivY;
	p.set(rX, rY);
	tmp = p.getx();
	p.set(rY, tmp);
	p.set(p.getx() + pivX, p.gety() + pivY);

	return p;
}

void Shape::rotate()
{
	int x, y, rX, rY, pivX, pivY;

	pivX = body[2].getx();
	pivY = body[2].gety();
	for (int i = 0; i < bodySize; ++i)
	{
		x = body[i].getx();
		y = body[i].gety();
		rX = x - pivX;
		rY = -y + pivY;
		body[i].set(rX, rY);
		int tmp = body[i].getx();
		body[i].set(rY, tmp);
		body[i].set(body[i].getx() + pivX, body[i].gety() + pivY);
		gotoxy(x, y);
		cout << " ";
	}
	
	draw(ch);
}

bool Shape:: checkAvailability(Board &board, char keyPressed)
{
	switch (keyPressed)
	{
	   case LEFT_KEY: // left
		   for (int i = 0; i < bodySize; i++)
		   {
			   if (board.getValue(getx(i) - 1, gety(i)) == false)
				   return false;
		   }
		return true;

	  case RIGHT_KEY: // right
			for (int i = 0; i < bodySize; i++)
			{
				if (board.getValue(getx(i) + 1, gety(i)) == false)
					return false;
			}
		return true;

	case DOWN_KEY: // down
			for (int i = 0; i < bodySize; i++)
			{

				if (board.getValue(getx(i),gety(i) + 1) == false)
					return false;
			}
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

int Shape :: getLowestAvailableLine(Board & board)
{
	int lowestLine = gety(3);

	while (lowestLine < SCREENLENGTH - 1) // the bottom wall is in line 16, so the last line of the board is 15
	{
		for (int i = 0; i < bodySize; i++)
		{
			if (board.getValue(getx(i),lowestLine) == false)
			{
				return lowestLine - 1;
			}
		}
		lowestLine++;
	}

	return lowestLine - 1;
}


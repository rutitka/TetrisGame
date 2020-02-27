#include "Bomb.h"

void Bomb::setShape(const Point& head)
{
	for (int i = 0; i < bodySize; i++)
		body[i] = head;

	dirKeys[0] = LEFT_KEY;
	dirKeys[1] = RIGHT_KEY;
	dirKeys[2] = DOWN_KEY;
	dirKeys[3] = DROPDOWN_KEY;

	ch = '@';
	isRotatable = false;
	setColor(Color::LIGHTRED);
}

void Bomb::dropDown(int lowestLine)
{
	eraseShape();

	for (int i = 0; i < bodySize; i++)
	     body[i].set(body[i].getx(), lowestLine);

	draw(ch);
}

string Bomb::type()
{
	return "Bomb";
}

void Bomb:: rotate(){}

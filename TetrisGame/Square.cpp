#include "Square.h"

void Square::setShape(const Point& head)
{
	body[0] = head;
	body[1] = head.right();
	body[2] = head.down();
	body[3] = body[2].right();

	dirKeys[0] = LEFT_KEY;
	dirKeys[1] = RIGHT_KEY;
	dirKeys[2] = DOWN_KEY;
	dirKeys[3] = DROPDOWN_KEY;

	ch = '*';
	isRotatable = false;
	setColor(Color::LIGHTGREEN);		
}

void Square::dropDown(int lowestLine)
{
	eraseShape();

	for (int i = 0; i <= 1; i++)
		body[i].set(body[i].getx(), lowestLine - 1);

	for (int i = 2; i < bodySize; i++)
		body[i].set(body[i].getx(), lowestLine);

	draw(ch);
}

string Square::type()
{
	return "Square";
}

void Square::rotate() {}

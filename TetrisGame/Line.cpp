#include "Line.h"

void Line::setShape(const Point& head)
{
	body[0] = head;

	for (int i = 1; i < bodySize; i++)
	{
		body[i] = body[i - 1].right();
	}
	dirKeys[0] = LEFT_KEY;
	dirKeys[1] = RIGHT_KEY;
	dirKeys[2] = DOWN_KEY;
	dirKeys[3] = ROTATE_KEY;
	dirKeys[4] = DROPDOWN_KEY;
	
	ch = '*';
	isRotatable = true;
	setColor(Color::LIGHTCYAN);
}

void Line::dropDown(int lowestLine)
{
	eraseShape();

	if (body[0].gety() == body[1].gety())
	{
		for (int i = 0; i < bodySize; i++)
			body[i].set(body[i].getx(), lowestLine);

	}

	else
	{
		for (int i = bodySize - 1; i >= 0; i--) // the shape is a rotated LINE
		{
			body[i].set(body[i].getx(), lowestLine);
			lowestLine--;
		}
	}

	draw(ch);
}

string Line::type()
{
	return "Line";
}
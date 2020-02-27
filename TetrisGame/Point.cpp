#include "Point.h"

void Point::changeDir(Direction dir) {
	switch (dir) {

	case Direction::LEFT:
		dir_x = -1;
		dir_y = 0;
		break;
	case Direction::RIGHT:
		dir_x = 1;
		dir_y = 0;
		break;
	case Direction::DOWN:
		dir_x = 0;
		dir_y = 1;
		break;
	}
}
void Point:: set(int _x, int _y)
{
	x = _x;
	y = _y;
}
int Point::gety()
{
	return this->y;
}

Point::Point(int x1, int y1)
{
	x = x1;
	y = y1;
}

Point Point::right() const
{
	return Point(x + 1, y);
}

Point Point::left() const
{
	return Point(x - 1, y);
}

Point Point::down() const 
{
	return Point(x, y + 1);
}

void Point::move(Direction dir)
{
	changeDir(dir);
	this->x += this->dir_x;
	this->y += this->dir_y;
}

void Point::draw(char c , Color color) const
{
	setTextColor(color);
	gotoxy(x, y);
	cout << c;
	cout.flush();
}

int Point::getx()
{
	return this->x;
}

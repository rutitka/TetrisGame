#pragma once
#include "Gotoxy.h"

class Point
{
	int x, y;
	int dir_x = 0, dir_y = 0;
public:
	Point() {};
	Point(int x1, int y1);
	Point right() const;
	Point down() const;
	Point left() const;
	void changeDir(Direction dir);
	void move(Direction dir);
	void draw(char c , Color color) const;
	int getx();
	int gety();
	void set(int _x, int _y);
	
};




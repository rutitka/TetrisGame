#pragma once
#include "Point.h"

class Board;
class Shape {
protected:
	bool isRotatable;
	enum { keysArraySize = 5 };
	char dirKeys[keysArraySize]; // the keys for the five possible directions
	Point body[bodySize];
	char ch;
	Color color;

public:
	Shape() {};
	enum ShapeType { SQUARE, LINE, JOKER, BOMB, PLUS, ZED, EL};
	virtual bool checkAvailability(Board &board, char keyPressed);
	virtual void setShape(const Point& head) = 0;
	virtual string type() = 0;
	Direction getDir(char keyPressed);
	virtual void move(char keypressed, bool erase);
	void draw(char ch);
	int getx(int i);
	int gety(int i);
	virtual void rotate();
	Point getLocationAfterRotation(int i, int pivX, int pivY);
	virtual void dropDown(int lowestLine) = 0;
	void eraseShape();
	void setColor(Color c);
	virtual int getLowestAvailableLine(Board & board);
	friend class TetrisGame;
};
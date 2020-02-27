#pragma once

#include "Shape.h"

class Joker : public Shape
{
public:
	virtual void setShape(const Point& head) override;
	virtual void move(char keypressed, bool erase) override;
	virtual void dropDown(int lowestLine) override;
	virtual bool checkAvailability(Board &board, char keyPressed) override;
	virtual string type() override;
	virtual void rotate()override;
};

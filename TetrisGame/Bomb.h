#pragma once

#include "Shape.h"

class Bomb : public Shape
{
	virtual void setShape(const Point& head)override;
	virtual void dropDown(int lowestLine)override;
	virtual string type() override;
	virtual void rotate() override;
};

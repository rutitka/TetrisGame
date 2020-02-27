#pragma once
#include "Shape.h"

class Plus : public Shape
{
public:
	virtual void setShape(const Point& head) override;
	virtual void dropDown(int lowestLine) override;
	virtual string type() override;
	virtual int getLowestAvailableLine(Board & board);
};
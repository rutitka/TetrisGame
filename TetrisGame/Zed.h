#pragma once
#include "Shape.h"

class Zed : public Shape
{
   void setShape(const Point& head) override;
   void dropDown(int lowestLine) override;
   virtual string type() override;
   virtual int getLowestAvailableLine(Board & board);
};
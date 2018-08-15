#ifndef POINT_H
#define POINT_H

#include "Point.h"

class Point
{
public:
    Point();
    Point(float, float);
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
private:
	float cx;
	float cy;
//
};

#endif // POINT_H

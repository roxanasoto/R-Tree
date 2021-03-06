#ifndef POINT_H
#define POINT_H
#include <cmath>
#include "Point.h"
using namespace std;

class Point
{
public:
    Point();
    Point(float, float);
	float getX();
	float getY();
	void setX(float x);
	void setY(float y);
 	float distanceToPoint(Point p);
 	float distanceToRect(Point A, Point B);
 	float distanceToSegment(Point A, Point B);

private:
	float cx;
	float cy;
//
};

#endif // POINT_H

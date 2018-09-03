#include "Point.h"


Point::Point(){}
Point::Point(float x, float y):cx(x),cy(y)
{
//
}
float Point::getX(){
    return this->cx;
}
float Point::getY(){
    return this->cy;
}

void Point::setX(float x)
{
	cx = x;
}

void Point::setY(float y)
{
	cy = y;
}
 float Point::distanceToPoint(Point p){
 	return sqrt(pow(p.cx-cx,2)+pow(p.cy-cy,2));
 }

float Point::distanceToRect(Point A, Point B){
	return abs((B.cx-A.cx)*(cy-A.cy)-(B.cy-A.cy)*(cx-A.cx))/sqrt(pow(B.cx-A.cx,2)+pow(B.cy-A.cy,2));
}
 float Point::distanceToSegment(Point A, Point B){
 	//hallamos el parametro U.
 	float u=((cx-A.cx)*(B.cx-A.cx)+(cy-A.cy)*(B.cy-A.cy))/(pow(B.cx-A.cx,2)+pow(B.cy-A.cy,2));
 	if(u<0)
 		return distanceToPoint(A);
 	else if(u>1)
 		return distanceToPoint(B);
 	else
 		return distanceToRect(A,B);

 }
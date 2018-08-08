#include "Point.h"


Point::Point(){}
Point::Point(int x, int y):cx(x),cy(y)
{
//
}
int Point::getX(){
    return this->cx;
}
int Point::getY(){
    return this->cy;
}

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

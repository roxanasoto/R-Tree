#include "Polygon.h"


Polygon::Polygon()
{
    points = new vector<Point>();
}
Polygon::Polygon(int n){
    //   this->no_points=n;
    // //   this->points = new vector<Point>();
    //   Point *newPoint;
    //   for(int i=0;i<n;i++){
    //     newPoint = new Point();
    //     this->points->push_back(*newPoint);
    //   }
    //
}
void Polygon::addPoint(float x,float y){
    Point pt(x,y);
    this->points->push_back(pt);
}
int Polygon::size(){
    return points->size();
    // return 0;
}
vector<Point> Polygon::getPoints(){
    return *points;
}

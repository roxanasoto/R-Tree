#ifndef POLYGON_H
#define POLYGON_H

#include "Point.h"
#include <vector>
using namespace std;
//
class Polygon
{
public:
    Polygon();
    Polygon(int n); //crear un poligo de n puntos
    void addPoint(float x,float y); //agrega punto al poligono
    int size(); //retornna numero de puntos del poligono
    vector<Point> getPoints();
    
private:
    vector<Point>* points;
    //std::vector<Point>* points;
    int no_points;
};

#endif // POLIGON_H

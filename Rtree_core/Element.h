#ifndef ELEMENT_H
#define ELEMENT_H
#include "vector"
#include "Region.h"
#include "Polygon.h"

class Element
{
    public:
        Element();
        Element(Polygon pol);
        int getOid();
		void setOid(int id);
        Region getMbr();
        Polygon getPolygon();
		float getAreaPol();
		void print();
        float distance;
        float distanceToPoint(Point p);
    private:
        int oid;
        Region mbr;
        Polygon poligono;
	Point punto;
};

#endif // ELEMENT_H

#ifndef ELEMENT_H
#define ELEMENT_H
#include "vector"
#include "Region.h"
#include "Polygon.h"

class Element
{
    public:
        int oid;
        Region mbr;
        Polygon poligono;
        Element();
        void buildMbr();
};

#endif // ELEMENT_H
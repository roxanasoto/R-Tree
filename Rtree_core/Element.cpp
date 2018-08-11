#include "Element.h"

Element::Element(){}

Element::Element(Polygon pol)
{
    poligono = pol;
   //Calcular la region 
   vector<Point> points = poligono.getPoints();
   float minX = points.at(0).getX();
   float minY = points.at(0).getY();
   float maxX = minX;
   float maxY = minY;
   for(int i = 1; i < points.size() ; i++)
   {
       Point temp = points.at(i);
       if(temp.getX() < minX)
       {
           minX = temp.getX();
       }
       else if(temp.getX() > maxX)
       {
           maxX = temp.getX();
       }

       if(temp.getY() < minY)
       {
           minY = temp.getY();
       }
       else if(temp.getY() > maxY)
       {
           maxY = temp.getY();
       }
      
   }
    mbr.coordMinX = minX;
    mbr.coordMinY = minY;
    mbr.coordX = maxX;
    mbr.coordY = maxY;
}

int Element::getOid()
{
    return oid;
}

Region Element::getMbr()
{
    return mbr;
}

Polygon Element::getPolygon()
{
    return poligono;
}
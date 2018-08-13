#include "Element.h"

Element::Element(){}

Element::Element(Polygon pol)
{
    poligono = pol;
   //Calcular la region 
   vector<Point> points = poligono.getPoints();
   int minX = points.at(0).getX();
   int minY = points.at(0).getY();
   int maxX = minX;
   int maxY = minY;
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

float Element::getAreaPol()
{
	//if (mbr != NULL)
	//{
		float axisX = mbr.coordX - mbr.coordMinX;
		float axisY = mbr.coordY - mbr.coordMinY;
		return axisX*axisY;
	//}
}

void Element::print()
{
	for (int i = 0; i < poligono.getPoints().size(); i++)
	{
		cout << "(" << poligono.getPoints().at(i).getX() << "," << poligono.getPoints().at(i).getY() << ") " ;
	}
	cout << endl;
}
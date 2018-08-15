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

void Element::setOid(int id)
{
	oid = id;
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


float Element::distanceToPoint(Point p){
  Point difference;
  int distanceResult;
  if (p.getX() > mbr.coordMinX)
  {
    if (p.getX() < mbr.coordX)
        difference.setX(0);
    else
      difference.setX(p.getX() - mbr.coordX);
  }
  else
  difference.setX(mbr.coordMinX - p.getX());
  if (p.getY() > mbr.coordMinY)
  {
    if (p.getY() < mbr.coordY)
      difference.setY(0);
    else
      difference.setY( p.getY() - mbr.coordY);
  }
  else
    difference.setY(mbr.coordMinY - p.getY());

  this->distance = sqrt(difference.getX()*difference.getX() + difference.getY()*difference.getY());
  return this->distance;
}
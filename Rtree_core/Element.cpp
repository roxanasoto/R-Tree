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

  vector<Point> poli=poligono.getPoints();
  distance=sqrt((p.getX()-poli[0].getX())*(p.getX()-poli[0].getX())+(p.getY()-poli[0].getY())*(p.getY()-poli[0].getY()));
  for(auto punto:poli)
  {
    float temp=sqrt((p.getX()-punto.getX())*(p.getX()-punto.getX())+(p.getY()-punto.getY())*(p.getY()-punto.getY()));
    if(temp<distance)
      distance=temp;
  }
  return this->distance;
}
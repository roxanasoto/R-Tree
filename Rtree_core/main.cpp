#include "RTree.h"
#include "Element.h"
int main()
{
    int n= 3;
    RTree* example = new RTree(n);
    //Puntos
    Point p1(3,5);
    Point p2(1,1);
    Point p3(3,1);
    Point p4(3,10);

    Element a;
    a.addPoint(p1);

    Element b;
    b.addPoint(p2);

    Element c;
    c.addPoint(p3);

    Element d;
    d.addPoint(p4);

    example->insertElement(a);
    example->insertElement(b);
    example->insertElement(c);
    example->insertElement(d);

}
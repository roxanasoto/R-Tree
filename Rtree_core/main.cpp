#include "RTree.h"
#include "Polygon.h"
int main()
{
    int n= 3;
    RTree* example = new RTree(n);
    
    Polygon p1;
    p1.addPoint(1,1);
    Polygon p2;
    p2.addPoint(1,3);
    Polygon p3;
    p3.addPoint(9,3);
    Polygon p4;
    p4.addPoint(6,3);
	Polygon p5;
	p5.addPoint(5, 3);

    example->insertElement(p1);
    example->insertElement(p2);
    example->insertElement(p3);
    example->insertElement(p4);
	example->insertElement(p5);
	example->insertElement(p6);

	example->printTree();

	getchar();
}
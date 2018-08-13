#include "RTree.h"
#include "Polygon.h"
int main()
{
    RTree* example = new RTree(3,1);
    
    Polygon p1;
    p1.addPoint(1,1);
    Polygon p2;
    p2.addPoint(1,4);
    Polygon p3;
    p3.addPoint(9,3);
    Polygon p4;
    p4.addPoint(6,3);
	Polygon p5;
	p5.addPoint(5,3);
	Polygon p6;
	p6.addPoint(1,7);
	Polygon p7;
	p7.addPoint(4,6);
	Polygon p8;
	p8.addPoint(2, 3);
	Polygon p9;
	p9.addPoint(3, 4);
	Polygon p10;
	p10.addPoint(3, 4);


    example->insertElement(p1);
    example->insertElement(p2);
    example->insertElement(p3);
    example->insertElement(p4);
	example->insertElement(p5);
	example->insertElement(p6);
	example->insertElement(p7);
	example->insertElement(p8);
	example->insertElement(p9);


	example->printTree();


	cout << "Query range" << endl;
	vector<Element> queryRange = example->queryRange(0, 0, 5, 4);
	for (int i = 0; i < queryRange.size(); i++)
	{
		cout << "Elemento " << i << endl;
		vector<Point> points = queryRange.at(i).getPolygon().getPoints();
		for (int j = 0; j < points.size(); j++)
		{
			cout << "(" << points.at(j).getX() << "," << points.at(j).getY() << ")" << endl;
		}
	}
	getchar();
}
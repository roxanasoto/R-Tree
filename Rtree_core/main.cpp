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
	Polygon p11;
	p11.addPoint(10, 4);
	Polygon p12;
	p12.addPoint(12, 4);
	Polygon p13;
	p13.addPoint(23, 4);
	Polygon p14;
	p14.addPoint(35, 4);
	Polygon p15;
	p15.addPoint(36, 4);



    example->insertElement(p1);
    example->insertElement(p2);
    example->insertElement(p3);
    example->insertElement(p4);
	example->insertElement(p5);
	example->insertElement(p6);
	example->insertElement(p7);
	example->insertElement(p8);
	example->insertElement(p9);
	example->insertElement(p10);

	example->insertElement(p8);
	example->insertElement(p9);
	example->insertElement(p10);

	example->insertElement(p11);
	example->insertElement(p12);
	example->insertElement(p13);
	example->insertElement(p14);
	example->insertElement(p15);
	example->printTree();


	cout << "Query range" << endl;
	vector<int> queryRange = example->queryRange(0, 0, 5, 4);
	for (int i = 0; i < queryRange.size(); i++)
	{
		cout << "Elemento " << i << endl;
		cout << "Elemento " << queryRange.at(i) << endl;
	//	vector<Point> points = queryRange.at(i).getPolygon().getPoints();
		/*for (int j = 0; j < queryRange.at(i).getPolygon().getPoints().size(); j++)
		{
			cout << "(" << queryRange.at(i).getPolygon().getPoints().at(j).getX() << "," << queryRange.at(i).getPolygon().getPoints().at(j).getY() << ")" << endl;
		}*/
	}


	getchar();
}
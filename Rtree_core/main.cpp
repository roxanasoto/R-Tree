#include "RTree.h"
#include "Polygon.h"

int main()
{
    RTree* example = new RTree(3,1);
    
    Polygon p1;
    p1.addPoint(259.25,269.25);
    Polygon p2;
    p2.addPoint(230.59,329.87);
    Polygon p3;
    p3.addPoint(402.36,152.45);
    Polygon p4;
    p4.addPoint(479.35,222.48);
	Polygon p5;
	p5.addPoint(84.848,92.858);
	Polygon p6;
	p6.addPoint(1,1);
	Polygon p7;
	p7.addPoint(2, 7);
	p7.addPoint(25, 25);
	p7.addPoint(2, 14);
	p7.addPoint(25, 56);

    example->insertElement(p1);
    example->insertElement(p2);
    example->insertElement(p3);
    example->insertElement(p4);
	example->insertElement(p5);
	example->insertElement(p6);
	example->insertElement(p7);
	example->printTree();


	cout << "Query range" << endl;
	vector<int> queryRange = example->queryRange(0, 0, 300, 350);
	for (int i = 0; i < queryRange.size(); i++)
	{
		//cout << "Elemento " << i << endl;
		cout << "Elemento " << queryRange.at(i) << endl;
	//	vector<Point> points = queryRange.at(i).getPolygon().getPoints();
		/*for (int j = 0; j < queryRange.at(i).getPolygon().getPoints().size(); j++)
		{
			cout << "(" << queryRange.at(i).getPolygon().getPoints().at(j).getX() << "," << queryRange.at(i).getPolygon().getPoints().at(j).getY() << ")" << endl;
		}*/
	}

	example->deleteTree();
	getchar();
}
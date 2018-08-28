#include "RTree.h"
#include "Polygon.h"

int main()
{
    RTree* example = new RTree(3,1);
    
    Polygon p1;
    p1.addPoint(1,1);
    Polygon p2;
    p2.addPoint(25,25);
    Polygon p3;
    p3.addPoint(50,50);
    Polygon p4;
    p4.addPoint(100,100);
	Polygon p5;
	p5.addPoint(150,150);
	Polygon p6;
	p6.addPoint(200,200);
	Polygon p7;
	p7.addPoint(300, 300);
	Polygon p8;
	p8.addPoint(500, 500);
	Polygon p9;
	p9.addPoint(600, 600);
	Polygon p10;
	p10.addPoint(700, 700);
	Polygon p11;
	p11.addPoint(800, 900);
	
	Polygon p12;
	p12.addPoint(800, 1);
	Polygon p22;
	p22.addPoint(700, 25);
	Polygon p32;
	p32.addPoint(600, 50);
	Polygon p42;
	p42.addPoint(500, 100);
	Polygon p52;
	p52.addPoint(400, 150);
	Polygon p62;
	p62.addPoint(350, 200);
	Polygon p72;
	p72.addPoint(300, 300);
	Polygon p82;
	p82.addPoint(250, 500);
	Polygon p92;
	p92.addPoint(200, 600);
	Polygon p102;
	p102.addPoint(100, 700);
	Polygon p112;
	p112.addPoint(10, 900);

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
	example->insertElement(p11);
	example->insertElement(p11);
	example->insertElement(p11);
	example->insertElement(p11);

	example->insertElement(p12);
	example->insertElement(p22);
	example->insertElement(p32);
	example->insertElement(p42);
	example->insertElement(p52);
	example->insertElement(p62);
	example->insertElement(p72);
	example->insertElement(p82);
	example->insertElement(p92);
	example->insertElement(p102);
	example->insertElement(p112);
	example->printTree();


	cout << "Query range" << endl;
	vector<int> queryRange = example->queryRange(500, 500, 700, 700);
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

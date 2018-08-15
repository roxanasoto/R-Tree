#include <vector>
//#include "Region.h"
#include "Element.h"

using namespace std;
class Node
{
	public:
		bool isLeaf;
		Region *region;
		//vector<Region> keyRegion;
		Node *parent;
		vector<Node*> children;
		//Node is leaf
		vector<Element> echildren;

		float getAreaNode();
		void updateRegion();
		static bool funcioncompare(Node* a,Node* b);
		static bool funcioncomparee(Element a,Element b);
		float distanceToPoint(Point p);
		void sort(Point p);
};
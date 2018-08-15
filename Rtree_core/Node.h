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
		Node();
		float getAreaNode();
		void updateRegion();

};
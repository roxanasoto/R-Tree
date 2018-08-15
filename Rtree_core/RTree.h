#include "Node.h"

using namespace std;
class RTree 
{
	private:
        Node* root = NULL;
        int degree; //valor de M
        int min; //m <= M/2
        int max; //M
        int countRegion;
		int countElem;

		vector<Region> listRegion;

		Node* chooseLeaf(Node *node, Element elem);
		float calcArea(Region nodeRegion, Region elemRegion);
		void splitNode(Node *node);
		void splitNodeInterno(Node *node);
		vector<float> getPointRegion();
		Region calcularMbr(Region regionNode, Region regionElem);
		void queryRangeInt(Node *node, Region regionSearch, vector<int> & result);
		void updateRegion(Region &regionBase, Region region);
		void updateRegion(Node* node, Element *elem);
		void print(Node *node);
		void deleteNode(Node *node);
    public:
        RTree(int max, int min);
        vector<float> insertElement( Polygon obj);
		vector<int> queryRange(float minX, float minY, float maxX, float maxY);
        vector<Element> queryNearest(Polygon obj, int k);
		int getCountElements();
		void deleteTree();
		void printTree();

};
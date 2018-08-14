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
		void updateRegion(Region &regionBase, Region region);

		vector<float> getPointRegion();

		Node* searchNode(Node *node, Region mbrObj);
		
		Region calcularMbr(Region regionNode, Region regionElem);
		void queryRangeInt(Node *node, Region regionSearch, vector<int> & result);
		void updateRegion(Node* node, Element *elem);
		void print(Node *node);
    public:
        RTree(int max, int min);
        vector<float> insertElement( Polygon obj);

		vector<int> queryRange(int minX, int minY, int maxX, int maxY);
        vector<Element> queryNearest(Polygon obj, int k);
		void printTree();
		void deleteTree();
		void deleteNode(Node *node);
		int getCountElements();

};
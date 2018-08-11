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

		Node* searchNode(Node *node, Region mbrObj);
		void splitNode(Node *node);
		Region calcularMbr(Region regionNode, Region regionElem);
		vector<Element> queryRangeInt(Node *node, Region regionSearch);
		void updateRegion(Node* node, Element *elem);
		void print(Node *node);
    public:
        RTree(int degree);
        bool insertElement( Polygon obj);
		vector<Element> queryRange(int minX, int minY, int maxX, int maxY);
        vector<Element> queryNearest(Polygon obj, int k);
		void printTree();

};
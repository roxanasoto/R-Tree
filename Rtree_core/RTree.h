#include "Node.h"

using namespace std;
class RTree 
{
    
        Node* root = NULL;
        int degree; //valor de M
        int min; //m <= M/2
        int max; //M
        
        //Maxlevel?
        int level;
    public:
        RTree(int degree);
        //bool insertElement(int minX, int minY, int maxX, int maxY, Element obj);
        bool insertElement( Element obj);
        bool deleteElement(Element obj);
        vector<Element> queryRange(int minX, int minY, int maxX, int maxY);
        vector<Element> queryNearest(Element obj, int k);
    //private:
        Node* searchRegion(Node *node, Region mbrObj);
        void splitNode(Node *node);
        bool balanceTree();
        void minimunBoudaringRegion();
        Region calcularMbr(Region regionNode, Region regionElem);
        vector<Element> queryRange(Node* node, Region regionSearch);
};
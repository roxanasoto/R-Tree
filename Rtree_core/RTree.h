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

    RTree(int degree);
    bool insertElement(int minX, int minY, int maxX, int maxY, Element obj);
    bool deleteElement(Element obj);
    vector<Element> queryRange(int minX, int minY, int maxX);
    vector<Element> queryNearest(Element obj, int k);
//private:
    void splitNode(Node &node);
    bool balanceTree();
    void minimunBoudaringRegion();
};
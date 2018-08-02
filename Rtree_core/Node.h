#include <vector>
#include "Region.h"
#include "Element.h"

using namespace std;
class Node
{
    public:
    //Informacion de que area abarca cada nodo
    bool isLeaf;
    bool isInterno;

    //Nodos internos
    vector<Region> rchildren;
    int r_children;

    //Nodos hojas contienen elementos
    vector<Element> echildren;
    int e_children;

    
};
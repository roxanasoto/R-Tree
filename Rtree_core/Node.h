#include <vector>
//#include "Region.h"
#include "Element.h"

using namespace std;
class Node
{
    public:
    //Informacion de que area abarca cada nodo
    bool isLeaf;

    //Puntero a array de key-regiones / nodo interno
   // Region* keyRegion;
   vector<Region> keyRegion;
   // Node* children;
   vector<Node*> children;
    int countKey;

    //Puntero a array de elementos / nodo hoja
    Node* parent;
    vector<Element> echildren;// Element* echildren;
    int countElement;

    //cada entrada  contiene el (mbr, oid)
    //mbr: espacio que contiene el objeto
    //oid identificador del objeto
    //element tambien deberia tener una region 
    //y un identificador

    //Minimo de entradas en el root es 2
    //Si root es hoja  entonces puede ser 0 o 1
    //Todas las hojas estan al mismo nivel
    
};
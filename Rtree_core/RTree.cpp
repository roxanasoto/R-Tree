#include "RTree.h"
using namespace std;
RTree::RTree(int degree)
{
    this->degree = degree;
    this->min = degree/2;
    this->max = degree;
    this->level = 0;
}

/*
    Insertar un nuevo elemento
*/
bool RTree::insertElement( Element obj)
{
    bool state =  true;
    // int minX, int minY, int maxX, int maxY representa el mbr del elemento
    if(root == NULL)
    {
        //Insertar el primer elemento
        Node newNode;
        newNode.isLeaf = true;
        newNode.countElement = 1;
        newNode.parent = NULL;
        newNode.echildren.push_back(obj);
        root = &newNode;
        //TODO regiones
    } 
    else if(root->isLeaf)
    {
        //Si es nodo hoja solo hay un nodo en el arbol
        //Verificamos si aun hay espacio para insertar
        if(root->countElement < max)
        {
            root->echildren.push_back(obj);
            root->countElement++;
        } 
        else if(root->countElement == max)
        {
            //se alcanzó el maximo numero de registros
            //Insertar y hacer split del nodo root
            root->echildren.push_back(obj);
            //TODO
            //Implicar evaluar la expansión mínima para cada region
            splitNode(root);
        }
        else
        {
            //Verificar caso
            state = false;
        }
    }
    else //Si no es hoja , root es nodo interno
    {
        //TODO
       // buscar donde debe insertarse 
       //Buscar si er mbr del objeto esta esta dentro de una region existente en el arbol
       //si existe una region insertar
       Node* node = searchRegion(root, obj.mbr); //Retorna un nodo interno h -1 //nodo interno donde puede ser insertado
       if(node != NULL)
       {
           //Buscar en que region de node->keyregion debs ser insertado
           Region minMbr = calcularMbr(node->keyRegion.at(0), obj.mbr);
           int idxTemp = 0;
           for(int i = 1 ; i <  node->keyRegion.size(); i++)
           {
               Region temp = calcularMbr(node->keyRegion.at(i), obj.mbr);
               if(temp < minMbr) // implementar
               {
                   minMbr = temp;
                   idxTemp = i;
               }
           }
           //Insertar en la hoja correspondiente a la region correspondiente
           node->children.at(idxTemp)->echildren.push_back(obj);
           if(node->echildren.size() > max)
           {
               splitNode(node->children.at(idxTemp));
           }
           else
           {
               //TODO actualizar el mbr de cada region
           }
           state = true;
       }
       else
       {
           //TODO

       }

    }

    return state;
}

/*
    Buscar la region donde debe ser insertado el elemento
    se debe elegir la region donde el area de modificacion sea la mínima
*/
Node* RTree::searchRegion(Node *node, Region mbrObj)
{
    Node* result = NULL;
    //Buscar nodo de un nivel anterior a las hojas
    Region minMbr = calcularMbr(node->keyRegion.at(0), mbrObj);
    int idx = 0;
    for(int i = 1 ; i <  node->keyRegion.size(); i++)
    {
        Region temp = calcularMbr(node->keyRegion.at(i), mbrObj);
        if(temp < minMbr) // implementar
        {
            minMbr = temp;
            idx = i;
        }
    }
    if(!(node->children(idx)->isLeaf))
    {
        searchRegion(node->children(idx));
    }
    return result;
}

/*
Split de un nodo, separar el nodo hoja / interno 
de forma que se cumpla lo requerido y que el mbr sea al minimo
una expasion mínima
*/

void RTree::splitNode(Node* node)
{
    //Dividir el nodo 
    //Convertir en padre a node y crear dos nodos hijos


    //Verificar si el arbol se encuentra al mismo nivel
}

/*
    Bpusqueda query range
*/
vector<Element> RTree::queryRange(int minX, int minY, int maxX, int maxY)
{
    //Buscamosregiones que este inluidas en 
    Region regionSearch;
    regionSearch.coordMinX = minX;
    regionSearch.coordX = maxX;
    regionSearch.coordMinY = minY;
    regionSearch.coordY = maxY;
    vector<Element> result = queryRange(root, regionSearch);

    return result;
}
vector<Element> queryRange(Node* node, Region regionSearch)
{
    //Buscar todas las regiones que forman interseccion con regionSearch
    vector<Element> result;
    if(!node->isLeaf)
    {
        //Examinar todas las regiones
        for(int i = 0; i < node->keyRegion.size(); i++)
        {
            //Consultar si keyregion(i).mbr insertsecta a sarchregion
            //Si intersecta buscar recursivamente a los hijos regiones
            //hasta encontrar los elemento que esten dentro del rectangulo
            Region region = node->keyRegion.at(i);
            if(!(regionSearch.coordMinY > region.coordY ||
                regionSearch.coordMinX > region.coordX ||
                regionSearch.coordY < region.coordMinY ||
                regionSearch.coordX < region.coordMinX ))
            {
               queryRange(node->children.at(i), regionSearch);
            }
        }   
    }
    else
    {
        //Examinar todas las regiones de los elementos estan contenidas en la region
        for(int i = 0; i < node->echildren.size(); i++)
        {
            //Verificar si el mbr del eleento esta dentro de la region
            Region regionObj = node->echildren.at(i).mbr;
            if(regionSearch.coordMinX <= regionObj.coordMinX &&
                 regionSearch.coordMinY <= regionObj.coordMinY &&
                 regionSearch.coordX >= regionObj.coordX &&
                 regionSearch.coordY >= regionObj.coordY )
            {
                result.push_back(node->echildren.at(i));
            }
            
        }    
    }
    return result;
}

/*
    Búsqueda de los k vecinos más cercanos
*/
vector<Element>RTree::queryNearest(Element obj, int k)
{
    
}

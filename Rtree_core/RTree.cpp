#include "RTree.h"

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
        newNode.echildren.push_back(&obj);
        root = &newNode;
        //TODO regiones
    } 
    else if(root->isLeaf)
    {
        //Si es nodo hoja solo hay un nodo en el arbol
        //Verificamos si aun hay espacio para insertar
        if(root->countElement < max)
        {
            root->echildren.push_back(&obj);
            root->countElement++;
        } 
        else if(root->countElement == max)
        {
            //se alcanzó el maximo numero de registros
            //Insertar y hacer split del nodo root
            root->echildren.push_back(&obj);
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
       //si existe uan region insertar
       Node* node = searchRegion(obj.mbr);
       if(node != NULL)
       {
           node->echildren.push_back(&obj);
           if(node->echildren.size() >= max + 1)
           {
               splitNode(node);
           }
           state = true;
       }
       else
       {
           //Buscar la posible region donde debe ser insertado 
           // establecer la expasión mínima
           //TODO

       }

    }

    return state;
}

/*
    Buscar la region donde debe ser insertado el elemento
*/
Node* RTree::searchRegion(Region mbrObj)
{
    Node* result = NULL;
    //TODO
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
#include "RTree.h"

RTree::RTree(int degree)
{
    this->degree = degree;
    this->min = degree/2;
    this->max = degree;
    this->level = 0;
}

bool RTree::insertElement(int minX, int minY, int maxX, int maxY, Element obj)
{
    // int minX, int minY, int maxX, int maxY representa el mbr del elemento
    if(root == NULL)
    {
        //Insertar el primer elemento
        Node newNode;
        newNode.isLeaf = true;
        newNode.countElement = 1;
        newNode.parent = NULL;
        root = &newNode;
    } 
    else if(root->isLeaf)
    {
        //Si es nodo hoja solo hay un nodo en el arbol
        //Verificamos si aun hay espacio para insertar
        if(root)
        {
            //Insertar y hacer split
            //splitNode(root);
        } 
        else 
        {

        }
    }
    else 
    {
       // Node node = searc
    }
}

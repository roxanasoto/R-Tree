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
    // int minX, int minY, int maxX, int maxY representa el mbb del elemento
    if(root == NULL)
    {
        //Insertar el primer elemento
        Node newNode;
        newNode.isLeaf = true;
        newNode.echildren.push_back(obj);
        newNode.e_children = 1;
        newNode.r_children = 0;
        root = &newNode;
        level = 0;
    } 
    else if(root->isLeaf)
    {
        //Si es nodo hoja verificamos si aun hay espacio
        if(root->e_children == max)
        {
            //Insertar y hacer split
            //splitNode(root);
        } 
        else 
        {

        }
    }
}

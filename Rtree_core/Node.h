#include "Element.h"
class Node
{
    //Informacion de que area abarca cada nodo
    private:
        int coordX;
        int coordeY;
        int width;
        int height;
        int count;
    Element* data;//nul si es una region
    Node* children;
};
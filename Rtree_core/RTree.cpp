#include "RTree.h"
using namespace std;

RTree::RTree(){}
RTree::RTree(int degree)
{
    this->degree = degree;
    this->min = degree/2;
    this->max = degree;
	countRegion = 0;
}

/*
    Insertar un nuevo elemento
*/
bool RTree::insertElement( Polygon pol)
{
    bool state =  true;
    Element obj(pol);
    if(root == NULL)
    {
        Node *newNode = new Node();
        newNode->isLeaf = true;
        newNode->parent = NULL;
        newNode->echildren.push_back(obj);
		updateRegion(newNode, &obj);
        root = newNode;
    } 
    else if(root->isLeaf)
    {
		root->echildren.push_back(obj);
		if (root->echildren.size() >= max)
		{
			splitNode(root);
		}
		else
		{
			updateRegion(root, &obj);
		}
    }
    else //Si no es hoja , root es nodo interno
    {
       
       Node* node = searchNode(root, obj.getMbr()); //Retorna un nodo hoja
       if(node != NULL)
       {
		   node->echildren.push_back(obj);
           if(node->echildren.size() > max)
           {
               splitNode(node);
           }
           else
           {
			   updateRegion(node->parent, &obj);
           }
           state = true;
       }
       else
       {
		   state = false;
       }
    }

    return state;
}

/*
	Actualizar el area de la region del nodo
*/
void RTree::updateRegion(Node *node, Element *elem)
{
	while (node != NULL)
	{
		if (node->region != NULL)
		{
			if (elem->getMbr().coordMinX < node->region->coordMinX)
				node->region->coordMinX = elem->getMbr().coordMinX;
			if (elem->getMbr().coordMinY < node->region->coordMinY)
				node->region->coordMinY = elem->getMbr().coordMinY;
			if (elem->getMbr().coordX > node->region->coordX)
				node->region->coordX = elem->getMbr().coordX;
			if (elem->getMbr().coordY > node->region->coordY)
				node->region->coordY = elem->getMbr().coordY;
		}
		else
		{
			Region region;
			region.coordMinX = elem->getMbr().coordMinX;
			region.coordMinY = elem->getMbr().coordMinY;
			region.coordX = elem->getMbr().coordX;
			region.coordY = elem->getMbr().coordY;
			node->region = &region;
		}
		node = node->parent;
	}
	
	
}

vector<Element> RTree::queryRangeInt(Node* node, Region regionSearch)
{
    //Buscar todas las regiones que forman interseccion con regionSearch
    vector<Element> result;
    if(!node->isLeaf)
    {
        //Examinar todas las regiones
        for(int i = 0; i < node->children.size(); i++)
        {
            //Consultar si keyregion(i).mbr insertsecta a sarchregion
            //Si intersecta buscar recursivamente a los hijos regiones
            //hasta encontrar los elemento que esten dentro del rectangulo
            Region region = *node->children.at(i)->region;
            if(!(regionSearch.coordMinY > region.coordY ||
                regionSearch.coordMinX > region.coordX ||
                regionSearch.coordY < region.coordMinY ||
                regionSearch.coordX < region.coordMinX ))
            {
               queryRangeInt(node->children.at(i), regionSearch);
            }
        }   
    }
    else
    {
        //Examinar todas las regiones de los elementos estan contenidas en la region
        for(int i = 0; i < node->echildren.size(); i++)
        {
            //Verificar si el mbr del eleento esta dentro de la region
            Region regionObj = node->echildren.at(i).getMbr();
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


vector<Element> RTree::queryRange(int minX, int minY, int maxX, int maxY)
{
    //Buscamosregiones que este inluidas en 
    Region regionSearch;
    regionSearch.coordMinX = minX;
    regionSearch.coordX = maxX;
    regionSearch.coordMinY = minY;
    regionSearch.coordY = maxY;
    vector<Element> result = queryRangeInt(root, regionSearch);

    return result;
}

/*
    Búsqueda de los k vecinos más cercanos
*/
vector<Element>RTree::queryNearest(Polygon obj, int k)
{
	vector<int> indexs_found;
    indexs_found.push_back(1);
    indexs_found.push_back(3);
    //logica para calcular cercanos
    //TODO: IMPLEMENTAR BUSQUEDA
    return indexs_found;
}

/*
Calcular la nueva region si se incluye el la region del elemento
*/
Region RTree::calcularMbr(Region regionNode, Region regionElem)
{
    Region result;
    result.coordMinX = (regionNode.coordMinX < regionElem.coordMinX)?regionNode.coordMinX:regionElem.coordMinX;
    result.coordMinY = (regionNode.coordMinY < regionElem.coordMinY)?regionNode.coordMinY:regionElem.coordMinY;
    result.coordX = (regionNode.coordX > regionElem.coordX)?regionNode.coordX:regionElem.coordX;
    result.coordY = (regionNode.coordY > regionElem.coordY)?regionNode.coordY:regionElem.coordY;
    return result;
}

/*
    Buscar la region donde debe ser insertado el elemento
    se debe elegir la region donde el area de modificacion sea la mínima
*/
Node*  RTree::searchNode(Node *node, Region mbrObj)
{
	if (node->isLeaf)
		return node;

	Region regionTemp = *node->children.at(0)->region;
	Region regionMin = calcularMbr(regionTemp, mbrObj);
	Node *nodeResult = new Node();
	nodeResult = node->children.at(0);
	for (int i = 1; i<node->children.size(); i++)
	{
		if (regionMin < calcularMbr(*node->children.at(i)->region, mbrObj))
		{
			regionMin = calcularMbr(*node->children.at(i)->region, mbrObj);
			nodeResult = node->children.at(i);
		}
	}

	return(searchNode(nodeResult, mbrObj));
}

/*
Split de un nodo, separar el nodo hoja / interno 
de forma que se cumpla lo requerido y que el mbr sea al minimo
una expasion mínima
*/

void  RTree::splitNode(Node* node)
{
	//Dividir el nodo 
	//Convertir en padre a node y crear dos nodos hijos
	//Elegiremos los nodos mas lejanos y agruparemos los que queden en medio
	//hacia el lado con el que formen el mbr mínimo
	if (node->isLeaf)
	{
		//Creamos los hijos y nodo region
		vector<Element> nodeLeft;
		vector<Element> nodeRight;
		int idxi = 0, idxy = 1;
		//Buscar el par de nodos con la distancia mas lejana
		Element e1 = node->echildren.at(0);
		Element e2 = node->echildren.at(1);
		double dist = sqrt(pow((e1.getMbr().coordX - e2.getMbr().coordX), 2) + pow((e1.getMbr().coordY - e2.getMbr().coordY), 2));
		for (int i = 0; i < node->echildren.size(); i++)
		{
			for (int j = 0; j < node->echildren.size() && j != i; j++)
			{
				double temp = sqrt(pow((node->echildren.at(i).getMbr().coordX - node->echildren.at(j).getMbr().coordX), 2) + pow((node->echildren.at(i).getMbr().coordY - node->echildren.at(j).getMbr().coordY), 2));
				if (temp < dist)
				{
					dist = temp;
					e1 = node->echildren.at(i);
					e2 = node->echildren.at(j);
					idxi = i;
					idxy = j;
				}
			}
		}

		nodeLeft.push_back(e1);
		Region *regionLeft = new Region();
		regionLeft->coordMinX = e1.getMbr().coordMinX;
		regionLeft->coordMinY = e1.getMbr().coordMinY;
		regionLeft->coordX = e1.getMbr().coordX;
		regionLeft->coordY = e1.getMbr().coordY;
		nodeRight.push_back(e2);
		Region *regionRight = new Region();
		regionRight->coordMinX = e2.getMbr().coordMinX;
		regionRight->coordMinY = e2.getMbr().coordMinY;
		regionRight->coordX = e2.getMbr().coordX;
		regionRight->coordY = e2.getMbr().coordY;

		Element elem;
		//agregamos los nodos 
		for (int i = 0; i < node->echildren.size(); i++)
		{
			//Calcular en mbb 
			if (idxi != i && idxy != i)
			{
				elem = node->echildren.at(i);
				if (calcularMbr(*regionLeft, elem.getMbr()) < calcularMbr(*regionRight, elem.getMbr()))
				{
					if (nodeLeft.size() <= max - min + 1)
					{
						nodeLeft.push_back(elem);
					}
					else
					{
						nodeRight.push_back(elem);
					}
				}
				else
				{
					if (nodeRight.size() <= max - min + 1)
					{
						nodeRight.push_back(elem);
					}
					else
					{
						nodeLeft.push_back(elem);
					}
				}
			}
		}

		//obtener las regiones de los nodos
		if (node->parent == NULL)
		{
			//Root
			Node *nuevoNodo = new Node();
			nuevoNodo->isLeaf = false;
			nuevoNodo->parent = NULL;
			Region* result = new Region();
			//result->id = ++countRegion;
			//nuevoNodo->region = ++countRegion;

			//Left leaf
			regionLeft->id = ++countRegion;
			Node *nuevoHijoLeft = new Node();
			nuevoHijoLeft->isLeaf = true;
			nuevoHijoLeft->echildren = nodeLeft;
			nuevoHijoLeft->parent = nuevoNodo;
			nuevoHijoLeft->region = regionLeft;
			nuevoNodo->children.push_back(nuevoHijoLeft);
			//Left Right
			regionRight->id = ++countRegion;
			Node *nuevoHijoRight = new Node();
			nuevoHijoRight->isLeaf = true;
			nuevoHijoRight->echildren = nodeRight;
			nuevoHijoRight->parent = nuevoNodo;
			nuevoHijoRight->region = regionRight;
			nuevoNodo->children.push_back(nuevoHijoRight);

			/*result->coordMinX = (regionLeft->coordMinX < regionRight->coordMinX) ? regionLeft->coordMinX : regionRight->coordMinX;
			result->coordMinY = (regionLeft->coordMinY < regionRight->coordMinY) ? regionLeft->coordMinY : regionRight->coordMinY;
			result->coordX = (regionLeft->coordX > regionRight->coordX) ? regionLeft->coordX : regionRight->coordX;
			result->coordY = (regionLeft->coordY > regionRight->coordY) ? regionLeft->coordY : regionRight->coordY;
			nuevoNodo->region = result;*/
			root = nuevoNodo;
		}
	}
	else
	{
		//Split region
	}

}

void RTree::printTree()
{
	//Comenzamos por el root que tiene el arreglo de regiones no es una region?
	for (int i = 0; i < root->children.size(); i++)
	{
		print(root->children.at(i));
	}
}

void RTree::print(Node *node)
{
	cout << "Region " << node->region->id;
	cout << "Min (" << node->region->coordMinX << "," << node->region->coordMinY<<")";
	cout << "-Max (" << node->region->coordX << "," << node->region->coordY << ")" << endl;
	if (node->isLeaf)
	{
		for (int i = 0; i < node->echildren.size(); i++)
		{
			if (node->parent != NULL)
			{
				cout << "Puntos poligono(Father: R" << node->parent->region->id << ") :" << endl;
			}
			else
			{
				cout << "Puntos poligono: " << endl;
			}
			node->echildren.at(i).print();
		}
	}
	else
	{
		for (int i = 0; i < node->children.size(); i++)
		{
			print(node->children.at(i));
		}
	}
}
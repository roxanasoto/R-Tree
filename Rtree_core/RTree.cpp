
#include "RTree.h"
using namespace std;

RTree::RTree(int max, int min)
{
	if (min <= max / 2 && min > 0)
	{
		this->degree = max;
		this->min = min;
		this->max = max;
		countRegion = 0; 
		countElem = 0;
		//Inicializamos la raiz como nodo hoja
		root = new Node();
		root->isLeaf = true;
		root->parent = NULL;
	}
	else
	{
		cout << "min debe ser mayor a cero y menos a max/2";
		throw runtime_error("min debe ser mayor a cero y menos a max/2");
	}
}

/*
Insertar un nuevo elemento
*/
vector<float> RTree::insertElement(Polygon pol)
{
	//bool state = true;
	Element obj(pol);
	obj.setOid(++countElem);
	if (root->isLeaf)
	{
		root->echildren.push_back(obj);
		if (root->echildren.size() > max)
			splitNode(root);
	}
	else
	{
		//Choose node leaf
		Node *leaf = chooseLeaf(root, pol);
		if (leaf->isLeaf)
		{
			leaf->echildren.push_back(obj);
			if (leaf->echildren.size() > max)
				splitNode(leaf);
		}
		else
		{
			//El nodo devuelto es una region
			//state = false;
			return getPointRegion();
		}
	}
	//return state;
	return getPointRegion();
}


/*
Choose leaft to insert
*/
Node* RTree::chooseLeaf(Node *node, Element elem)
{
	if (node->isLeaf)
		return node;
	//node is not leaf
	Node  *selectedNode = node->children[0];
	float areaRegion = selectedNode->getAreaNode();
	float areaRegionElement = calcArea(*selectedNode->region, elem.getMbr());
	//area aumentada
	float difMinArea = abs(areaRegion - areaRegionElement); //abs is necessary?
	float difMinTemp = 0;
	for (int i = 1; i < node->children.size(); i++)
	{
		areaRegion = node->children[i]->getAreaNode();
		areaRegionElement = calcArea(*node->children[i]->region, elem.getMbr());
		difMinTemp = abs(areaRegion - areaRegionElement);
		if (difMinTemp < difMinArea)
		{
			difMinArea = difMinTemp;
			selectedNode = node->children[i];
		}
	}

	return(chooseLeaf(selectedNode, elem));
}

/*
	Return area 
*/
float RTree::calcArea(Region nodeRegion, Region elemRegion)
{
	float maxX = (nodeRegion.coordX > elemRegion.coordX) ? nodeRegion.coordX : elemRegion.coordX;
	float minX = (nodeRegion.coordMinX < elemRegion.coordMinX) ? nodeRegion.coordMinX : elemRegion.coordMinX;
	float maxY = (nodeRegion.coordY > elemRegion.coordY) ? nodeRegion.coordY : elemRegion.coordY;
	float minY = (nodeRegion.coordMinY < elemRegion.coordMinY) ? nodeRegion.coordMinY : elemRegion.coordMinY;
	float axisX = maxX - minX;
	float axisY = maxY - minY;
	return axisX*axisY;

}

/*
	Actualiza los parametros de una region si se incluye una region(elemento/nodo)
*/
void RTree::updateRegion(Region &regionBase, Region region)
{
	if (regionBase.coordMinX != NULL && regionBase.coordX != NULL &&
		regionBase.coordMinY != NULL && regionBase.coordY != NULL)
	{
		if (region.coordMinX < regionBase.coordMinX)
			regionBase.coordMinX = region.coordMinX;
		if (region.coordMinY < regionBase.coordMinY)
			regionBase.coordMinY = region.coordMinY;

		if (region.coordX > regionBase.coordX)
			regionBase.coordX = region.coordX;
		if (region.coordY > regionBase.coordY)
			regionBase.coordY = region.coordY;
	}
	else
	{
		regionBase.coordMinX = region.coordMinX;
		regionBase.coordMinY = region.coordMinY;
		regionBase.coordX = region.coordX;
		regionBase.coordY = region.coordY;
	}
}

/*
Split de un nodo, separar el nodo hoja / interno
de forma que se cumpla lo requerido y que el mbr sea al minimo
una expasion mínima
*/

void  RTree::splitNode(Node* node)
{
	//Quadratic
	vector<Element> nodeLeft;
	vector<Element> nodeRigth;

	int idxElemI = -1;//Element elemI;
	int idxElemII = -1;//Element elemII;
	float areaElemI = 0;
	float areaElemII = 0;
	float areaJ = 0;
	float d = -10000; //largest d
	float temp = -1; //largest d
	for (int i = 0; i < node->echildren.size(); i++)
	{
		areaElemI = node->echildren[i].getAreaPol();
		for (int j = 0; j < node->echildren.size(); j++)
		{
			if (j != i)
			{
				areaElemII = node->echildren[j].getAreaPol();
				areaJ = calcArea(node->echildren[i].getMbr(), node->echildren[j].getMbr());
				//d = area(J) - area(E1I) - area{ E2).
				temp = areaJ - areaElemI - areaElemII;
				if (d < temp)
				{
					idxElemI = i;//elemI = node->echildren[i];
					idxElemII = j;//elemII = node->echildren[j];
					d = temp;
				}
			}
		}
	}

	//group
	Element elemI = node->echildren[idxElemI];
	Element elemII = node->echildren[idxElemII];
	nodeLeft.push_back(elemI);
	nodeRigth.push_back(elemII);
	Region *areaNodeLeft = new Region();
	updateRegion(*areaNodeLeft, elemI.getMbr());
	Region *areaNodeRigth = new Region();
	updateRegion(*areaNodeRigth, elemII.getMbr());

	float aumLeft = 0;
	float aumRight = 0;

	//Area de cada grupo
	areaElemI = (areaNodeLeft->coordX - areaNodeLeft->coordMinX)*(areaNodeLeft->coordY - areaNodeLeft->coordMinY); //area del grupo left
	areaElemII = (areaNodeRigth->coordX - areaNodeRigth->coordMinX)*(areaNodeRigth->coordY - areaNodeRigth->coordMinY);; // area de grupo right
	for (int i = 0; i < node->echildren.size(); i++)
	{
		if (!(i == idxElemI || i == idxElemII))
		{
			//d1 = el aumento de área requerido en el rectángulo de cobertura del Grupo 1 para incluir E.I.Calcule d2 de manera similar para el Grupo 2.

			aumLeft = calcArea(*areaNodeLeft, node->echildren.at(i).getMbr()) - areaElemI;
			aumRight = calcArea(*areaNodeRigth, node->echildren.at(i).getMbr()) - areaElemII;
			if (aumLeft < aumRight)
			{
				nodeLeft.push_back(node->echildren.at(i));
				updateRegion(*areaNodeLeft, node->echildren.at(i).getMbr());
			}
			else
			{
				nodeRigth.push_back(node->echildren.at(i));
				updateRegion(*areaNodeRigth, node->echildren.at(i).getMbr());
			}
		}
	}
	//node = noleaf
	//nodeLeft.push_back(elemI);
	//nodeRigth.push_back(elemII);
	
		if (node->parent == NULL) {
			node->isLeaf = false;
			node->echildren.clear();

			//Node region - left / rigth
			Node *regionLeft = new Node();
			regionLeft->isLeaf = true;
			areaNodeLeft->id = ++countRegion;
			regionLeft->region = areaNodeLeft;
			regionLeft->echildren = nodeLeft;
			
			listRegion.push_back(*areaNodeLeft);

			//Node region - left / rigth
			Node *regionRight = new Node();
			regionRight->isLeaf = true;
			areaNodeRigth->id = ++countRegion;
			regionRight->region = areaNodeRigth;
			regionRight->echildren = nodeRigth;

			listRegion.push_back(*areaNodeRigth);


			regionLeft->parent = node;//regionLeft->parent = node;
			regionRight->parent = node;
			node->children.push_back(regionLeft);
			node->children.push_back(regionRight);
			// actualizar region
		}
		else
		{

			//node = regionLeft;
			node->isLeaf = true;
			node->echildren.clear();
			areaNodeLeft->id = (node->region->id > 0) ? node->region->id : ++countRegion;
			node->region = areaNodeLeft;
			node->echildren = nodeLeft;
			//node->echildren
			listRegion.push_back(*areaNodeLeft);

			///Para nodeRight se crea una region la cual se insert como padre  de nodeleft y tio de node
		
			Node *regionRight = new Node();
			regionRight->isLeaf = true;
			areaNodeRigth->id = ++countRegion;
			regionRight->region = areaNodeRigth;
			regionRight->echildren = nodeRigth;
			regionRight->parent = node;

			listRegion.push_back(*areaNodeRigth);


			node->parent->children.push_back(regionRight);
			if (node->parent->children.size() > max)
			{
				splitNodeInterno(node->parent);
			}


			//insert node(new region) in parent y aplica split de nodo internos
			/*Node *nodeParent = node->parent;
			node->parent = nodeParent->parent;
			nodeParent->children.push_back(node);
			if (nodeParent->children.size() > max)
			{
				splitNodeInterno(nodeParent);
			}*/
		}
	

}

/*
	Split node interno
*/
void RTree::splitNodeInterno(Node *node)
{
	//Nodo interno  split 
	//Node agrupara los nodos creados a partir de node
	//Quadratic
	vector<Node*> nodeLeft;
	vector<Node*> nodeRigth;

	int idxElemI = -1;//Element elemI;
	int idxElemII = -1;//Element elemII;
	float areaElemI = 0;
	float areaElemII = 0;
	float areaJ = 0;
	float d = -10000; //largest d
	float temp = -1; //largest d
	for (int i = 0; i < node->children.size(); i++)
	{
		areaElemI = node->children[i]->getAreaNode();
		for (int j = 0; j < node->children.size(); j++)
		{
			if (j != i)
			{
				areaElemII = node->children[j]->getAreaNode();
				areaJ = calcArea(*node->children[i]->region, *node->children[j]->region);
				//d = area(J) - area(E1I) - area{ E2).
				temp = areaJ - areaElemI - areaElemII;
				if (d < temp)
				{
					idxElemI = i;//elemI = node->echildren[i];
					idxElemII = j;//elemII = node->echildren[j];
					d = temp;
				}
			}
		}
	}

	//group
	Node *elemI = node->children[idxElemI];
	Node *elemII = node->children[idxElemII];
	nodeLeft.push_back(elemI);
	nodeRigth.push_back(elemII);

	Region *areaNodeLeft = new Region();
	updateRegion(*areaNodeLeft, *elemI->region);
	Region *areaNodeRigth = new Region();
	updateRegion(*areaNodeRigth, *elemII->region);

	float aumLeft = 0;
	float aumRight = 0;

	//Area de cada grupo
	areaElemI = (areaNodeLeft->coordX - areaNodeLeft->coordMinX)*(areaNodeLeft->coordY - areaNodeLeft->coordMinY); //area del grupo left
	areaElemII = (areaNodeRigth->coordX - areaNodeRigth->coordMinX)*(areaNodeRigth->coordY - areaNodeRigth->coordMinY);; // area de grupo right
	for (int i = 0; i < node->children.size(); i++)
	{
		if (!(i == idxElemI || i == idxElemII))
		{
			//d1 = el aumento de área requerido en el rectángulo de cobertura del Grupo 1 para incluir E.I.Calcule d2 de manera similar para el Grupo 2.

			aumLeft = calcArea(*areaNodeLeft, *node->children.at(i)->region) - areaElemI;
			aumRight = calcArea(*areaNodeRigth, *node->children.at(i)->region) - areaElemII;
			if (aumLeft < aumRight)
			{
				nodeLeft.push_back(node->children.at(i));
				updateRegion(*areaNodeLeft, *node->children.at(i)->region);
			}
			else
			{
				nodeRigth.push_back(node->children.at(i));
				updateRegion(*areaNodeRigth, *node->children.at(i)->region);
			}
		}
	}
	
	if (node->parent == NULL) {
		node->isLeaf = false;
		node->children.clear();

		//Node region - left / rigth
		Node *regionLeft = new Node();
		regionLeft->isLeaf = false;
		areaNodeLeft->id = ++countRegion;
		regionLeft->region = areaNodeLeft;
		regionLeft->children = nodeLeft;

		listRegion.push_back(*areaNodeLeft);

		//Node region - left / rigth
		Node *regionRight = new Node();
		regionRight->isLeaf = false;
		areaNodeRigth->id = ++countRegion;
		regionRight->region = areaNodeRigth;
		regionRight->children = nodeRigth;

		listRegion.push_back(*areaNodeRigth);

		regionLeft->parent = node;
		regionRight->parent = node;
		node->children.push_back(regionLeft);
		node->children.push_back(regionRight);
		//actualizar region 
		node->updateRegion();
	}
	else
	{

		//node = regionLeft;
		node->isLeaf = false;
		node->children.clear();
		//areaNodeLeft->id = ++countRegion;
		areaNodeLeft->id = (node->region->id > 0)? node->region->id :++countRegion;
		node->region = areaNodeLeft;
		node->children = nodeLeft;
		//node->echildren
		listRegion.push_back(*areaNodeLeft);


		///Para nodeRight se crea una region la cual se insert como padre  de nodeleft y tio de node

		Node *regionRight = new Node();
		regionRight->isLeaf = false;
		areaNodeRigth->id = ++countRegion;
		regionRight->region = areaNodeRigth;
		regionRight->children = nodeRigth;
		regionRight->parent = node->parent;

		listRegion.push_back(*areaNodeRigth);


		node->parent->children.push_back(regionRight);
		if (node->parent->children.size() > max)
		{
			splitNodeInterno(node->parent);
		}

	}
}

/*
	convert region in parray point
*/
vector<float> RTree::getPointRegion()
{
	vector<float> listPoint;
	//Ordenar listRegion
	int  j;
	Region key;
	for (int i = 1; i < listRegion.size(); i++)
	{
		key = listRegion.at(i);
		j = i - 1;

		while (j >= 0 && listRegion.at(j).id > key.id)
		{
			listRegion.at(j + 1) = listRegion.at(j);
			j = j - 1;
		}
		listRegion.at(j + 1) = key;
	}

	for (int i = 0; i < listRegion.size(); i++)
	{
		//minx, min y, maxx, maxy
		listPoint.push_back(listRegion.at(i).coordMinX);
		listPoint.push_back(listRegion.at(i).coordMinY);
		listPoint.push_back(listRegion.at(i).coordX);
		listPoint.push_back(listRegion.at(i).coordY);
	}
	listRegion.clear();
	return listPoint;
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
			//Region region;
			node->region->coordMinX = elem->getMbr().coordMinX;
			node->region->coordMinY = elem->getMbr().coordMinY;
			node->region->coordX = elem->getMbr().coordX;
			node->region->coordY = elem->getMbr().coordY;
			//node->region->coordMinX = &region;
		}
		node = node->parent;
	}


}

void RTree::queryRangeInt(Node* node, Region regionSearch, vector<int> &result)
{
	//Buscar todas las regiones que forman interseccion con regionSearch
	
	if (!node->isLeaf)
	{
		//Examinar todas las regiones
		for (int i = 0; i < node->children.size(); i++)
		{
			//Consultar si keyregion(i).mbr insertsecta a sarchregion
			//Si intersecta buscar recursivamente a los hijos regiones
			//hasta encontrar los elemento que esten dentro del rectangulo
			Region region = *node->children.at(i)->region;
			if (!(regionSearch.coordMinY > region.coordY ||
				regionSearch.coordMinX > region.coordX ||
				regionSearch.coordY < region.coordMinY ||
				regionSearch.coordX < region.coordMinX))
			{
				queryRangeInt(node->children.at(i), regionSearch, result);
			}
		}
	}
	else
	{
		//Examinar todas las regiones de los elementos estan contenidas en la region
		for (int i = 0; i < node->echildren.size(); i++)
		{
			//Verificar si el mbr del eleento esta dentro de la region
			Region regionObj = node->echildren.at(i).getMbr();
			if (regionSearch.coordMinX <= regionObj.coordMinX &&
				regionSearch.coordMinY <= regionObj.coordMinY &&
				regionSearch.coordX >= regionObj.coordX &&
				regionSearch.coordY >= regionObj.coordY)
			{
				result.push_back(node->echildren.at(i).getOid());
			}

		}
	}
}


vector<int> RTree::queryRange(int minX, int minY, int maxX, int maxY)
{
	//Buscamosregiones que este inluidas en 
	Region regionSearch;
	regionSearch.coordMinX = minX;
	regionSearch.coordX = maxX;
	regionSearch.coordMinY = minY;
	regionSearch.coordY = maxY;
	vector<int> result;
	queryRangeInt(root, regionSearch, result);

	return result;
}

/*
Búsqueda de los k vecinos más cercanos
*/
vector<Element>RTree::queryNearest(Polygon obj, int k)
{
	vector<Element> result;
	return result;
}

/*
Calcular la nueva region que incluye el la region del elemento
*/
Region RTree::calcularMbr(Region regionNode, Region regionElem)
{
	Region result;
	result.coordMinX = (regionNode.coordMinX < regionElem.coordMinX) ? regionNode.coordMinX : regionElem.coordMinX;
	result.coordMinY = (regionNode.coordMinY < regionElem.coordMinY) ? regionNode.coordMinY : regionElem.coordMinY;
	result.coordX = (regionNode.coordX > regionElem.coordX) ? regionNode.coordX : regionElem.coordX;
	result.coordY = (regionNode.coordY > regionElem.coordY) ? regionNode.coordY : regionElem.coordY;
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
	Region temp;
	nodeResult = node->children.at(0);
	for (int i = 1; i<node->children.size(); i++)
	{
		temp = calcularMbr(*node->children.at(i)->region, mbrObj);
		if (regionMin < temp)
		{
			regionMin = temp;
			nodeResult = node->children.at(i);
		}
	}
	
	return(searchNode(nodeResult, mbrObj));
}

void RTree::deleteTree()
{
	
	deleteNode(root);
	countRegion = 0;
	countElem = 0;
	root = new Node();
	root->isLeaf = true;
	root->parent = NULL;
}

void RTree::deleteNode(Node *node)
{
	if (node == NULL)
		return;
	for (Node* child : root->children)
	{
		deleteNode(child);
	}
	delete node;
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
	cout << "Min (" << node->region->coordMinX << "," << node->region->coordMinY << ")";
	cout << "-Max (" << node->region->coordX << "," << node->region->coordY << ")" << endl;
	if (node->isLeaf)
	{
		for (int i = 0; i < node->echildren.size(); i++)
		{
			/*if (node->parent != NULL)
			{
				cout << "Puntos poligono(Father: R" << node->parent->region->id << ") :" << endl;
			}
			else
			{
				cout << "Puntos poligono: " << endl;
			}*/
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
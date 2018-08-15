#include "Node.h"
#include <algorithm>

Node::Node()
{
	region = NULL;
}

float Node::getAreaNode()
{
	if (region != NULL) 
	{
		float axisX = region->coordX - region->coordMinX;
		float axisY = region->coordY - region->coordMinY;
		return axisX*axisY;
	}
}

void Node::updateRegion()
{
	if (region != NULL)
	{
		for (int i = 0; i < children.size(); i++)
		{
			Region *regionTemp = children.at(i)->region;
			if (region->coordMinX > regionTemp->coordMinX)
				region->coordMinX = regionTemp->coordMinX;
			if (region->coordMinY > regionTemp->coordMinY)
				region->coordMinY = regionTemp->coordMinY;
			if (region->coordX < regionTemp->coordX)
				region->coordX = regionTemp->coordX;
			if (region->coordY < regionTemp->coordY)
				region->coordY = regionTemp->coordY;
		}
	}
}

bool Node::funcioncompare(Node* a,Node* b){
	return a->distance < b->distance;
}
bool Node::funcioncomparee(Element a,Element b){
	return a.distance < b.distance;
}
float Node::distanceToPoint(Point p){
	Point difference;
	int distanceResult;
	if (p.getX() > region->coordMinX)
	{
		if (p.getX() < region->coordX)
				difference.setX(0);
		else
			difference.setX(p.getX() - region->coordX);
	}
	else
	difference.setX(region->coordMinX - p.getX());
	if (p.getY() > region->coordMinY)
	{
		if (p.getY() < region->coordY)
			difference.setY(0);
		else
			difference.setY(p.getY() - region->coordY);
	}
	else
		difference.setY(region->coordMinY - p.getY());

	this->distance = sqrt(difference.getX()*difference.getX() + difference.getY()*difference.getY());
	return this->distance;
}
void Node::sort(Point p){
	if(this->isLeaf)
	{
		for(int i=0;i<echildren.size();i++){
			echildren[i].distanceToPoint(p);//mbr point
		}

		std::sort(echildren.begin(),echildren.end(),funcioncomparee);
	}
	else{
		for(int i=0;i<children.size();i++){
			children[i]->distanceToPoint(p);//mbr point
		}

		std::sort(children.begin(),children.end(),funcioncompare);
	}
	
}




#include "Node.h"
#include <algorithm>

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
	if (p.cx > region->coordMinX)
	{
		if (p.cx < region->coordX)
				difference.cx = 0;
		else
			difference.cx = p.cx - region->coordX;
	}
	else
	difference.cx = region->coordMinX - p.cx;
	if (p.cy > region->coordMinY)
	{
		if (p.cy < region->coordY)
			difference.cy = 0;
		else
			difference.cy = p.cy - region->coordY;
	}
	else
		difference.cy = region->coordMinY - p.cy;

	this->distance = sqrt(difference.cx*difference.cx + difference.cy*difference.cy);
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




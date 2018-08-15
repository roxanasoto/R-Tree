#include "Node.h"

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
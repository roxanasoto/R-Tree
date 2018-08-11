#include "Region.h"
using namespace std;

Region::Region()
{
    
}
Region::Region(int coordMinX, int coordMinY, int coordX, int coordY)
{
	this->coordMinX = coordMinX;
	this->coordMinY = coordMinY;
	this->coordX = coordX;
	this->coordY = coordY;
}
bool operator<( Region a , Region b) {
    //Verificar si region a es menor qque region b
    //distancia euclideana
    float disRegA =  sqrt(pow(a.coordX-a.coordMinX,2) + pow((a.coordY - a.coordMinY),2));
    float disRegB =  sqrt(pow(b.coordX-b.coordMinX,2) + pow((b.coordY - b.coordMinY),2));
    return disRegA < disRegB;
};
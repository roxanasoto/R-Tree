//MBR
#include <iostream>
#include <math.h>
using namespace std;
class Region
{
    public:
        int coordX;
        int coordY;
        int coordMinX;
        int coordMinY;
		int id;
        Region();
		Region(int coordMinX, int coordMinY, int coordX, int coordY);
        friend bool operator<( Region a , Region b);
        
};
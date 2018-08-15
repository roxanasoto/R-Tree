//MBR
#include <iostream>
#include <math.h>
using namespace std;
class Region
{
    public:
		float coordX;
		float coordY;
		float coordMinX;
		float coordMinY;
		float id;
        Region();
		Region(float coordMinX, float coordMinY, float coordX, float coordY);
        friend bool operator<( Region a , Region b);
        
};
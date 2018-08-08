//MBR
#include <iostream>
#include <math.h>
using namespace std;
class Region
{
    public:
        int coordX;
        int coordY;
        int width;//?
        int height;//?
        int coordMinX;
        int coordMinY;
        Region();
        friend bool operator<( Region a , Region b);
        
};
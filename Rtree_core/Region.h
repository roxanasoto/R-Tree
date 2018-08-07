//MBR
class Region
{
    public:
        int coordX;
        int coordY;
        int width;//?
        int height;//?
        int coordMinX;
        int coordMinY;

        bool operator<( Region objRegion,  Region objRegioncmp);
        
};
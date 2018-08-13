#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../../Rtree_core/Polygon.h"
#include "../../Rtree_core/RTree.h"
#include <iostream>
#include <vector>
using namespace std;

//c++ -O3 -Wall -shared -std=c++11 -fPIC `python2 -m pybind11 --includes`funcs.cpp wrap.cpp -o wrap`python2-config --exteuffix`x`

class vc{
    private:
        vector <float>* puntos ;
        RTree* rtree;
        int no_polygons;
    public: 
        vc(){
            puntos=new vector<float>();
            rtree = new RTree(3);
            no_polygons = 0;
        };
        void set_vector();
        void insert_coordinate(float);
        int vector_size();
        int rtree_size();
        bool rtree_insert(vector<float>);
        int vector_iterator(int index);
        // boost::python::list rangeQuery(boost::python::list pts);
        Polygon builPolygon(vector<float>pts);
        ~vc(){};
};

void vc::set_vector()
{
        // MBR pg1 (0,3,4,2,4);
        // MBR pg2  (1,4,3,6,7);
        // MBR pg3  (2,5,7,5,5);
        // puntos.push_back(pg1.getXmin());
        // puntos.push_back(pg1.getYmin());
        // puntos.push_back(pg1.getXmax());
        // puntos.push_back(pg1.getYmax());

        // puntos.push_back(pg2.getXmin());
        // puntos.push_back(pg2.getYmin());
        // puntos.push_back(pg2.getXmax());
        // puntos.push_back(pg2.getYmax());

        // puntos.push_back(pg3.getXmin());
        // puntos.push_back(pg3.getYmin());
        // puntos.push_back(pg3.getXmax());
        // puntos.push_back(pg3.getYmax());
    // for(int i=0;i<10;i++){
    //     this->vec.push_back(i);
    // }
        
}

int vc::vector_size()
{   
    return this->puntos->size();
}
int vc::rtree_size()
{   
    return this->no_polygons;
}
int vc::vector_iterator(int index)
{   
    if(this->puntos->size()> index)
        return  (*puntos)[index];
    return 0;
}
void vc::insert_coordinate(float cc){
    this->puntos->push_back(cc);
}
/**
  *Funcion que inserta un poligono en el R-Tree
  *Input: lista python de puntos
*/
bool vc::rtree_insert(vector<float> pts){
    Polygon p= builPolygon(pts);
    bool resultado = this->rtree->insertElement(p);
    if(resultado)
        this->no_polygons++;

    
    return resultado;
}
Polygon vc::builPolygon(vector<float>pts){
    // boost::python::ssize_t len = boost::python::len(pts);
    // double s=0;
    int len = pts.size();
    Polygon newPolygon;
    float cx, cy;

    int i=0;
    while(i<len){
        cx = pts[i];
        cy = pts[i+1];
        newPolygon.addPoint(cx,cy);
        i+=2;
    }
    return newPolygon;
}
// boost::python::list vc::rangeQuery(boost::python::list pts){
   
//     //resultado de consulta
//     Polygon p1;
//     p1.addPoint(1.112,4);
//     p1.addPoint(1.112,4);
//     p1.addPoint(1.1121,3);

//     Polygon p2;
//     p2.addPoint(2,8);
//     p2.addPoint(2,5.66);
//     p2.addPoint(2,3);
    
//     Polygon p3;
//     p3.addPoint(3,1);
//     p3.addPoint(3,9);
//     p3.addPoint(3,3);
    
//     Polygon p4;
//     p4.addPoint(4,9);
//     p4.addPoint(4,12);
//     p4.addPoint(4,11.0004);

//     vector<Polygon> queryResult;
//     queryResult.push_back(p1);
//     queryResult.push_back(p2);
//     queryResult.push_back(p3);
//     queryResult.push_back(p4);
//     //extraer puntos de los poligonos respuesta y convertirlos a python::list
//     boost::python::list list;
//     vector<Point> pg;
//     float x,y;
//     for(int i=0;i<queryResult.size();i++){
//         pg=queryResult[i].getPoints();
//         int j=0;
//         // list.append(pg.size());
//         while(j<pg.size()){
//             x=pg[j].getX();
//             y=pg[j].getY();
//             list.append(x);
//             list.append(y);
//             j+=1;
//         }
//     }
//     return list;
// }


namespace py = pybind11;

using namespace pybind11::literals;



PYBIND11_MODULE(mi_modulo, m) {
    // py::class_<Pet>(m, "Pet")
    //     .def(py::init<const std::string &>())
    //     .def("setName", &Pet::setName)
    //     .def("getName", &Pet::getName);


    py::class_<vc>(m,"vc")
        .def(py::init<>())
        .def("set_vector",&vc::set_vector)
        .def("vector_size",&vc::vector_size) 
        .def("rtree_size",&vc::rtree_size) 
        .def("vector_iterator",&vc::vector_iterator)
        .def("insert_coordinate",&vc::insert_coordinate)
        .def("rtree_insert",&vc::rtree_insert)
        // .def("rangeQuery",&vc::rangeQuery)
    ; 
}
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include "../../Rtree_core/Polygon.h"
#include "../../Rtree_core/RTree.h"
#include <iostream>
#include <vector>
#include <math.h>
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
            rtree = new RTree(6,1);
            no_polygons = 0;
        };
        void set_vector();
        void insert_coordinate(float);
        int vector_size();
        int rtree_size();
        vector<float> rtree_insert(vector<float>);
        int vector_iterator(int index);
        vector<int> rangeQuery(vector<float>);
        vector<int> nearestQuery(vector<int>,int);
        Polygon builPolygon(vector<float>pts);
        void delete_tree();
        ~vc(){};
        vector<float> test_insert();
};

void vc::set_vector()
{
    Polygon p1;
    p1.addPoint(1,1);
    Polygon p2;
    p2.addPoint(1,4);
    Polygon p3;
    p3.addPoint(9,3);
    Polygon p4;
    p4.addPoint(6,3);        
}

int vc::vector_size()
{   
    return this->puntos->size();
}
int vc::rtree_size()
{   
    return this->rtree->getCountElements();
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
void vc::delete_tree(){
    this->rtree->deleteTree();
}
/**
  *Funcion que inserta un poligono en el R-Tree
  *Input: lista python de puntos
*/
vector<float> vc::rtree_insert(vector<float> pts){
    Polygon p= builPolygon(pts);
    vector<float> mbr = this->rtree->insertElement(p);
    // if(resultado)
    //     this->no_polygons++;

    
    return mbr;
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
vector<int> vc::rangeQuery(vector<float> mbr){
   
    vector<int> ids =  this->rtree->queryRange((int) floor(mbr[0]), (int) floor(mbr[1]), (int) floor(mbr[2]), (int) floor(mbr[3]));
    // vector<int> ids;
    // ids.push_back((int) floor(mbr[0]+0.5));
    // ids.push_back((int) floor(mbr[1]+0.5));
    // ids.push_back((int) floor(mbr[2]+0.5));
    // ids.push_back((int) floor(mbr[3]+0.5));

//  ids.push_back(mbr[0]);
//  ids.push_back(mbr[1]);
//  ids.push_back(mbr[2]);
//  ids.push_back(mbr[3]);
    return ids;
}
vector<int> vc::nearestQuery(vector<int> punto, int k){
    Polygon pol;
    pol.addPoint(punto[0],punto[1]);
    vector<int> ids = this->rtree->queryNearest(pol,k);
    return ids;
}


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
        .def("rangeQuery",&vc::rangeQuery)
        .def("nearestQuery",&vc::nearestQuery)
        .def("delete_tree",&vc::delete_tree)
    ; 
}

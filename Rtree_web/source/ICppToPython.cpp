#include "../../Rtree_core/Polygon.h"
#include <iostream>
#include <vector>
using namespace std;

// typedef std::vector<MBR> MyList;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class Rtree{
    vector<Polygon>* regiones;
public:
    Rtree(){
        regiones = new vector<Polygon>();
    }
    void addRegion(Polygon p){
        regiones->push_back(p);
    }
    void insert(vector<int> puntos){
        Polygon newPolygon;
        int coorX,coorY;
        int index=0;
        while(index<puntos.size()){
            coorX = puntos[index];
            coorY = puntos[index+1];
            newPolygon.addPoint(coorX,coorY);
            index +=2;
        }
        this->regiones->push_back(newPolygon);
    }
    int getTreeSize(){
        return regiones->size();
    }

};


#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python/implicit.hpp>
using namespace boost::python;

class vc{
    private:
        vector <int>* puntos ;
        Rtree rtree;
    public: 
        vc(){
            puntos=new vector<int>();
            //rtree = Rtree();
        };
        void set_vector();
        void insert_coordinate(int);
        int vector_size();
        int rtree_size();
        void rtree_insert(boost::python::list pts);
        int vector_iterator(int index);
        boost::python::list rangeQuery(boost::python::list pts);
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
    return this->rtree.getTreeSize();
}
int vc::vector_iterator(int index)
{   
    if(this->puntos->size()> index)
        return  (*puntos)[index];
    return 0;
}
void vc::insert_coordinate(int cc){
    this->puntos->push_back(cc);
}
/**
  *Funcion que inserta un poligono en el R-Tree
  *Input: lista python de puntos
*/
void vc::rtree_insert(boost::python::list pts){
    boost::python::ssize_t len = boost::python::len(pts);
    double s=0;
    for(int i=0; i<len;i++){
        int p = boost::python::extract<int>(pts[i]);
        // int q = boost::python::extract<int>(pts[i]);
        this->puntos->push_back(p);
        //calculating..
    }
    this->rtree.insert(*puntos);
}
boost::python::list vc::rangeQuery(boost::python::list pts){
   
    //resultado de consulta
    Polygon p1;
    p1.addPoint(1,4);
    p1.addPoint(1,4);
    p1.addPoint(1,3);

    Polygon p2;
    p2.addPoint(2,8);
    p2.addPoint(2,5);
    p2.addPoint(2,3);
    
    Polygon p3;
    p3.addPoint(3,1);
    p3.addPoint(3,9);
    p3.addPoint(3,3);
    
    Polygon p4;
    p4.addPoint(4,9);
    p4.addPoint(4,12);
    p4.addPoint(4,11);

    vector<Polygon> queryResult;
    queryResult.push_back(p1);
    queryResult.push_back(p2);
    queryResult.push_back(p3);
    queryResult.push_back(p4);
    //extraer puntos de los poligonos respuesta y convertirlos a python::list
    boost::python::list list;
    vector<Point> pg;
    int x,y;
    for(int i=0;i<queryResult.size();i++){
        pg=queryResult[i].getPoints();
        int j=0;
        // list.append(pg.size());
        while(j<pg.size()){
            x=pg[j].getX();
            y=pg[j].getY();
            list.append(x);
            list.append(y);
            j+=1;
        }
    }
    return list;
}


//#include <Python.h>


// int load(){
//     ICppToPython app = ICppToPython(4);
//     return app.loadMbrs();
// }
// int main(){
//     ICppToPython app = ICppToPython();
//     cout<<"se añadio"<<app.loadPolygons()<<endl;
//     return 0;
// }

BOOST_PYTHON_MODULE(mi_modulo){
   
    // class_<std::vector<int> >("intVect")
    //     .def(vector_indexing_suite<std::vector<int> >())
    // ;
    // def("toPythonList", toPythonList);
    class_<vc>("vc", init<>())
        .def("set_vector",&vc::set_vector)
        .def("vector_size",&vc::vector_size) 
        .def("rtree_size",&vc::rtree_size) 
        .def("vector_iterator",&vc::vector_iterator)
        .def("insert_coordinate",&vc::insert_coordinate)
        .def("rtree_insert",&vc::rtree_insert)
        .def("rangeQuery",&vc::rangeQuery)
    ;  
    class_<Rtree>("Rtree")
        .def(init<>())
        .def(init<Rtree>())
        .def("insert", &Rtree::insert)
    ;
    class_<Polygon>("Polygon")
        .def(init<>())
        .def(init<Polygon>())
        .def(init<int>())
        .def("addPoint",&Polygon::addPoint)
    ;
    class_<Point>("Point")
        .def(init<>())
        .def(init<Point>())
        .def(init<int,int>())
        
    ;
}

// class_<ICppToPython>("ICppToPython",init<int>())
    // .def(init<>())
    // .def(init<ICppToPython>())
    // .def("loadMbrs", &ICppToPython::loadMbrs)
    // .def("getMbrs", &ICppToPython::getMbrs)
    // ;
    // class_<std::vector<int> >("MBRVect")
    //     .def(vector_indexing_suite<std::vector<int> >())
    // ;

    // class_<MBR>("MBR")
    //     .def(init<>())
    //     .def(init<MBR>())
    //     .def(init<int,int,int,int,int>())
    //     .def("getId", &MBR::getId)
    //     .def("getString", &MBR::getString)
    // ;
    
   
    // class_<MyList>("MyList")
    //     .def(vector_indexing_suite<MyList>() )
    // ;
    // class_<Polygon>("Polygon",init<int>())
    // ;

// #include <boost/python/suite/indexing/vector_indexing_suite.hpp>
// #include <boost/python/module.hpp>
// #include <boost/python/def.hpp>
// #include <boost/python/implicit.hpp>

// using namespace boost::python;

// struct X // a container element
// {
//     string s;

//     X():s("default") {}
//     X(string s):s(s) {}

//     string repr() const { return s; }
//     void reset() { s = "reset"; }
//     void foo() { s = "foo"; }
//     bool operator==(X const& x) const { return s == x.s; }
//     bool operator!=(X const& x) const { return s != x.s; }
// };

// string x_value(X const& x)
// {
//     return "gotya " + x.s;
// }

// BOOST_PYTHON_MODULE(vector_indexing_suite_ext)
// {    
//     class_<X>("X")
//         .def(init<>())
//         .def(init<X>())
//         .def(init<std::string>())
//         .def("__repr__", &X::repr)
//         .def("reset", &X::reset)
//         .def("foo", &X::foo)
//     ;

//     def("x_value", x_value);
//     implicitly_convertible<std::string, X>();
    
//     class_<std::vector<X> >("XVec")
//         .def(vector_indexing_suite<std::vector<X> >())
//     ;
        
//     // Compile check only...
//     class_<std::vector<float> >("FloatVec")
//         .def(vector_indexing_suite<std::vector<float> >())
//     ;
    
//     // Compile check only...
//     class_<std::vector<bool> >("BoolVec")
//         .def(vector_indexing_suite<std::vector<bool> >())
//     ;
    
//     // vector of strings
//     class_<std::vector<std::string> >("StringVec")
//         .def(vector_indexing_suite<std::vector<std::string> >())
//     ;
// }






#include <pybind11/pybind11.h>

//c++ -O3 -Wall -shared -std=c++11 -fPIC `python2 -m pybind11 --includes`funcs.cpp wrap.cpp -o wrap`python2-config --exteuffix`x`

int  add ( int  i ,  int  j )  { 
    return  i  +  j ; 
};

namespace py = pybind11;

using namespace pybind11::literals;

PYBIND11_PLUGIN(pybind) {
    py::module m("pybind", "pybind11 example plugin");
    m.def("add", &add, "A function which adds two numbers",
          "i"_a=1, "j"_a=2);
    return m.ptr();
}
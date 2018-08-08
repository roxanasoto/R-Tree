
#include <iostream>
#include <string>
#include <vector>
using namespace std;
//namespace { // Avoid cluttering the global namespace.
class Punto{
  private:
    int cx;
    int cy;
  public:
    Punto(int x, int y){
      this->cx=x;
      this->cy=y;
    }
    int getX(){
      return this->cx;
    }
    int getY(){
      return this->cy;
    }
};
class Poligono{
  public:
    vector<Punto>* puntos;
    int no_puntos;
  public:
    Poligono(){}
    Poligono(int no_puntos){
      this->no_puntos=no_puntos;
      this->puntos = new vector<Punto>();
    }
    void add(int x,int y){
      Punto pt(x,y);
      this->puntos->push_back(pt);
    }
    int size(){
      return puntos->size();
    }


};

#include <boost/python.hpp>
using namespace boost::python;

BOOST_PYTHON_MODULE(tree_ext)
{
    class_<Poligono>("Poligono").def(init<int>())
    // .add_property("puntos", 
    //  make_getter(&Poligono::puntos, return_value_policy<reference_existing_object>()),
    //  make_setter(&Poligono::puntos, return_value_policy<reference_existing_object>())) 
     .def("insertar", &Poligono::add).def("size",&Poligono::size)
    ;
}
  // A friendly class.
//   class hello
//   {
//     public:
//       hello(const std::string& country) { this->country = country; }
//       std::string greet() const { return "Hello from " + country; }
//     private:
//       std::string country;
//   };

//   // A function taking a hello object as an argument.
//   std::string invite(const hello& w) {
//     return w.greet() + "! Please come soon!";
//   }
// //}

// #include <boost/python.hpp>
// using namespace boost::python;

// BOOST_PYTHON_MODULE(tree_ext)
// {
//     // Create the Python type object for our extension class and define __init__ function.
//     class_<hello>("hello", init<std::string>())
//         .def("greet", &hello::greet)  // Add a regular member function.
//         .def("invite", invite)  // Add invite() as a regular function to the module.
//     ;

//     def("invite", invite); // Even better, invite() can also be made a member of module!!!
// }
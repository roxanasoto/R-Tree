from mi_modulo import *


###imprimir puntos de lista instanciada en c++
def imprimir_puntos(obj):
    size=obj.vector_size()
    for i in range(0,size):
        element = obj.vector_iterator(i)
        print element

###Leer datos y enviar a c++
def insertarPoligono(lpuntos):
    return lpuntos

###cargar datos de C++ a Python
lista = [2.43,3.65,4.68,2.09,6.77,7.88]
lista2 = [1,1,1,1,1,1]
vc_obj = vc() #este es una lista de puntos
#vc_obj.set_vector()
# for p in lista:
#     vc_obj.insert_coordinate(p)
#imprimir_puntos(vc_obj)p
print "rtree inicial size: "
print vc_obj.rtree_size()

print "el bool que devuleve insert es: "
print vc_obj.rtree_insert(lista2)
print vc_obj.rtree_insert(lista)
#imprimir_puntos(vc_obj)
# print vc_obj.rtree_size()
# vc_obj.rtree_insert(lista2)
# print vc_obj.rtree_size()
# vc_obj.rtree_insert([3,6,5,7])
print "rtree inicial size: "
print vc_obj.rtree_size()
# vc_obj.rtree_insert(lista)
# vc_obj.rtree_insert(lista)
# vc_obj.rtree_insert(lista)
# print "r-tree despues de 4 insert -size..."
# print vc_obj.rtree_size()

# print "prueba range query...input ;"
# result = vc_obj.rangeQuery([0.334,5.6612,.0126,7.0992,7.8889])
# print result






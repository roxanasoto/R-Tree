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
lista = [2,3,4,2,6,7]
lista2 = [1,1,1,1,1,1]
vc_obj = vc() #este es una lista de puntos
#vc_obj.set_vector()
# for p in lista:
#     vc_obj.insert_coordinate(p)
#imprimir_puntos(vc_obj)

vc_obj.rtree_insert(lista)
#imprimir_puntos(vc_obj)
# print vc_obj.rtree_size()
# vc_obj.rtree_insert(lista2)
# print vc_obj.rtree_size()
# vc_obj.rtree_insert([3,6,5,7])
# print vc_obj.rtree_size()

result = vc_obj.rangeQuery([4,5,6,7,7])
print result
for r in result:
    print r
# from tree_ext import *

# obj = Poligono(4)
# obj.insertar(3,5)
# obj.insertar(4,6)
# obj.insertar(5,7)
# print obj.size()

# from my_module import *
# # obj = my_module.ICppToPython()
# print my_module.load()



# mbr= MBR(2,1,2,3,4)
# # print mbr.getString()
# # mbrs_lista = MBRVect()
# # mbrs_lista[:]=[MBR(2,3,4,2,4),MBR(5,5,5,5,5),MBR(8,8,8,8,8)]

# def print_xvec(vector):
#     for x in vector: 
#         print x.getString()

# def extract_data(vector):
#     for pt in vector:
#         print pt
# # print_xvec(mbrs_lista)

# rtree = ICppToPython(5)
# pts = rtree.getMbrs()
# # lista = toPythonList()
# # extract_data(lista)
# extract_data(pts)






from mi_modulo import *
vc_obj = vc()
print vc_obj.rtree_size()
lista=[2.23,5,3.6,7]
poligon1=[282,150]
poligon2=[331,186]
print vc_obj.rtree_insert(lista)

# print vc_obj.rtree_insert(lista3)

# print vc_obj.rtree_insert(lista4)
print vc_obj.rtree_size()
print vc_obj.rtree_insert(poligon2)
print vc_obj.rtree_size()


print "prueba rango"

print vc_obj.rangeQuery([1.02, 3.7, 8.1, 8])
# lista=[2.23,5,3.6,7]
# print vc_obj.rtree_insert(lista)
# # print vc_obj.rtree_size()
# lista=[2.23,5,3.6,7]
# print vc_obj.rtree_insert(lista)
# # print vc_obj.rtree_size()
# lista=[2.23,5,3.6,7]
# print vc_obj.rtree_insert(lista)
# # print vc_obj.rtree_size()
# lista=[2.23,5,3.6,7]
# print vc_obj.rtree_insert(lista)
# # print vc_obj.rtree_size()
# lista=[2.23,5,3.6,7]
# print vc_obj.rtree_insert(lista)
# print vc_obj.rtree_size()
# print "Hello World!: "+ str(pybind.add(3, 4))
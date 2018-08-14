from mi_modulo import *
vc_obj = vc()
print vc_obj.rtree_size()
lista=[2.23,5,3.6,7]
lista2=[2.23,5,3.6,7]
lista3=[2.23,5,3.6,7]
lista4=[2.23,5,3.6,7]
print vc_obj.rtree_insert(lista)
print vc_obj.rtree_insert(lista2)
print vc_obj.rtree_insert(lista3)

print vc_obj.rtree_insert(lista4)
print vc_obj.rtree_size()

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
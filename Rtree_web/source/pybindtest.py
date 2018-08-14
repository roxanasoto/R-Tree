from mi_modulo import *
vc_obj = vc()
print vc_obj.rtree_size()
lista=[2.23,5,3.6,7]

poligon1=[282,150]
poligon2=[331,186]
# print vc_obj.rtree_insert(lista)

# print vc_obj.rtree_insert(lista3)

# print vc_obj.rtree_insert(lista4)
# print vc_obj.rtree_size()
# print vc_obj.rtree_insert(poligon2)
# print vc_obj.rtree_size()

# print "inserciones "
# vc_obj.rtree_insert([9.68,3.323])
# vc_obj.rtree_insert([6.43,3.89])
# vc_obj.rtree_insert([5.66,3.44])
# vc_obj.rtree_insert([1,7.5])
# vc_obj.rtree_insert([4,6.09])
# vc_obj.rtree_insert([2.65, 3])
# vc_obj.rtree_insert([3, 4])
# vc_obj.rtree_insert([3, 4.78])
# vc_obj.rtree_insert([10.44, 4.66])
# vc_obj.rtree_insert([23.66, 4.4])
# vc_obj.rtree_insert([35.21, 4])
# vc_obj.rtree_insert([36, 4.0987])

# print "size"
# print vc_obj.rtree_size()

# print "prueba rango"

# print str(vc_obj.rangeQuery([0, 0, 5, 4]))


print "prueba rango2"

vc_obj.rtree_insert([207,117])
vc_obj.rtree_insert([307,113])
vc_obj.rtree_insert([252,183])
vc_obj.rtree_insert([345,218])
vc_obj.rtree_insert([345,218])

print str(vc_obj.rangeQuery([163,230,218,-150]))

print "prueba knearest"
print vc_obj.rtree_nearestQuery(2,[2.8, 3.2])

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
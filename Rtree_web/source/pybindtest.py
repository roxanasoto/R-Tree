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


# [21:52, 15/8/2018] Roxana Maestria: [{"x":393.01171875,"y":55.41015625}]
# [21:52, 15/8/2018] Roxana Maestria: [{"x":298.01171875,"y":247.41015625}]
# [21:52, 15/8/2018] Roxana Maestria: [{"x":369.01171875,"y":373.41015625}]
# [21:52, 15/8/2018] Roxana Maestria: [{"x":153.01171875,"y":243.41015625}]
# [21:53, 15/8/2018] Roxana Maestria: [{"x":97.01171875,"y":536.41015625}]

vc_obj.rtree_insert([207,117])
vc_obj.rtree_insert([307,113])
vc_obj.rtree_insert([252,183])
vc_obj.rtree_insert([345,218])
vc_obj.rtree_insert([345,218])

print "rtree size"
print vc_obj.rtree_size()

print str(vc_obj.rangeQuery([163,230,218,-150]))

print "prueba delete tree"

vc_obj.delete_tree()
print vc_obj.rtree_size()
# print vc_obj.rtree_nearestQuery(2,[2.8, 3.2])

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
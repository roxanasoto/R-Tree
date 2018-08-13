from distutils.core import setup
from distutils.extension import Extension

hello_ext = Extension(
    'hello_ext'
    ,sources=['ICppToPython.cpp']
    ,libraries=['boost_python2.7']     # for python 3 use 'boost_python3-mt'
    # you may also want to add these
    ,extra_compile_args=['-std=c++11','-stdlib=libc++']
    ,extra_link_args=['-stdlib=libc++']
    )

setup(
    name='hello-world',
    version='0.1',
    ext_modules=[hello_ext])
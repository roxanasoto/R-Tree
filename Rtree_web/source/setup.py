import os, sys

from distutils.core import setup, Extension
from distutils import sysconfig
from pybind11 import get_include

# cpp_args = ['-std=c++11', '-stdlib=libc++', '-mmacosx-version-min=10.7']
ext_modules = [
    Extension(
    'pybind',
    ['pybind.cpp'],
    include_dirs=[get_include()],
    language='c++',
    # extra_compile_args = cpp_args,
    ),
]

setup(
    name='wrap',
    version='0.0.1',
    author='Cliburn Chan',
    author_email='cliburn.chan@duke.edu',
    description='Example',
    ext_modules=ext_modules,
)
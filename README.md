R-Tree
========

Demo online que muestra el funcionamiento de un R-Tree

Integrantes:
------------

1. Choqueluque Roman David
2. Lima Tinco Lizbeth
3. Soto Barrera Roxana

Instalacion (MAC OSX)
---------------------

La siguiente instalacion fue comprobada en OSX Sierra 10.12

REQUERIMIENTOS:
---------------

- Brew
- Python 2.7.15
- Pip
- Virtualenv

PASOS DE INSTALACION:
---------------------

## 1. INSTALAR  HOMEBREW

Para instalar las depencias necesarias para ejecutar la aplicacion se hara uso de brew, si no tiene instalado brew en su computador siga las siguientes instrucciones:

Instalar brew: Abra una terminal (consola) y pegue el siguiente comando:
- /usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"

Siga las instrucciones que se muestran en la terminal.

## 2. OBTENER COPIA LOCAL DEL CODIGO FUENTE

Puede obtener la copia local de la aplicacion de dos formas:

### 2.1 Descargando archivo comprimido: 
Para obtener el codigo fuente del proyecto puede descargarlo como .zip desde github en la siguiente direccion: https://github.com/roxanasoto/R-Tree
### 2.2 Clonando el repositorio: 
Si desea clonar el repositorio es necesario tener instalado git en su computador, si no lo tiene instalelo con el siguiente comando

- brew install git

Despues de obtener la copia local del proyecto, cree una nueva carpeta donde desee tener el código fuente de la aplicación.

Desde la terminal diríjase a la  carpeta que creo con el comando cd.

Si descargo el repositorio como .zip , simplemente descomprimalo en la carpeta que creo
Si esta usando Git Clone el repositorio con el comando:
		
- git clone https://github.com/roxanasoto/R-Tree.git

Deberia tener la siguiente estructura de carpetas:
	
	CarpetaCreada
    	└───R-Tree
			
## 3. Instalar python 2.7.15
La aplicacion trabaja con Python 2.7.15. Si no la tiene Instalela con el siguiente comando:

- brew install python@2

Nota: Recuerde que si tiene instalado otras versiones de python debe ejecutar los comandos con “python2”, por ejemplo para instalar un paquete con pip seria: pip2 install flask
 
## 4. Instalar virtualenv
Las dependencias del proyecto se instalaran en un entorno virtual, para crear un virtual enviroment es necesario tener instalado virtualenv, si no lo tiene instalelo  con el siguiente comando:

- pip2 install virtualenv

## 5. Crear un entorno virtual
Recuerde que debe crearlo en la carpeta que creo “Carpeta creada”. Ahora cree un entorno virtual donde se instalara las dependencias de la aplicacion:

Desde el terminal diríjase a la carpeta que creo anteriormente con el comando cd.
Cree el entorno virtual con el siguiente comando:

- virtualenv env --python=python2

Se creara el entorno virtual “env”. Ahora deberia tener la siguiente estructura de carpetas:

	CarpetaCreada
    	└───R-Tree
    	└───env

## 6. Activar el entorno virtual
Active el entorno virtual que creo con el siguiente comando:

- source env/bin/activate

El bash debe modificarse por ejemplo:


## 7. Instalar las dependencias
Recuerde que en la terminal estamos en la carpeta “CarpetaCreada” y tiene activa el entorno virtual que creo . Ahora instale las dependencias de la aplicacion con el siguiente comando:

- pip2 install -r R-Tree/requirements.txt

Al final de la instalación de las dependencias anteriores debería obtener el siguiente resultado en la consola:
Successfully installed Flask-1.0.2 Jinja2-2.10 MarkupSafe-1.0 WTForms-2.2.1 Werkzeug-0.14.1 click-6.7 itsdangerous-0.24

## 8. Construir el modulo (Binding)
Este proyecto extiende la aplicacion web de python mediante la creacion de un modulo en C++ que debe construirse desde cada sistema operativo, es decir debe obtener una libreria (modulo) de extension .so (.dll en windows) que permita la integracion de python y c++. Para ello realice los siguientes pasos:
### 8.1 Instalar pbind11:
Abra un nuevo terminal y pegue el siguiente comando: (Puede usar el mismo terminal pero debe desactivar el entorno con el siguiente comando: deactivate)

- pip2 install pybind11

### 8.2 Ir a la carpeta  /source: 
Para ello ejecute el siguiente comendo:

- cd R-Tree/Rtree_web/source

### 8.3 Construir el modulo: Para ello ejecute el siguiente comando

- g++ -O3 -Wall -shared -std=c++11 -undefined dynamic_lookup `python -m pybind11 --includes` pybind.cpp ../../Rtree_core/Polygon.cpp ../../Rtree_core/Point.cpp ../../Rtree_core/RTree.cpp  ../../Rtree_core/Element.cpp ../../Rtree_core/Region.cpp ../../Rtree_core/Node.cpp  -o mi_modulo`python-config --extension-suffix`
 
El comando anterior creara el archivo “mi_modulo.so” en la carpeta source (), si no tiene la extencion .so simplemente modifique el nombre agregandole la extension. (Nota:  es importante que el nombre del archivo generado sea: “mi_modulo.so”). 
La siguiente imagen muestra el módulo construido



## 9. Ejecutar la aplicacion (levantar el servidor)
Con la terminal en la carpeta source (path: carpetaCreada/R-Tree/Rtree_web/source) y el entorno virtual activado (bash: (env) $), ejecute la aplicacion con el comando:

- python2 run.py

Se levantara el servidor como se muestra en la siguiente imagen:


## 10. Visualizar la aplicacion
Con el servidor ya ejecutandose, abra su navegador(Chrome de preferencia) e ingrese a la siguiente ruta:
http://127.0.0.1:8001/rtree

Debe visualizar la siguiente interfaz:

`![sin conexion](https://drive.google.com/open?id=1gWyDpxOIPX7KgBrYBM8krdV94T-WNAYh)`


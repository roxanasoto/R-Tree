from flask import Flask,send_from_directory, flash
from flask import request
from flask import render_template
from wtforms import Form, TextField, TextAreaField, validators, StringField, SubmitField
######### modulos necesarios para comunicacion python - c++ ##############
from mi_modulo import *
from flask import request
from flask import render_template
import json

# App config.
DEBUG = True
app = Flask(__name__,template_folder='plantillas')
app.config.from_object(__name__)
app.config['SECRET_KEY'] = '7d441f27d441f27567d441f2b6176a'

class ReusableForm(Form):
    k_element = TextField('Elements for query nearest:', validators=[validators.required()])



@app.route('/rtree', methods=['GET', 'POST'])
def rtree():



    return render_template('ventana.html')


#################### Rtree #######################
vc_obj = vc()
####################################################

####insertar Poligono return regiones #######
@app.route('/insertar', methods =['POST','GET'])
def ajax_test():
    if(request.method=='POST'):
        #datos = request.POST.get_list('datos[]')
        datos = request.json
        #print("data is " + format(datos))
        puntos=[]
        for coordenada in datos:
            x = coordenada['x']
            y= coordenada['y']
            puntos.append(x)
            puntos.append(y)

        # for l in puntos:
        #print puntos


        resultadoRegiones = vc_obj.rtree_insert(puntos)
        print 'se inserto?: '+str(resultadoRegiones) + ', numero de poligonos en el arbol: '+str(vc_obj.rtree_size())
        dataResult = json.dumps(resultadoRegiones)
        # print("data is " + format(datos))
        # regiones=[puntos[0],puntos[1],400,400,puntos[0]+50,puntos[1]+50,200,200]
        dataResult=json.dumps(resultadoRegiones)
        return dataResult
        # return render_template('ventana.html',dataResult=json.dumps(puntosOutput))

        #print("data is " + format(datos))
        #return json.dumps(datos)

####################consultar Range #####################
@app.route('/rangeQuery', methods =['POST'])
def rangeQuery():

    datos = request.json
    puntosInput=[]
    #for coordenada in datos:
    x1 = datos[0]['x1']
    y1 = datos[0]['y1']
    x2 = datos[0]['x2']
    y2 = datos[0]['y2']
    puntosInput.append(x1)
    puntosInput.append(y1)
    puntosInput.append(x2)
    puntosInput.append(y2)

    #for coordenada in datos:
        #xmin = coordenada['x']
        #ymin= coordenada['y']
        #puntosInput.append(xmin)
        #puntosInput.append(ymin)
    ids = vc_obj.rangeQuery(puntosInput)
    #puntosOutput = [1,2,3,4,5]
    # print puntosOutput
    dataResult = json.dumps(ids)
    #print "llamado"
        #print("data is " + format(datos))
    return  dataResult
        #return render_template('ventana.html',dataResult=json.dumps(puntosOutput))

####################consultar Nearest #####################
@app.route('/nearestQuery', methods =['POST','GET'])
def nearestQuery():

    datos = request.json
    x = datos[0]['x']
    y = datos[0]['y']
    k = datos[1]

    #puntosOutput = vc_obj.rangeQuery(x,y,k)
    puntosOutput = [1,5,7]
    print puntosOutput
    dataResult = json.dumps(puntosOutput)

        #print("data is " + format(datos))
    return  dataResult
        #return render_template('ventana.html',dataResult=json.dumps(puntosOutput))
#################################################################
@app.route('/<path:path>')
def send_images(path):
    return send_from_directory('static',path)
#@app.route('/params')
#@app.route('/params/<name>/<int:num>')
#def parametros(name='valor por defecto', num='nada'):
 #   return 'el parametro es {}{}'.format(name,num)

if __name__ == '__main__':
    app.run(debug=True,port=8001)
#app.run()

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
    form = ReusableForm(request.form)

    # print form.errors
    if request.method == 'POST':
        k_element=request.form['k_element']
       # print name

        if form.validate():
            # Save the comment here.
            flash('Insert the count element:' + k_element )
        else:
            flash('All the form fields are required. ')


    return render_template('ventana.html',form=form)


#################### Rtree #######################
vc_obj = vc()
####################################################

####################insertar Poligono #####################
@app.route('/insertar', methods =['POST'])
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

        for l in puntos:
            print l


        vc_obj.rtree_insert(puntos)
        print vc_obj.rtree_size()

        #print("data is " + format(datos))
        return json.dumps(datos)

####################consultar #####################
@app.route('/rangeQuery', methods =['POST'])
def rangeQuery():

    datos = request.json
    puntosInput=[]
    for coordenada in datos:
        x = coordenada['x']
        y= coordenada['y']
        puntosInput.append(x)
        puntosInput.append(y)

    puntosOutput = vc_obj.rangeQuery(puntosInput)
    print puntosOutput
    dataResult = json.dumps(puntosOutput)

        #print("data is " + format(datos))
    return  render_template('ventana.html', dataResult=dataResult)
        #return render_template('ventana.html',dataResult=json.dumps(puntosOutput))

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

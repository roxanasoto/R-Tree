from flask import Flask,send_from_directory, flash
from flask import request
from flask import render_template
from wtforms import Form, TextField, TextAreaField, validators, StringField, SubmitField

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
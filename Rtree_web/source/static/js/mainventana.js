var perimeters = new Array();
var perimeter = new Array();
var complete = false;
var canvas = document.getElementById("jPolygon");
var ctx;
rect = {},drag = false;
//funciones para insertar punto
//document.addEventListener("keydown",function(ev){
    //console.log(ev.keyCode);
    //ev.preventDefault();
//});
////////////////////// Insertar poligono nuevo ///////////////////////
function test_func(){

}


$(document).ready(function(){
    console.log("codigo facilito");
    $('#b_ajax').click(function(){
        //console.log("aquiiiii");
        //console.log(perimeter);
        //console.log(JSON.stringify(perimeter));
        var url = "/insertar";

        $.ajax({
           type: 'POST',
           url: url,
           //dataType: 'json',
           contentType: "application/json",
           data: JSON.stringify(perimeter),
           success: function(response)
           {
                console.log(response);

           }
       });
    });
});
/////////////////////////////range query//////////////////////////////////////////
function consultarRegion()
{
    var url = "/rangeQuery";

    $.ajax({
            type: 'POST',
            url: url,
            contentType: 'application/json',
            data: JSON.stringify(perimeter),
            success: function(response) {
                console.log(response);
            }
    });


}
/////////////////////////////////////////////////////////////////////////

var funcEvent = function(ev) {
           console.log('evento activar punto');
           //var pointSize = 3;
           getPosition(ev);
};
function insertPoint(){
     canvas.addEventListener('click',funcEvent );
}

function getPosition(event){
console.log('gdibujando punto');
     var rect = canvas.getBoundingClientRect();
     var x = event.clientX - rect.left; // x == the location of the click in the document - the location (relative to the left) of the canvas in the document
     var y = event.clientY - rect.top; // y == the location of the click in the document - the location (relative to the top) of the canvas in the document

     // This method will handle the coordinates and will draw them in the canvas.
     drawCoordinates(x,y);
}

function drawCoordinates(x,y){
    var pointSize = 3; // Change according to the size of the point.
    //var ctx = document.getElementById("canvas").getContext("2d");
    ctx=canvas.getContext("2d");

    ctx.fillStyle = "#ff2626"; // Red color

    ctx.beginPath(); //Start path
    ctx.arc(x, y, pointSize, 0, Math.PI * 2, true); // Draw a point using the arc function of the canvas with a point structure.
    ctx.fill(); // Close the path and fill.
}

//funciones para insertar poligono

var funcEventPolygon = function(event) {
           console.log('evento activar poligono;');
           //var pointSize = 3;
           point_it(event);
};
function insertPolygon(){
     canvas.addEventListener('click',funcEventPolygon );
}

function line_intersects(p0, p1, p2, p3) {
    var s1_x, s1_y, s2_x, s2_y;
    s1_x = p1['x'] - p0['x'];
    s1_y = p1['y'] - p0['y'];
    s2_x = p3['x'] - p2['x'];
    s2_y = p3['y'] - p2['y'];

    var s, t;
    s = (-s1_y * (p0['x'] - p2['x']) + s1_x * (p0['y'] - p2['y'])) / (-s2_x * s1_y + s1_x * s2_y);
    t = ( s2_x * (p0['y'] - p2['y']) - s2_y * (p0['x'] - p2['x'])) / (-s2_x * s1_y + s1_x * s2_y);

    if (s >= 0 && s <= 1 && t >= 0 && t <= 1)
    {
        // Collision detected
        return true;
    }
    return false; // No collision
}

function point(x, y){
    ctx.fillStyle="red";
    ctx.strokeStyle = "blue";
    ctx.fillRect(x-2,y-2,4,4);
    ctx.moveTo(x,y);
}

function undo(){
    ctx = undefined;
    perimeter.pop();
    complete = false;
    start(true);
}

function clear_canvas(){
    ctx = undefined;
    perimeter = new Array();
    complete = false;
    document.getElementById('coordinates').value = '';
    start();
}

function draw(end){
    ctx.lineWidth = 1;
    ctx.strokeStyle = "white";
    ctx.lineCap = "square";
    ctx.beginPath();

    for(var i=0; i<perimeter.length; i++){
        if(i==0){
            ctx.moveTo(perimeter[i]['x'],perimeter[i]['y']);
            end || point(perimeter[i]['x'],perimeter[i]['y']);
        } else {
            ctx.lineTo(perimeter[i]['x'],perimeter[i]['y']);
            end || point(perimeter[i]['x'],perimeter[i]['y']);
        }
    }
    if(end){
        ctx.lineTo(perimeter[0]['x'],perimeter[0]['y']);
        ctx.closePath();
        ctx.fillStyle = 'rgba(255, 0, 0, 0.5)';
        ctx.fill();
        ctx.strokeStyle = 'blue';
        complete = true;
    }
    ctx.stroke();

    // print coordinates
    if(perimeter.length == 0){
        document.getElementById('coordinates').value = '';
    } else {
        document.getElementById('coordinates').value = JSON.stringify(perimeter);
    }
}

function check_intersect(x,y){
    if(perimeter.length < 4){
        return false;
    }
    var p0 = new Array();
    var p1 = new Array();
    var p2 = new Array();
    var p3 = new Array();

    p2['x'] = perimeter[perimeter.length-1]['x'];
    p2['y'] = perimeter[perimeter.length-1]['y'];
    p3['x'] = x;
    p3['y'] = y;

    for(var i=0; i<perimeter.length-1; i++){
        p0['x'] = perimeter[i]['x'];
        p0['y'] = perimeter[i]['y'];
        p1['x'] = perimeter[i+1]['x'];
        p1['y'] = perimeter[i+1]['y'];
        if(p1['x'] == p2['x'] && p1['y'] == p2['y']){ continue; }
        if(p0['x'] == p3['x'] && p0['y'] == p3['y']){ continue; }
        if(line_intersects(p0,p1,p2,p3)==true){
            return true;
        }
    }
    return false;
}

function point_it(event) {
    if(complete){
        alert('Polygon already created');
        return false;
    }
    var rect, x, y;

    if(event.ctrlKey || event.which === 3 || event.button === 2){
        if(perimeter.length==2){
            alert('You need at least three points for a polygon');
            return false;
        }
        x = perimeter[0]['x'];
        y = perimeter[0]['y'];
        if(check_intersect(x,y)){
            alert('The line you are drowing intersect another line');
            return false;
        }
        draw(true);
        alert('Polygon closed');
	    event.preventDefault();
        return false;
    } else {
        rect = canvas.getBoundingClientRect();
        x = event.clientX - rect.left;
        y = event.clientY - rect.top;
        if (perimeter.length>0 && x == perimeter[perimeter.length-1]['x'] && y == perimeter[perimeter.length-1]['y']){
            // same point - double click
            return false;
        }
        if(check_intersect(x,y)){
            alert('The line you are drowing intersect another line');
            return false;
        }
        perimeter.push({'x':x,'y':y});
        draw(false);
        return false;
    }
}

function start(with_draw) {
    var img = new Image();
    img.src = canvas.getAttribute('data-imgsrc');

    img.onload = function(){
        ctx = canvas.getContext("2d");
        ctx.drawImage(img, 0, 0, canvas.width, canvas.height);
        if(with_draw == true){
            draw(false);
        }
    }
}
//funciones para buscar elementos dentro de la region
function queryRange(){
    canvas.removeEventListener('click', funcEvent);
    console.log('desactivo?');
    //document.getElementById("punto").disabled = true;
    initRange();
}
function initRange() {
  canvas.addEventListener('mousedown', mouseDown, false);
  canvas.addEventListener('mouseup', mouseUp, false);
  canvas.addEventListener('mousemove', mouseMove, false);
}
  var Image;
function mouseDown(e) {
  rect.startX = e.pageX - this.offsetLeft;
  rect.startY = e.pageY - this.offsetTop;
Image=ctx.getImageData(0, 0, canvas.width, canvas.height);
  drag = true;
}
function mouseUp() {
  drag = false;
}
function mouseMove(e) {
  if (drag) {
    rect.w = (e.pageX - this.offsetLeft) - rect.startX;
    rect.h = (e.pageY - this.offsetTop) - rect.startY ;
    //ctx.clearRect(0,0,canvas.width,canvas.height);

    drawRegion();

  }
}
function drawRegion() {
    ctx.putImageData(Image, 0, 0);
    ctx.fillStyle = 'rgba(0, 0, 255, 0.25)';
    ctx.strokeStyle = 'red';
    ctx.strokeRect(rect.startX, rect.startY, rect.w, rect.h);

}
//funciones para buscar k elementos cercanos

function queryNearest(){
}

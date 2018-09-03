/*Declaración de variables*/
var perimeters = new Array();
var id=0;
var idsPerimeters =  new Array();
var perimeter = new Array();
var complete = false;
var canvas = document.getElementById("rTreeCanvas");
var ctx;
var numElement = 2;
var element = [];
var tree;
var ImageGlobal;
var ImageElem;
rect = {},
drag = false;


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
           data: JSON.stringify(perimeters[0]),
           success: function(response)
           {

                console.log(response);

           }
       });
    });
});

//funciones para limpiar la ventana
function clear_canvas(){
    ctx = undefined;
    perimeter = new Array();
    complete = false;
    document.getElementById('coordinates').value = '';
    start();
}
function clear_tree(){
    clear_canvas()
    perimeters=new Array();
    id=0;
    var url = "/clear";

    $.ajax({
       type: 'POST',
       url: url,
       //dataType: 'json',
       contentType: "application/json",
       data: JSON.stringify(1),
       success: function(response)
       {
            console.log('se limpio: ',response);

       }
   });
   canvas.removeEventListener('click', funcEventPoint);
    canvas.removeEventListener('click', funcEventPolygon);
    canvas.removeEventListener("click", funcNearestQuery);
initRemoveRange();
}
function start(with_draw) {
    var img = new Image();
    img.src = canvas.getAttribute('data-imgsrc');

    img.onload = function(){
        ctx = canvas.getContext("2d");
        ctx.drawImage(img, 0, 0, canvas.width, canvas.height);
        ImageGlobal=ctx.getImageData(0, 0, canvas.width, canvas.height);//Image for draw
        ImageElem=ctx.getImageData(0, 0, canvas.width, canvas.height); //Image for elements
        if(with_draw == true){
            draw(false);
        }
    }
}
//funciones insert point
function drawRegions(list) {

    ctx.fillStyle = '(0, 0, 255, 0.25)';
    ctx.strokeStyle = 'black';
    var idR=0;
    for(var i= 0;i<list.length;i=i+4){
    	ctx.strokeStyle = 'black'
    	ctx.font = "24px Arial";
    	ctx.lineWidth = 1;
        ctx.strokeText("R"+idR.toString(),list[i],list[i+1]);
        idR=idR +1;

        ctx.beginPath();
        ctx.strokeStyle = "#"+((1<<24)*Math.random()|0).toString(16);
        ctx.lineWidth = 4;
        ctx.strokeRect(list[i],list[i+1],list[i+2],list[i+3]);

        ctx.closePath();
    }


}
function drawCoordinatesPoint(x,y){
    var pointSize = 3; // Change according to the size of the point.
    //var ctx = document.getElementById("canvas").getContext("2d");
    //ctx=canvas.getContext("2d");

    ctx.fillStyle = "#ff2626"; // Red color

    ctx.beginPath(); //Start path
    ctx.arc(x, y, pointSize, 0, Math.PI * 2, true); // Draw a point using the arc function of the canvas with a point structure.
    ctx.fill(); // Close the path and fill.
}
function getPosition(eventPoint){
    console.log('gdibujando punto');
    var rectPoint = canvas.getBoundingClientRect();
    var x = eventPoint.clientX - rectPoint.left; // x == the location of the click in the document - the location (relative to the left) of the canvas in the document
    var y = eventPoint.clientY - rectPoint.top; // y == the location of the click in the document - the location (relative to the top) of the canvas in the document

    var point = new Array();
    point.push({'x':x,'y':y});
    perimeters.push(point);
    console.log(perimeters[id]);
    ctx.putImageData(ImageElem, 0, 0);

    document.getElementById('coordinates').value = JSON.stringify(point);

    // This method will handle the coordinates and will draw them in the canvas.
    drawCoordinatesPoint(x,y);
    ImageElem=ctx.getImageData(0, 0, canvas.width, canvas.height);
    /************/
    var url = "/insertar";

        $.ajax({
           type: 'POST',
           url: url,
           //dataType: 'json',
           contentType: "application/json",
           data: JSON.stringify(perimeters[id]),
           success: function(response)
           {

                console.log(response);
                var list=JSON.parse(response);
                console.log(list);
                drawRegions(list);
           }
       });
    ImageGlobal=ctx.getImageData(0, 0, canvas.width, canvas.height);
    /***********/
    id=id+1;
}
var funcEventPoint = function(eventPoint) {
    console.log('evento activar punto');
    //var pointSize = 3;
    getPosition(eventPoint);
};
function insertPoint(elem){
    alert("You actived the function INSERT POINT, read instrucctions");
    ctx.putImageData(ImageElem, 0, 0);
    canvas.addEventListener('click',funcEventPoint );
    canvas.removeEventListener('click', funcEventPolygon);
    initRemoveRange();
    canvas.removeEventListener("click", funcNearestQuery)
}
//funciones insert Poligono
function point(x, y){

    ctx.fillStyle="red";
    ctx.fill();
    ctx.lineWidth = 1;
    ctx.strokeStyle = "red";
    ctx.lineCap = "square";
    ctx.fillRect(x-2,y-2,4,4);
    ctx.moveTo(x,y);
}
function draw(end){
    ctx.beginPath();
    //ctx.lineWidth = 1;
    //ctx.strokeStyle = "orange";
    //ctx.lineCap = "square";


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
        ctx.fillStyle = 'orange';//colour for relleno of polygon
        ctx.fill();
        ctx.strokeStyle = 'orange';

    }
    ctx.stroke();

    // print coordinates
    if(perimeter.length == 0){
        document.getElementById('coordinates').value = '';
    } else {
        document.getElementById('coordinates').value = JSON.stringify(perimeter);
    }
}
function line_intersects(p0, p1, p2, p3) {
    console.log('create line_intersects for each polygon;');
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
function point_it(eventPolygon) {

    var rectPolygon, x, y;

    if(eventPolygon.ctrlKey || eventPolygon.metaKey || eventPolygon.which === 3 || eventPolygon.button === 2){
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
        ctx.putImageData(ImageElem, 0, 0);
        draw(true);
        perimeters.push(perimeter);
        ImageElem=ctx.getImageData(0, 0, canvas.width, canvas.height);

        /************/
        var url = "/insertar";

        $.ajax({
           type: 'POST',
           url: url,
           //dataType: 'json',
           contentType: "application/json",
           data: JSON.stringify(perimeters[id]),
           success: function(response)
           {

                console.log(response);
                var list=JSON.parse(response);
                drawRegions(list);

           }
          });
        id=id+1;
        ImageGlobal=ctx.getImageData(0, 0, canvas.width, canvas.height);

        /***********/
        perimeter = new Array();
        alert('Polygon closed');
        eventPolygon.preventDefault();
        return false;
    }
    else {
        rectPolygon = canvas.getBoundingClientRect();
        x = eventPolygon.clientX - rectPolygon.left;
        y = eventPolygon.clientY - rectPolygon.top;
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
var funcEventPolygon = function(eventPolygon) {
           console.log('event activar poligono;');

           //var pointSize = 3;
           point_it(eventPolygon);
};
function insertPolygon(elem){
    alert("You actived the function INSERT POLYGON, read instrucctions");
    console.log('function insertPolygon;');
    ctx.putImageData(ImageElem, 0, 0);
    canvas.addEventListener('click',funcEventPolygon );
    canvas.removeEventListener('click', funcEventPoint);
    initRemoveRange();
    canvas.removeEventListener("click", funcNearestQuery)
}
//funciones query Range
var pointsRectangle;
function drawRegion() {
    ctx.putImageData(ImageGlobal, 0, 0);
    ctx.fillStyle = 'rgba(0, 0, 255, 0.25)';
    ctx.strokeStyle = 'green';
    var x1 = rect.startX;
    var y1 = rect.startY;
    var x2 = rect.w;
    var y2 = rect.h;
    if(x2<0){
        x1=x1+x2;
        x2=-x2
    }

    if(y2<0){
        y1=y1+y2;
        y2=-y2
    }
    ctx.strokeRect(rect.startX, rect.startY, rect.w, rect.h);
    pointsRectangle= new Array();
    pointsRectangle.push({'x1':x1,'y1':y1,'x2':x2,'y2':y2 });


}
function mouseMove(e) {
  if (drag) {
    rect.w = (e.pageX - this.offsetLeft) - rect.startX;
    rect.h = (e.pageY - this.offsetTop) - rect.startY ;
    //ctx.clearRect(0,0,canvas.width,canvas.height);

    drawRegion();

  }
}
function mouseUp(){
  drag = false;
  document.getElementById('coordinates').value = JSON.stringify(pointsRectangle);
    //creo que esto no deberia ir
    //ctx.putImageData(Image, 0, 0);
    //
  var url = "/rangeQuery";
  $.ajax({
            type: 'POST',
            url: url,
         //dataType: 'json',
            contentType: "application/json",
            data: JSON.stringify(pointsRectangle),
            success: function(response)
            {

                console.log(response);
                var list=JSON.parse(response);

                reDrawElement(list);


            }
        });
}
function mouseDown(e) {
  rect.startX = e.pageX - this.offsetLeft;
  rect.startY = e.pageY - this.offsetTop;
 // Image=ctx.getImageData(0, 0, canvas.width, canvas.height);
  drag = true;
}

function initRange() {
  canvas.addEventListener('mousedown', mouseDown, false);
  canvas.addEventListener('mouseup', mouseUp, false);
  canvas.addEventListener('mousemove', mouseMove, false);
}
function initRemoveRange() {
  canvas.removeEventListener('mousedown', mouseDown, false);
  canvas.removeEventListener('mouseup', mouseUp, false);
  canvas.removeEventListener('mousemove', mouseMove, false);
}
function queryRange(elem){
    alert("You activated the function QUERY NEAREST, read instrucctions");
    console.log('function queryRange');
    canvas.removeEventListener('click', funcEventPoint);
    canvas.removeEventListener('click', funcEventPolygon);
    canvas.removeEventListener("click", funcNearestQuery);
    //document.getElementById("punto").disabled = true;
    initRange();
}
//funciones query Nearest
function reDrawElement(list){
    for(var i=0;i<list.length;i++){
        if(perimeters[list[i]].length <=2){
            var pointSize = 3*2; // Change according to the size of the point.

            ctx.fillStyle = "blue"; // Red color
            ctx.beginPath(); //Start path
            ctx.arc(perimeters[list[i]][0]['x'],perimeters[list[i]][0]['y'] , pointSize, 0, Math.PI * 2, true); // Draw a point using the arc function of the canvas with a point structure.
            ctx.fill(); // Close the path and fill.
            ctx.closePath();
        }
        else{

             ctx.beginPath();
             for(var j=0; j<perimeters[list[i]].length;j++){
                if(j==0){
                    ctx.moveTo(perimeters[list[i]][j]['x'],perimeters[list[i]][j]['y']);
                    //point(perimeters[list[i]][j]['x'],perimeters[list[i]][j]['y']);
                } else {
                    ctx.lineTo(perimeters[list[i]][j]['x'],perimeters[list[i]][j]['y']);
                    //point(perimeters[list[i]][j]['x'],perimeters[list[i]][j]['y']);
                }
             }


            ctx.lineTo(perimeters[list[i]][0]['x'],perimeters[list[i]][0]['y']);

            ctx.fillStyle = 'blue';//colour for relleno of polygon
            ctx.fill();
            ctx.strokeStyle = 'blue';
            ctx.stroke();
            ctx.closePath();

        }
    }
}
function buildNearest(eventPointQ){

    var rectPoint = canvas.getBoundingClientRect();

    var x = eventPointQ.clientX - rectPoint.left; // x == the location of the click in the document - the location (relative to the left) of the canvas in the document
    var y = eventPointQ.clientY - rectPoint.top; // y == the location of the click in the document - the location (relative to the top) of the canvas in the document

   // var x = eventPointQ.clientX;
    //var y = eventPointQ.clientY;

    var k=Number(document.getElementById("myNumberK").value);
    console.log(k);
    var pointMarker= new Array();
    pointMarker.push({'x':x,'y':y});
    //point.push(x);
    //point.push(y);
    //document.getElementById('coordinates').value = JSON.stringify(x,y);
    document.getElementById('coordinates').value = JSON.stringify(pointMarker);
    pointMarker.push({'k':k});

    ctx.putImageData(ImageGlobal, 0, 0);

    var url = "/nearestQuery";

    $.ajax({
        type: 'POST',
        url: url,
         //dataType: 'json',
        contentType: "application/json",
        data: JSON.stringify(pointMarker),
        success: function(response)
        {

            console.log(response);
            var list=JSON.parse(response);

            reDrawElement(list);


        }
     });

    //var idexf={{dataResult}};
}
var funcNearestQuery=function(event){
ctx.putImageData(ImageGlobal, 0, 0);
        buildNearest(event);
}
function queryNearest(elem){
    alert("You activated the function QUERY NEAREST, read instrucctions");
    console.log("function queryNearest");

    canvas.removeEventListener('click',funcEventPoint);
    canvas.removeEventListener('click', funcEventPolygon);
    initRemoveRange();
    //canvas.addEventListener("mousemove", funcNearestQuery)
    canvas.addEventListener("click", funcNearestQuery)


}

// dummy data
points = [];
const canv = document.getElementById("graph");

// populates dummy data randomly
for (let i = 0; i < 200; i++) {
    switch (i % 2) {
        case 0:
            points.push((i / 2) + 1);
            break;
        case 1:
            points.push(Math.floor(Math.random() * 100));
            break;
    }
}

// when the run button is pressed, this code is run
// the ajax call runs the python script and if it successful it updates the graph
document.getElementById("run").onclick = function() {
    var grassGrowthRate = "0.0078123";
    var grassEaten = "0.0010958904";
    var prairieDogGrowthRate = "0.001";
    var prairieDogDeathRate = "0.03";
    var timeSpan = document.getElementById("time-interval").value;
    var timeIncrement = "1.0";
    var prairieDogIV = document.getElementById("prairie-dogs").value;
    var grassIV = document.getElementById("vegetation").value;

    console.log(timeSpan);
    $.ajax({
        url: "./main.py",
        success: function(response) {
            console.log("It ran!");
        }
    });
};

var scale = 4;
canv.width = document.getElementById("graph").width * scale;
canv.height = document.getElementById("graph").height * scale;
initCanvas();

function getCurvePoints(pts, tension, isClosed, numOfSegments) {

    // use input value if provided, or use a default value   
    tension = (typeof tension != 'undefined') ? tension : 0.5;
    isClosed = isClosed ? isClosed : false;
    numOfSegments = numOfSegments ? numOfSegments : 16;

    var _pts = [],
        res = [], // clone array
        x, y, // our x,y coords
        t1x, t2x, t1y, t2y, // tension vectors
        c1, c2, c3, c4, // cardinal points
        st, t, i; // steps based on num. of segments

    // clone array so we don't change the original
    //
    _pts = pts.slice(0);

    // The algorithm require a previous and next point to the actual point array.
    // Check if we will draw closed or open curve.
    // If closed, copy end points to beginning and first points to end
    // If open, duplicate first points to befinning, end points to end
    if (isClosed) {
        _pts.unshift(pts[pts.length - 1]);
        _pts.unshift(pts[pts.length - 2]);
        _pts.unshift(pts[pts.length - 1]);
        _pts.unshift(pts[pts.length - 2]);
        _pts.push(pts[0]);
        _pts.push(pts[1]);
    } else {
        _pts.unshift(pts[1]); //copy 1. point and insert at beginning
        _pts.unshift(pts[0]);
        _pts.push(pts[pts.length - 2]); //copy last point and append
        _pts.push(pts[pts.length - 1]);
    }

    // ok, lets start..

    // 1. loop goes through point array
    // 2. loop goes through each segment between the 2 pts + 1e point before and after
    for (i = 2; i < (_pts.length - 4); i += 2) {
        for (t = 0; t <= numOfSegments; t++) {

            // calc tension vectors
            t1x = (_pts[i + 2] - _pts[i - 2]) * tension;
            t2x = (_pts[i + 4] - _pts[i]) * tension;

            t1y = (_pts[i + 3] - _pts[i - 1]) * tension;
            t2y = (_pts[i + 5] - _pts[i + 1]) * tension;

            // calc step
            st = t / numOfSegments;

            // calc cardinals
            c1 = 2 * Math.pow(st, 3) - 3 * Math.pow(st, 2) + 1;
            c2 = -(2 * Math.pow(st, 3)) + 3 * Math.pow(st, 2);
            c3 = Math.pow(st, 3) - 2 * Math.pow(st, 2) + st;
            c4 = Math.pow(st, 3) - Math.pow(st, 2);

            // calc x and y cords with common control vectors
            x = c1 * _pts[i] + c2 * _pts[i + 2] + c3 * t1x + c4 * t2x;
            y = c1 * _pts[i + 1] + c2 * _pts[i + 3] + c3 * t1y + c4 * t2y;

            //store points in array
            res.push(x);
            res.push(y);

        }
    }

    return res;
}

function drawLines(ctx, pts) {
    ctx.moveTo(pts[0], pts[1]);
    for (i = 2; i < pts.length - 1; i += 2) ctx.lineTo(pts[i], pts[i + 1]);
}

function drawCurve(ctx, ptsa, tension, isClosed, numOfSegments, showPoints) {

    ctx.beginPath();

    drawLines(ctx, getCurvePoints(ptsa, tension, isClosed, numOfSegments));

    if (showPoints) {
        ctx.beginPath();
        for (var i = 0; i < ptsa.length - 1; i += 2)
            ctx.rect(ptsa[i] - 2, ptsa[i + 1] - 2, 4, 4);
    }

    ctx.stroke();
}

function getCurvePoints(pts, tension, isClosed, numOfSegments) {
    // use input value if provided, or use a default value	 
    tension = (typeof tension != 'undefined') ? tension : 0.5;
    isClosed = isClosed ? isClosed : false;
    numOfSegments = numOfSegments ? numOfSegments : 16;

    var _pts = [],
        res = [], // clone array
        x, y, // our x,y coords
        t1x, t2x, t1y, t2y, // tension vectors
        c1, c2, c3, c4, // cardinal points
        st, t, i; // steps based on num. of segments

    // clone array so we don't change the original
    //
    _pts = pts.slice(0);

    // The algorithm require a previous and next point to the actual point array.
    // Check if we will draw closed or open curve.
    // If closed, copy end points to beginning and first points to end
    // If open, duplicate first points to befinning, end points to end
    if (isClosed) {
        _pts.unshift(pts[pts.length - 1]);
        _pts.unshift(pts[pts.length - 2]);
        _pts.unshift(pts[pts.length - 1]);
        _pts.unshift(pts[pts.length - 2]);
        _pts.push(pts[0]);
        _pts.push(pts[1]);
    } else {
        _pts.unshift(pts[1]); //copy 1. point and insert at beginning
        _pts.unshift(pts[0]);
        _pts.push(pts[pts.length - 2]); //copy last point and append
        _pts.push(pts[pts.length - 1]);
    }

    // ok, lets start..

    // 1. loop goes through point array
    // 2. loop goes through each segment between the 2 pts + 1e point before and after
    for (i = 2; i < (_pts.length - 4); i += 2) {
        for (t = 0; t <= numOfSegments; t++) {

            // calc tension vectors
            t1x = (_pts[i + 2] - _pts[i - 2]) * tension;
            t2x = (_pts[i + 4] - _pts[i]) * tension;

            t1y = (_pts[i + 3] - _pts[i - 1]) * tension;
            t2y = (_pts[i + 5] - _pts[i + 1]) * tension;

            // calc step
            st = t / numOfSegments;

            // calc cardinals
            c1 = 2 * Math.pow(st, 3) - 3 * Math.pow(st, 2) + 1;
            c2 = -(2 * Math.pow(st, 3)) + 3 * Math.pow(st, 2);
            c3 = Math.pow(st, 3) - 2 * Math.pow(st, 2) + st;
            c4 = Math.pow(st, 3) - Math.pow(st, 2);

            // calc x and y cords with common control vectors
            x = c1 * _pts[i] + c2 * _pts[i + 2] + c3 * t1x + c4 * t2x;
            y = c1 * _pts[i + 1] + c2 * _pts[i + 3] + c3 * t1y + c4 * t2y;

            //store points in array
            res.push(x);
            res.push(y);

        }
    }

    return res;
}

function drawLines(ctx, pts) {
    ctx.moveTo(pts[0], pts[1]);
    for (i = 2; i < pts.length - 1; i += 2) ctx.lineTo(pts[i], pts[i + 1]);
}

if (CanvasRenderingContext2D != 'undefined') {
    CanvasRenderingContext2D.prototype.drawCurve =
        function(pts, tension, isClosed, numOfSegments, showPoints) {
            drawCurve(this, pts, tension, isClosed, numOfSegments, showPoints)
        }
}

function initCanvas() {
    var ctx = canv.getContext("2d");
    var tension = .5;

    // find max values of x and y
    var maxX = 0;
    var maxY = 0;

    for (i = 0; i < points.length; i++) {
        switch (i % 2) {
            // x values
            case 0:
                if (points[i] > maxX) {
                    maxX = points[i];
                }
                break;
                // y values
            case 1:
                if (points[i] > maxY) {
                    maxY = points[i];
                }
                break;
        }
    }

    // scale values
    for (i = 0; i < points.length; i++) {
        switch (i % 2) {
            // x values
            case 0:
                points[i] = points[i] * canv.width / parseFloat(maxX) * .9;
                break;
            case 1:
                // compresses in the y direction further as well as a vertical shift down as to not have points cut off
                points[i] = points[i] * canv.height / parseFloat(maxY) * .75 + 100;
                break;
        }
    }

    console.log("Canvas initialized...")
    drawCurve(ctx, points, tension);
    console.log("Points drawn")
}
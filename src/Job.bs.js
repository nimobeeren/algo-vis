'use strict';

var React = require("react");
var Caml_array = require("bs-platform/lib/js/caml_array.js");
var Caml_int32 = require("bs-platform/lib/js/caml_int32.js");

var possibleColors = [
  "#ff0000",
  "#00ff00",
  "#0000ff",
  "#ff00ff",
  "#00ffff",
  "#ffff00"
];

function getColorString(i) {
  var c = Caml_array.caml_array_get(possibleColors, Caml_int32.mod_(i, possibleColors.length));
  console.log(i);
  return c;
}

function Job(Props) {
  var size = Props.size;
  var color = Props.color;
  return React.createElement("div", {
              style: {
                background: getColorString(color),
                display: "flex",
                fontSize: "20px",
                alignItems: "center",
                flexBasis: "0",
                flexGrow: String(size),
                justifyContent: "center"
              }
            }, size);
}

var make = Job;

exports.possibleColors = possibleColors;
exports.getColorString = getColorString;
exports.make = make;
/* react Not a pure module */

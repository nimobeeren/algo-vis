'use strict';

var React = require("react");
var LoadBalancing$AlgoVis = require("./LoadBalancing.bs.js");

var style = {
  display: "flex",
  height: "500px",
  width: "100%"
};

function BarPlot(Props) {
  var machines = Props.machines;
  LoadBalancing$AlgoVis.get_makespan(machines);
  return React.createElement("div", {
              style: style
            });
}

var make = BarPlot;

exports.style = style;
exports.make = make;
/* react Not a pure module */

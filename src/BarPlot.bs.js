'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var LoadBalancing$AlgoVis = require("./LoadBalancing.bs.js");

var barPlotStyle = {
  display: "flex",
  height: "500px",
  width: "100%",
  alignItems: "flex-end"
};

var barStyle = {
  background: "palevioletred",
  flexGrow: "1"
};

function BarPlot(Props) {
  var machines = Props.machines;
  var makespan = LoadBalancing$AlgoVis.get_makespan(machines);
  return React.createElement("div", {
              style: barPlotStyle
            }, $$Array.map((function (machine) {
                    var height = machine.load / makespan * 100;
                    return React.createElement("div", {
                                style: Object.assign({}, barStyle, {
                                      height: height.toString() + "%"
                                    })
                              });
                  }), machines));
}

var make = BarPlot;

exports.barPlotStyle = barPlotStyle;
exports.barStyle = barStyle;
exports.make = make;
/* react Not a pure module */

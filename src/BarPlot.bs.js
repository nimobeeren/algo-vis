'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var React = require("react");
var Job$AlgoVis = require("./Job.bs.js");
var LoadBalancing$AlgoVis = require("./LoadBalancing.bs.js");

var style = {
  display: "flex",
  height: "500px",
  width: "100%",
  alignItems: "flex-end"
};

function BarPlot(Props) {
  var machines = Props.machines;
  var makespan = LoadBalancing$AlgoVis.get_makespan(machines);
  return React.createElement("div", {
              style: style
            }, $$Array.map((function (machine) {
                    var height = machine.load / makespan * 100;
                    return React.createElement("div", {
                                key: String(machine.id),
                                style: {
                                  border: "1px solid",
                                  display: "flex",
                                  height: height.toString() + "%",
                                  flexFlow: "column nowrap",
                                  flexGrow: "1"
                                }
                              }, $$Array.map((function (job) {
                                      return React.createElement(Job$AlgoVis.make, {
                                                  size: job
                                                });
                                    }), $$Array.of_list(machine.jobs)));
                  }), machines));
}

var make = BarPlot;

exports.style = style;
exports.make = make;
/* react Not a pure module */

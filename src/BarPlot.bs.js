'use strict';

var List = require("bs-platform/lib/js/list.js");
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
                                  display: "flex",
                                  height: height.toString() + "%",
                                  flexFlow: "column nowrap",
                                  flexGrow: "1"
                                }
                              }, $$Array.init(List.length(machine.jobs), (function (i) {
                                      return React.createElement(Job$AlgoVis.make, {
                                                  size: List.nth(machine.jobs, i),
                                                  color: i + Math.imul(machine.id, Job$AlgoVis.possibleColors.length - 1 | 0) | 0
                                                });
                                    })));
                  }), machines));
}

var make = BarPlot;

exports.style = style;
exports.make = make;
/* react Not a pure module */

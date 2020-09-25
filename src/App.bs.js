'use strict';

var React = require("react");
var Layout$AlgoVis = require("./Layout.bs.js");
var BarPlot$AlgoVis = require("./BarPlot.bs.js");
var LoadBalancing$AlgoVis = require("./LoadBalancing.bs.js");

function App(Props) {
  var jobs = [
    3,
    2,
    1
  ];
  var result = LoadBalancing$AlgoVis.greedy(jobs, 2);
  return React.createElement(Layout$AlgoVis.make, {
              children: React.createElement(BarPlot$AlgoVis.make, {
                    machines: result
                  })
            });
}

var make = App;

exports.make = make;
/* react Not a pure module */

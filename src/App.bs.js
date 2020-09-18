'use strict';

var React = require("react");
var Layout$AlgoVis = require("./Layout.bs.js");
var BarPlot$AlgoVis = require("./BarPlot.bs.js");

function App(Props) {
  var machine1 = {
    jobs: {
      hd: 1,
      tl: {
        hd: 2,
        tl: /* [] */0
      }
    },
    load: 3
  };
  var machine2 = {
    jobs: {
      hd: 3,
      tl: /* [] */0
    },
    load: 3
  };
  var test_machines = [
    machine1,
    machine2
  ];
  return React.createElement(Layout$AlgoVis.make, {
              children: React.createElement(BarPlot$AlgoVis.make, {
                    machines: test_machines
                  })
            });
}

var make = App;

exports.make = make;
/* react Not a pure module */

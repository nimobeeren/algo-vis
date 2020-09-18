'use strict';

var React = require("react");

var style = {
  fontFamily: "sans-serif"
};

function App(Props) {
  return React.createElement("div", {
              style: style
            }, "sup");
}

var make = App;

exports.style = style;
exports.make = make;
/* react Not a pure module */

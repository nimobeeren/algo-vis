'use strict';

var React = require("react");

var style = {
  fontFamily: "sans-serif",
  margin: "0 auto",
  maxWidth: "800px",
  padding: "32px"
};

function Layout(Props) {
  var children = Props.children;
  return React.createElement("div", {
              style: style
            }, children);
}

var make = Layout;

exports.style = style;
exports.make = make;
/* react Not a pure module */

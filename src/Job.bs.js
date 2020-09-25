'use strict';

var React = require("react");

function Job(Props) {
  var size = Props.size;
  return React.createElement("div", {
              style: {
                border: "1px solid red",
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

exports.make = make;
/* react Not a pure module */

'use strict';

var React = require("react");
var ReactDom = require("react-dom");
var App$AlgoVis = require("./App.bs.js");

var root = document.querySelector("#root");

if (root == null) {
  throw {
        RE_EXN_ID: "Not_found",
        Error: new Error()
      };
}

ReactDom.render(React.createElement(App$AlgoVis.make, {}), root);

/* root Not a pure module */

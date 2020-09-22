'use strict';

var $$Array = require("bs-platform/lib/js/array.js");
var Caml_array = require("bs-platform/lib/js/caml_array.js");

function create_machine(param) {
  return {
          jobs: /* [] */0,
          load: 0
        };
}

function assign(job, machine) {
  return {
          jobs: {
            hd: job,
            tl: machine.jobs
          },
          load: machine.load + job | 0
        };
}

function greedy(jobs, m) {
  var machines = $$Array.init(m, (function (param) {
          return {
                  jobs: /* [] */0,
                  load: 0
                };
        }));
  $$Array.iter((function (job) {
          $$Array.sort((function (a, b) {
                  return a.load - b.load | 0;
                }), machines);
          return Caml_array.caml_array_set(machines, 0, assign(job, Caml_array.caml_array_get(machines, 0)));
        }), jobs);
  return machines;
}

function get_makespan(machines) {
  $$Array.sort((function (a, b) {
          return b.load - a.load | 0;
        }), machines);
  return Caml_array.caml_array_get(machines, 0).load;
}

exports.create_machine = create_machine;
exports.assign = assign;
exports.greedy = greedy;
exports.get_makespan = get_makespan;
/* No side effect */

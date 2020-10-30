open Jest;
open Expect;

type simpleMachine = {jobs: list(LoadBalancing.job)};

// Jest matcher that checks if an array of machines have the expected jobs.
// This is an attempt to ignore implementation details, such as machine ID
// and other internal values in the machine.
// Hopefully, this will make the tests a little more resilient to breaking.
let toMatchMachines =
    (expectedMachines: array(simpleMachine), actualMachinesAssertion) => {
  // Hacky way to get the value out of the Jest assertion
  let actualMachines: array(simpleMachine) = [%raw
    "actualMachinesAssertion.VAL"
  ];

  let actualSimpleMachines =
    Array.map(
      machine => {jobs: machine.jobs},
      actualMachines,
    );

  // When calling `_not |> toMatchMachines(...)`, a flag is set on the assertion
  // However, that inversion is not automatically applied to any assertions made
  // in this matcher! We therefore check the flag and apply _not as required.
  let isInvertedAssertion = [%raw "actualMachinesAssertion.NAME"] == "Not";
  if (isInvertedAssertion) {
    expect(expectedMachines) |> not_ |> toEqual(actualSimpleMachines);
  } else {
    expect(expectedMachines) |> toEqual(actualSimpleMachines);
  };
};

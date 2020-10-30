open Jest;
open Expect;

// Representation of a machine in its simplest form, stripped of any
// implementation details
type simpleMachine = list(LoadBalancing.job);

// Representation of a machine that is used to compare actual and expected
// machines
type partialMachine = {jobs: list(LoadBalancing.job)};

// Jest matcher that checks if an array of machines have the expected jobs.
// This is an attempt to ignore implementation details, such as machine ID and
// other internal values in the machine.
// Hopefully, this will make the tests a little more resilient to breaking.
// It currently fails when jobs/machines are in different order between actual
// and expected machines. Ideally, this would still pass, since their order
// does not affect the quality of the solution.
let toMatchMachines =
    (expectedMachines: array(simpleMachine), actualMachinesAssertion) => {
  // Hacky way to get the value out of the Jest assertion
  let actualMachines: array(LoadBalancing.machine) = [%raw
    "actualMachinesAssertion.VAL"
  ];

  let actualPartialMachines =
    Array.map(
      (machine: LoadBalancing.machine) => {jobs: machine.jobs},
      actualMachines,
    );
  let expectedPartialMachines = Array.map(simpleMachine => {jobs: simpleMachine}, expectedMachines);

  // When calling `_not |> toMatchMachines(...)`, a flag is set on the assertion
  // However, that inversion is not automatically applied to any assertions made
  // in this matcher! We therefore check the flag and apply _not as required.
  let isInvertedAssertion = [%raw "actualMachinesAssertion.NAME"] == "Not";
  if (isInvertedAssertion) {
    expect(expectedPartialMachines) |> not_ |> toEqual(actualPartialMachines);
  } else {
    expect(expectedPartialMachines) |> toEqual(actualPartialMachines);
  };
};

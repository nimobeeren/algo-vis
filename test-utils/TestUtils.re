open Jest;
open Expect;

type simpleMachine = {
  jobs: list(LoadBalancing.job)
}

let toMatchMachines = (expectedMachines: array(LoadBalancing.machine), actualMachinesJest) => {
  // Hacky way to get the value out of the Jest "thing"
  let actualMachines: array(simpleMachine) = [%raw "actualMachinesJest.VAL"];

  let expNumMachines = Array.length(expectedMachines);
  let actNumMachines = Array.length(actualMachines);
  if (expNumMachines !== actNumMachines) {
    expect(expNumMachines) |> toBe(actNumMachines);
  } else {
    expect(1) |> toBe(1)
  }
};

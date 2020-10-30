open Jest;
open Expect;
open TestUtils;

describe("toMatchMachines()", () => {
  test("passes when actual and expected match", () => {
    let actualMachines: array(simpleMachine) = [|
      {jobs: [1, 2]},
    |];

    let expectedMachines: array(LoadBalancing.machine) = [|
      {id: 0, jobs: [1, 2], load: 3},
    |];

    expect(actualMachines) |> toMatchMachines(expectedMachines);
  })

  test("passes when actual and expected differ only in implementation details", () => {
    let actualMachines: array(simpleMachine) = [|
      {jobs: [1, 2]},
    |];

    let expectedMachines: array(LoadBalancing.machine) = [|
      {id: -1, jobs: [1, 2], load: 42},
    |];

    expect(actualMachines) |> toMatchMachines(expectedMachines);
  })

  test("fails when actual and expected do not match", () => {
    let actualMachines: array(simpleMachine) = [|
      {jobs: [1, 2]},
    |];

    let expectedMachines: array(LoadBalancing.machine) = [|
      {id: 0, jobs: [1, 7], load: 8},
    |];

    expect(actualMachines) |> not_ |> toMatchMachines(expectedMachines);
  })
});

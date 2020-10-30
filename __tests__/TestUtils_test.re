open Jest;
open Expect;
open TestUtils;

describe("toMatchMachines()", () => {
  test("passes when actual and expected match", () => {
    let expectedMachines: array(simpleMachine) = [|[1, 2]|];

    let actualMachines: array(LoadBalancing.machine) = [|
      {id: 0, jobs: [1, 2], load: 3},
    |];

    expect(actualMachines) |> toMatchMachines(expectedMachines);
  });

  test(
    "passes when actual and expected differ only in implementation details", () => {
    let expectedMachines: array(simpleMachine) = [|[1, 2]|];

    let actualMachines: array(LoadBalancing.machine) = [|
      {id: (-1), jobs: [1, 2], load: 42},
    |];

    expect(actualMachines) |> toMatchMachines(expectedMachines);
  });

  test("fails when actual and expected do not match", () => {
    let expectedMachines: array(simpleMachine) = [|[1, 2]|];

    let actualMachines: array(LoadBalancing.machine) = [|
      {id: 0, jobs: [1, 7], load: 8},
    |];

    expect(actualMachines) |> not_ |> toMatchMachines(expectedMachines);
  });
});

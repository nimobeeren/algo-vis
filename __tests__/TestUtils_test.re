open Jest;
open Expect;
// It seems like the reason-vscode extension doesn't know how to resolve
// modules in other directories, which breaks error highlighting in the rest of
// the file :(
open TestUtils;

describe("toMatchMachines()", () => {
  test("passes when actual and expected match", () => {
    let expectedMachines: array(simpleMachine) = [|[1, 2], [5, 6]|];

    let actualMachines: array(LoadBalancing.machine) = [|
      {id: 0, jobs: [1, 2], load: 3},
      {id: 1, jobs: [5, 6], load: 11},
    |];

    expect(actualMachines) |> toMatchMachines(expectedMachines);
  });

  test(
    "passes when actual and expected differ only in implementation details", () => {
    let expectedMachines: array(simpleMachine) = [|[1, 2], [5, 6]|];

    let actualMachines: array(LoadBalancing.machine) = [|
      {id: (-1), jobs: [1, 2], load: 42},
      {id: 1234, jobs: [5, 6], load: 69},
    |];

    expect(actualMachines) |> toMatchMachines(expectedMachines);
  });

  test("fails when actual and expected do not match", () => {
    let expectedMachines: array(simpleMachine) = [|[1, 2], [11, 12], [21, 22]|];

    let actualMachines: array(LoadBalancing.machine) = [|
      {id: 0, jobs: [1, 2], load: 3},
      {id: 1, jobs: [11, 12], load: 23},
      {id: 2, jobs: [21, 88], load: 109},
    |];

    expect(actualMachines) |> not_ |> toMatchMachines(expectedMachines);
  });
});

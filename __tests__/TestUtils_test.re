open Jest;
open Expect;
open TestUtils;

describe("toMatchMachines()", () => {
  test("works", () => {
    let actualMachines: array(LoadBalancing.machine) = [|
      // {id: 0, jobs: [1, 2], load: 4},
    |];

    let expectedMachines: array(LoadBalancing.machine) = [|
      {id: 0, jobs: [1, 2], load: 3},
    |];

    expect(actualMachines) |> toMatchMachines(expectedMachines);
  })
});

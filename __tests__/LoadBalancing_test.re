open Jest;
open Expect;
// It seems like the reason-vscode extension doesn't know how to resolve
// modules in other directories, which breaks error highlighting in the rest of
// the file :(
open TestUtils;

describe("LoadBalancing", () => {
  describe("greedy()", () => {
    test("case 1 suboptimal", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;
      let expectedResult = [|
        [3, 1],
        [2],
      |];

      expect(LoadBalancing.greedy(jobs, m)) |> toMatchMachines(expectedResult);
    })
  });

  describe("bruteForce()", () => {
    test("case 1 optimal", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;
      let expectedResult = [|
        [2, 1],
        [3],
      |];

      expect(LoadBalancing.bruteForce(jobs, m)) |> toMatchMachines(expectedResult);
    });

    test("case 2 optimal", () => {
      let jobs = [|2, 3, 2, 2, 3|];
      let m = 2;
      let expectedResult = [|
        [2, 2, 2],
        [3, 3],
      |];

      expect(LoadBalancing.bruteForce(jobs, m)) |> toMatchMachines(expectedResult);
    });
  });

  describe("ptas()", () => {
    // test("case 1 suboptimal (eps=0.5)", () => {
    //   let jobs = [|1, 2, 3|];
    //   let m = 2;
    //   let expectedResult = [|
    //     [2, 1],
    //     [3],
    //   |];

    //   expect(LoadBalancing.ptas(jobs, m, 0.5)) |> toMatchMachines(expectedResult);
    // });

    // test("case 2 suboptimal (eps=0.5)", () => {
    //   let jobs = [|2, 3, 2, 2, 3|];
    //   let m = 2;
    //   let expectedResult = [|
    //     [2, 2, 2],
    //     [3, 3],
    //   |];

    //   expect(LoadBalancing.ptas(jobs, m, 0.5)) |> toMatchMachines(expectedResult);
    // });

    test("case 1 optimal (eps=0.0)", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;
      let expectedResult = [|
        [2, 1],
        [3],
      |];

      expect(LoadBalancing.ptas(jobs, m, 0.0)) |> toMatchMachines(expectedResult);
    });

    test("case 2 optimal (eps=0.0)", () => {
      let jobs = [|2, 3, 2, 2, 3|];
      let m = 2;
      let expectedResult = [|
        [2, 2, 2],
        [3, 3],
      |];

      expect(LoadBalancing.ptas(jobs, m, 0.0)) |> toMatchMachines(expectedResult);
    });
  });
});

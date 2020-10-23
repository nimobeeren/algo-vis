open Jest;
open Expect;

describe("LoadBalancing", () => {
  describe("greedy()", () => {
    // greedy() is suboptimal for this case, but ordered() is optimal
    test("case 1", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;
      let expectedResult: array(LoadBalancing.machine) = [|
        {id: 0, jobs: [3, 1], load: 4},
        {id: 1, jobs: [2], load: 2},
      |];

      expect(LoadBalancing.greedy(jobs, m)) |> toEqual(expectedResult);
    })
  });

  describe("bruteForce()", () => {
    // greedy() is suboptimal for this case, but ordered() is optimal
    test("case 1", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;
      let expectedResult: array(LoadBalancing.machine) = [|
        {id: 0, jobs: [2, 1], load: 3},
        {id: 1, jobs: [3], load: 3},
      |];

      expect(LoadBalancing.bruteForce(jobs, m)) |> toEqual(expectedResult);
    });

    // Both greedy() and ordered() are suboptimal for this case
    test("case 2", () => {
      let jobs = [|2, 3, 2, 2, 3|];
      let m = 2;
      let expectedResult: array(LoadBalancing.machine) = [|
        {id: 0, jobs: [2, 2, 2], load: 6},
        {id: 1, jobs: [3, 3], load: 6},
      |];

      expect(LoadBalancing.bruteForce(jobs, m)) |> toEqual(expectedResult);
    })
  });
});

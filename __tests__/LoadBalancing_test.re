open Jest;
open Expect;

describe("LoadBalancing", () => {
  describe("greedy()", () => {
    test("", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;
      let expectedResult: array(LoadBalancing.machine) = [|
        {id: 0, jobs: [3, 1], load: 4},
        {id: 1, jobs: [2], load: 2},
      |];

      expect(LoadBalancing.greedy(jobs, m)) |> toEqual(expectedResult);
    })
  })
});

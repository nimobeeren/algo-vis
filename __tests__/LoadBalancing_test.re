open Jest;
open Expect;

describe("LoadBalancing", () => {
  describe("greedy()", () => {
    test("case 1 suboptimal", () => {
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
    test("case 1 optimal", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;
      let expectedResult: array(LoadBalancing.machine) = [|
        {id: 0, jobs: [2, 1], load: 3},
        {id: 1, jobs: [3], load: 3},
      |];

      expect(LoadBalancing.bruteForce(jobs, m)) |> toEqual(expectedResult);
    });

    test("case 2 optimal", () => {
      let jobs = [|2, 3, 2, 2, 3|];
      let m = 2;
      let expectedResult: array(LoadBalancing.machine) = [|
        {id: 0, jobs: [2, 2, 2], load: 6},
        {id: 1, jobs: [3, 3], load: 6},
      |];

      expect(LoadBalancing.bruteForce(jobs, m)) |> toEqual(expectedResult);
    });
  });

  describe("ptas()", () => {
    // test("case 1 suboptimal (eps=0.5)", () => {
    //   let jobs = [|1, 2, 3|];
    //   let m = 2;
    //   let expectedResult: array(LoadBalancing.machine) = [|
    //     {id: 0, jobs: [2, 1], load: 3},
    //     {id: 1, jobs: [3], load: 3},
    //   |];

    //   expect(LoadBalancing.ptas(jobs, m, 0.5)) |> toEqual(expectedResult);
    // });

    // test("case 2 suboptimal (eps=0.5)", () => {
    //   let jobs = [|2, 3, 2, 2, 3|];
    //   let m = 2;
    //   let expectedResult: array(LoadBalancing.machine) = [|
    //     {id: 0, jobs: [2, 2, 2], load: 6},
    //     {id: 1, jobs: [3, 3], load: 6},
    //   |];

    //   expect(LoadBalancing.ptas(jobs, m, 0.5)) |> toEqual(expectedResult);
    // });

    test("case 1 optimal (eps=0.0)", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;
      let expectedResult: array(LoadBalancing.machine) = [|
        {id: 0, jobs: [2, 1], load: 3},
        {id: 1, jobs: [3], load: 3},
      |];

      expect(LoadBalancing.ptas(jobs, m, 0.0)) |> toEqual(expectedResult);
    });

    test("case 2 optimal (eps=0.0)", () => {
      let jobs = [|2, 3, 2, 2, 3|];
      let m = 2;
      let expectedResult: array(LoadBalancing.machine) = [|
        {id: 0, jobs: [2, 2, 2], load: 6},
        {id: 1, jobs: [3, 3], load: 6},
      |];

      expect(LoadBalancing.ptas(jobs, m, 0.0)) |> toEqual(expectedResult);
    });
  });
});

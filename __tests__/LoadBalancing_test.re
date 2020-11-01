open Jest;
open Expect;

type case = {
  jobs: array(LoadBalancing.job),
  m: int,
};

describe("LoadBalancing", () => {
  let cases = [|
    {jobs: [|1, 2, 3|], m: 2},
    {jobs: [|2, 3, 2, 2, 3|], m: 2},
    {jobs: [|10, 6, 12, 3, 3, 8, 4, 1|], m: 4},
    {jobs: [|1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 5|], m: 5},
  |];

  describe("greedy()", () => {
    test("case 0 suboptimal", () => {
      let {jobs, m} = cases[0];
      let result = LoadBalancing.greedy(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(4);
    });

    test("case 1 suboptimal", () => {
      let {jobs, m} = cases[1];
      let result = LoadBalancing.greedy(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(7);
    });

    test("case 2 suboptimal", () => {
      let {jobs, m} = cases[2];
      let result = LoadBalancing.greedy(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(14);
    });

    test("case 3 suboptimal", () => {
      let {jobs, m} = cases[3];
      let result = LoadBalancing.greedy(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(9);
    });
  });

  describe("ordered()", () => {
    test("case 0 optimal", () => {
      let {jobs, m} = cases[0];
      let result = LoadBalancing.ordered(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(3);
    });

    test("case 1 suboptimal", () => {
      let {jobs, m} = cases[1];
      let result = LoadBalancing.ordered(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(7);
    });

    test("case 2 suboptimal", () => {
      let {jobs, m} = cases[2];
      let result = LoadBalancing.ordered(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(13);
    });

    test("case 3 optimal", () => {
      let {jobs, m} = cases[3];
      let result = LoadBalancing.ordered(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(7);
    });
  });

  describe("bruteForce()", () => {
    test("case 0 optimal", () => {
      let {jobs, m} = cases[0];
      let result = LoadBalancing.bruteForce(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(3);
    });

    test("case 1 optimal", () => {
      let {jobs, m} = cases[1];
      let result = LoadBalancing.bruteForce(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(6);
    });

    test("case 2 optimal", () => {
      let {jobs, m} = cases[2];
      let result = LoadBalancing.bruteForce(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(12);
    });

    test("case 3 optimal", () => {
      let {jobs, m} = cases[3];
      let result = LoadBalancing.bruteForce(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(7);
    });
  });

  describe("ptas()", () => {
    test("case 0 optimal (eps=1.0)", () => {
      let {jobs, m} = cases[0];
      let result = LoadBalancing.ptas(jobs, m, 1.0);
      expect(LoadBalancing.getMakespan(result)) |> toBe(3);
    });

    test("case 0 optimal (eps=0.5)", () => {
      let {jobs, m} = cases[0];
      let result = LoadBalancing.ptas(jobs, m, 0.5);
      expect(LoadBalancing.getMakespan(result)) |> toBe(3);
    });

    test("case 1 suboptimal (eps=1.0)", () => {
      let {jobs, m} = cases[1];
      let result = LoadBalancing.ptas(jobs, m, 1.0);
      expect(LoadBalancing.getMakespan(result)) |> toBe(7);
    });

    test("case 1 suboptimal (eps=0.5)", () => {
      let {jobs, m} = cases[1];
      let result = LoadBalancing.ptas(jobs, m, 0.5);
      expect(LoadBalancing.getMakespan(result)) |> toBe(7);
    });

    test("case 2 suboptimal (eps=0.5)", () => {
      let {jobs, m} = cases[2];
      let result = LoadBalancing.ptas(jobs, m, 0.5);
      expect(LoadBalancing.getMakespan(result)) |> toBe(13);
    });

    test("case 3 optimal (eps=0.5)", () => {
      let {jobs, m} = cases[3];
      let result = LoadBalancing.ptas(jobs, m, 0.5);
      expect(LoadBalancing.getMakespan(result)) |> toBe(7);
    });

    test("case 3 optimal (eps=0.0)", () => {
      let {jobs, m} = cases[3];
      let result = LoadBalancing.ptas(jobs, m, 0.0);
      expect(LoadBalancing.getMakespan(result)) |> toBe(7);
    });
  });
});

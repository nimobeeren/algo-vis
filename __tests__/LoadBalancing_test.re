open Jest;
open Expect;

describe("LoadBalancing", () => {
  describe("greedy()", () => {
    test("case 1 suboptimal", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;

      let result = LoadBalancing.greedy(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(4);
    });

    test("case 2 suboptimal", () => {
      let jobs = [|2, 3, 2, 2, 3|];
      let m = 2;

      let result = LoadBalancing.greedy(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(7);
    });
  });

  describe("ordered()", () => {
    test("case 1 optimal", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;

      let result = LoadBalancing.ordered(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(3);
    });

    test("case 2 suboptimal", () => {
      let jobs = [|2, 3, 2, 2, 3|];
      let m = 2;

      let result = LoadBalancing.ordered(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(7);
    });
  })

  describe("bruteForce()", () => {
    test("case 1 optimal", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;

      let result = LoadBalancing.bruteForce(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(3);
    });

    test("case 2 optimal", () => {
      let jobs = [|2, 3, 2, 2, 3|];
      let m = 2;

      let result = LoadBalancing.bruteForce(jobs, m);
      expect(LoadBalancing.getMakespan(result)) |> toBe(6);
    });
  });

  describe("ptas()", () => {
    test("case 1 optimal (eps=0.0)", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;

      let result = LoadBalancing.ptas(jobs, m, 0.0);
      expect(LoadBalancing.getMakespan(result)) |> toBe(3);
    });

    test("case 2 optimal (eps=0.0)", () => {
      let jobs = [|2, 3, 2, 2, 3|];
      let m = 2;

      let result = LoadBalancing.ptas(jobs, m, 0.0);
      expect(LoadBalancing.getMakespan(result)) |> toBe(6);
    });

    test("case 1 optimal (eps=0.5)", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;

      let result = LoadBalancing.ptas(jobs, m, 0.5);
      expect(LoadBalancing.getMakespan(result)) |> toBe(3);
    });

    test("case 2 suboptimal (eps=0.5)", () => {
      let jobs = [|2, 3, 2, 2, 3|];
      let m = 2;

      let result = LoadBalancing.ptas(jobs, m, 0.5);
      expect(LoadBalancing.getMakespan(result)) |> toBe(7);
    });

    test("case 1 optimal (eps=1.0)", () => {
      let jobs = [|1, 2, 3|];
      let m = 2;

      let result = LoadBalancing.ptas(jobs, m, 1.0);
      expect(LoadBalancing.getMakespan(result)) |> toBe(3);
    });

    test("case 2 suboptimal (eps=1.0)", () => {
      let jobs = [|2, 3, 2, 2, 3|];
      let m = 2;

      let result = LoadBalancing.ptas(jobs, m, 1.0);
      expect(LoadBalancing.getMakespan(result)) |> toBe(7);
    });
  });
});

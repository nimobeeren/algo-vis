type job = int;
type machine = {
  id: int,
  jobs: list(job),
  load: int,
};

type algo =
  | Greedy
  | Ordered
  | PTAS
  | BruteForce;

// Gets a uniquely identifying string for each algo.
let algoToString = algo => {
  switch (algo) {
  | Greedy => "greedy"
  | Ordered => "ordered"
  | PTAS => "ptas"
  | BruteForce => "bruteForce"
  };
};

// Gets the worst-case running time for each algo, derived from the code.
// Value is returned as HTML to allow for sub/superscript.
let algoToRunningTime = algo => {
  switch (algo) {
  | Greedy => "O(n<sup>2</sup>)"
  | Ordered => "O(n<sup>2</sup>)"
  | PTAS => {js|O(((1-ε)n)! + (εn)<sup>2</sup>)|js}
  | BruteForce => "O(n!)"
  };
};

// Gets the approximation ratio for each algo.
let algoToApproxRatio = algo => {
  switch (algo) {
  | Greedy => "2 - 1/m"
  | Ordered => "3/2"
  | PTAS => {js|1 + ε|js}
  | BruteForce => "1"
  };
};

// Gets an algo from its uniquely identifying string.
let stringToAlgo = str => {
  switch (str) {
  | "greedy" => Some(Greedy)
  | "ordered" => Some(Ordered)
  | "ptas" => Some(PTAS)
  | "bruteForce" => Some(BruteForce)
  | _ => None
  };
};

let createMachine: int => machine = id => {id, jobs: [], load: 0};

// Produces a machine that is identical to the given machine, but with the given job added
let assign: (job, machine) => machine =
  (job, machine) => {
    {...machine, jobs: [job, ...machine.jobs], load: machine.load + job};
  };

// Produces a machine that is identical to the given machine, but with one job of the given
// size removed. If no such job is found, the jobs are unchanged.
let unassign: (job, machine) => machine =
  (job, machine) => {
    let isFound = ref(false);
    let newJobs =
      List.filter(
        j =>
          if (! isFound^ && j == job) {
            isFound := true;
            false;
          } else {
            true;
          },
        machine.jobs,
      );

    {...machine, jobs: newJobs, load: machine.load - job};
  };

// Produces a machine that is identical to the given machine, but with its
// first (most recently added) job removed.
let pop: machine => machine =
  machine => {
    switch (machine.jobs) {
    | [] => machine
    | [head, ...tail] => {...machine, jobs: tail, load: machine.load - head}
    };
  };

// The makespan is the maximum load across all machines
// Running time: O(n)
let getMakespan: array(machine) => int =
  Array.fold_left(
    (maximum, machine) => max(maximum, machine.load),
    min_int,
  );

// Function that is used internally by e.g. greedy(), which takes an array of
// machines instead of creating them when called
let greedyInternal: (array(job), array(machine)) => array(machine) =
  (jobs, machines) => {
    // Assign each job to the machine with smallest load
    Array.iter(
      job => {
        // Find the index of the machine with smallest load
        // TODO: machine with smallest load could be maintained using a min-heap,
        // which would be faster than finding the minimum in the array every time
        let index = ref(-1);
        let minimum = ref(max_int);
        Array.iteri(
          (i, machine) =>
            if (machine.load < minimum^) {
              index := i;
              minimum := machine.load;
            },
          machines,
        );

        // Assign job to machine with smallest load
        machines[index^] = assign(job, machines[index^]);
      },
      jobs,
    );

    machines;
  };

// Greedy algorithm that assigns each job to the machine with the smallest load
// at that time.
// Running time: O(n^2)
let greedy: (array(job), int) => array(machine) =
  (jobs, m) => {
    let machines = Array.init(m, createMachine);
    greedyInternal(jobs, machines);
  };

// Same as greedy(), but sorts the jobs in decreasing order first.
// Running time: O(n^2)
let ordered: (array(job), int) => array(machine) =
  (jobs, m) => {
    // Sort the jobs in decreasing order before running the regular greedy algo
    let jobsCopy = Array.copy(jobs); // don't modify the input array
    Array.fast_sort((job1, job2) => job2 - job1, jobsCopy);
    greedy(jobsCopy, m);
  };

// Brute force algorithm that tries all possible assignments of jobs to machines
// and returns a solution with minimum makespan.
// Running time: O(n!)
// TODO: prune equivalent states
let bruteForce: (array(job), int) => array(machine) =
  (jobs, m) => {
    let machines = Array.init(m, createMachine);
    let jobsList = Array.to_list(jobs);

    let recursiveCalls = ref(0);
    let arrayCopies = ref(0);

    // bestMakespan is the minimum makespan of a complete solution found so far
    let rec bruteForceRec = (jobsList, machines, bestMakespan) => {
      recursiveCalls := recursiveCalls^ + 1;
      // If the makespan of current machines is already larger than the best
      // makespan so far, don't go deeper into this branch
      if (getMakespan(machines) > bestMakespan) {
        (machines, max_int);
      } else {
        switch (jobsList) {
        // No more jobs to assign
        | [] => (machines, getMakespan(machines))
        // Continue assigning jobs
        | [nextJob, ...restJobs] =>
          // These variables maintain the best solution found in this branch,
          // but only if it is better than the global best
          let bestMachinesLocal = ref([||]);
          let bestMakespanLocal = ref(max_int);

          // Try assigning the next job to each machine and recurse
          // This is essentially just a for loop with mutation, not really "pure"
          Array.iteri(
            (i, _) => {
              machines[i] = assign(nextJob, machines[i]);

              let (newMachines, newMakespan) =
                bruteForceRec(
                  restJobs,
                  machines,
                  min(bestMakespan, bestMakespanLocal^),
                );

              if (newMakespan < min(bestMakespan, bestMakespanLocal^)) {
                // This solution is the best so far
                arrayCopies := arrayCopies^ + 1;
                bestMachinesLocal := Array.copy(newMachines);
                bestMakespanLocal := newMakespan;
              };

              machines[i] = pop(machines[i]);
            },
            machines,
          );

          (bestMachinesLocal^, bestMakespanLocal^);
        };
      };
    };

    let (bestMachines, _) = bruteForceRec(jobsList, machines, max_int);
    Js.log(recursiveCalls^);
    Js.log(arrayCopies^);
    bestMachines;
  };

// Hybrid algorithm that runs the brute force algorithm on part of the input
// jobs, and does the rest with sorted greedy scheduling.
// Running time: O(((1-ε)n)! + (εn)^2)
let ptas: (array(job), int, float) => array(machine) =
  (jobs, m, eps) => {
    // Sort jobs in decreasing order
    let jobsCopy = Array.copy(jobs); // don't modify the input array
    Array.fast_sort((job1, job2) => job2 - job1, jobsCopy);

    // Partition the array of jobs into a brute force part and a greedy part,
    // where the proportion (brute force) : greedy = (1 - eps) : eps
    let n = Array.length(jobsCopy);
    let greedyJobsLength = (float_of_int(n) *. eps)->floor->int_of_float;
    let bfJobs = Array.sub(jobsCopy, 0, n - greedyJobsLength);
    let greedyJobs =
      Array.sub(jobsCopy, n - greedyJobsLength, greedyJobsLength);

    let bfMachines = bruteForce(bfJobs, m);
    greedyInternal(greedyJobs, bfMachines);
  };

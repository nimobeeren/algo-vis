type job = int;
type machine = {
  id: int,
  jobs: list(job),
  load: int,
};

type algo =
  | Greedy
  | Ordered
  | BruteForce;

// Gets a uniquely identifying string for each algo.
let algoToString = algo => {
  switch (algo) {
  | Greedy => "greedy"
  | Ordered => "ordered"
  | BruteForce => "bruteForce"
  };
};

// Gets the worst-case running time for each algo, derived from the code.
// Value is returned as HTML to allow for sub/superscript.
let algoToRunningTime = algo => {
  switch (algo) {
  | Greedy => "O(n<sup>2</sup>)"
  | Ordered => "O(n<sup>2</sup>)"
  | BruteForce => "O(n!)"
  };
};

// Gets the approximation ratio for each algo.
let algoToApproxRatio = algo => {
  switch (algo) {
  | Greedy => "2 - 1/m"
  | Ordered => "3/2"
  | BruteForce => "1"
  };
};

// Gets an algo from its uniquely identifying string.
let stringToAlgo = str => {
  switch (str) {
  | "greedy" => Some(Greedy)
  | "ordered" => Some(Ordered)
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

// The makespan is the maximum load across all machines
let getMakespan: array(machine) => int =
  machines => {
    Array.fast_sort((a, b) => b.load - a.load, machines);
    machines[0].load;
  };

// Greedy algorithm that assigns each job to the machine with the smallest load
// at that time.
// Running time: O(n^2 log n)
let greedy: (array(job), int) => array(machine) =
  (jobs, m) => {
    let machines: array(machine) = Array.init(m, createMachine);

    // Assign each job to the machine with smallest load
    Array.iter(
      job => {
        // TODO: machine with smallest load could be maintained using a min-heap,
        // which would be faster than sorting the array every time
        Array.fast_sort((a, b) => a.load - b.load, machines);
        machines[0] = assign(job, machines[0]);
      },
      jobs,
    );
    machines;
  };

// Same as greedy(), but sorts the jobs in descending order first.
// Running time: O(n^2 log n)
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
let bruteForce: (array(job), int) => array(machine) =
  (jobs, m) => {
    let machines = Array.init(m, createMachine);

    let rec bruteForceRec = (jobsRec, machines) =>
      if (Array.length(jobsRec) == 0) {
        machines;
      } else {
        let results =
          Array.init(
            m,
            i => {
              machines[i] = assign(jobsRec[0], machines[i]);
              let result =
                Array.copy(
                  bruteForceRec(
                    Array.sub(jobsRec, 1, Array.length(jobsRec) - 1),
                    machines,
                  ),
                );
              machines[i] = unassign(jobsRec[0], machines[i]);
              result;
            },
          );

        let bestMachines = ref([||]);
        let bestMakespan = ref(max_int);

        for (i in 0 to m - 1) {
          let makespan = getMakespan(results[i]);
          if (makespan < bestMakespan^) {
            bestMachines := results[i];
            bestMakespan := makespan;
          };
        };

        bestMachines^;
      };

    bruteForceRec(jobs, machines);
  };

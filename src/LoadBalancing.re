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
// TODO: we can probably just set jobs to Array.tl(machines.jobs) since we only ever unassign
// the first job in the list
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

// Function that is used internally by e.g. greedy(), which takes an array of
// machines instead of creating them when called
let greedyInternal: (array(job), array(machine)) => array(machine) =
  (jobs, machines) => {
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

// Greedy algorithm that assigns each job to the machine with the smallest load
// at that time.
// Running time: O(n^2 log n)
let greedy: (array(job), int) => array(machine) =
  (jobs, m) => {
    let machines = Array.init(m, createMachine);
    greedyInternal(jobs, machines);
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
// TODO: prune when makespan is larger than best
// TODO: prune equivalent states
let bruteForce: (array(job), int) => array(machine) =
  (jobs, m) => {
    let machines = Array.init(m, createMachine);
    let jobsList = Array.to_list(jobs);

    let rec bruteForceRec = (jobsList, machines) =>
      switch (jobsList) {
      | [] => machines
      | [head, ...tail] =>
        let bestMachines = ref([||]);
        let bestMakespan = ref(max_int);

        let machinesCopy = Array.copy(machines);
        // This is essentially just a for loop, not really functional style
        Array.iteri(
          (i, _) => {
            machinesCopy[i] = assign(head, machinesCopy[i]);

            let result = bruteForceRec(tail, machinesCopy);
            let makespan = getMakespan(result);
            if (makespan < bestMakespan^) {
              bestMachines := Array.copy(result);
              bestMakespan := makespan;
            };

            machinesCopy[i] = unassign(head, machinesCopy[i]);
          },
          machinesCopy,
        );

        bestMachines^;
      };

    bruteForceRec(jobsList, machines);
  };

// Hybrid algorithm that runs the brute force algorithm on part of the input
// jobs, and does the rest with ordered scheduling
let ptas: (array(job), int, float) => array(machine) = (jobs, m, eps) => {
  let jobsCopy = Array.copy(jobs); // don't modify the input array
  Array.fast_sort((job1, job2) => job2 - job1, jobsCopy);

  // Partition the array of jobs into a brute force part and a greedy part,
  // where the proportion is determined by a parameter epsilon
  let n = Array.length(jobs);
  let bfJobsLength = (float_of_int(n) *. eps)->ceil->int_of_float;
  let bfJobs = Array.sub(jobs, 0, bfJobsLength);
  let greedyJobs = Array.sub(jobs, bfJobsLength, n - bfJobsLength);

  let bfMachines = bruteForce(bfJobs, m);
  greedyInternal(greedyJobs, bfMachines);
};

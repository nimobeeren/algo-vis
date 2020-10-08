type job = int;
type machine = {
  id: int,
  jobs: list(job),
  load: int,
};

type loadBalancer = (array(job), int) => array(machine);

type algo =
  | Greedy
  | Ordered
  | BruteForce;

let algoToString = algo => {
  switch (algo) {
  | Greedy => "greedy"
  | Ordered => "ordered"
  | BruteForce => "bruteforce"
  };
};

let stringToAlgo = str => {
  switch (str) {
  | "greedy" => Some(Greedy)
  | "ordered" => Some(Ordered)
  | "bruteforce" => Some(BruteForce)
  | _ => None
  };
};

let createMachine: int => machine = id => {id, jobs: [], load: 0};

// Produces a machine that is identical to the given machine, but with the given job added
let assign: (job, machine) => machine =
  (job, machine) => {
    {...machine, jobs: [job, ...machine.jobs], load: machine.load + job};
  };

// TODO
let unassign = () => ();

// The makespan is the maximum load across all machines
let getMakespan: array(machine) => int =
  machines => {
    Array.fast_sort((a, b) => b.load - a.load, machines);
    machines[0].load;
  };

// Greedy algorithm that assigns each job to the machine with the smallest load
// at that time.
// Running time: O(n^2 log n)
let greedy: loadBalancer =
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

let ordered: loadBalancer =
  (jobs, m) => {
    // Sort the jobs in decreasing order before running the regular greedy algo
    let jobsCopy = Array.copy(jobs); // don't modify the input array
    Array.fast_sort((job1, job2) => job2 - job1, jobsCopy);
    greedy(jobsCopy, m);
  };

let rec bruteForce = (jobs, machines) => {
  // if |jobs| = 0
  //   return machines

  // IMPERATIVE
  // for (i = 0 to m - 1)
  //   machines[i] = assign(jobs[0], machines[i])
  //   let result[i] = bruteForce(jobs \ jobs[0], machines)
  //   machines[i] = unassign(jobs[0], machines[i])
  // end for
  // return argmin(getMakespan(result[0]), ..., getMakespan(result[m-1]))

  // FUNCTIONAL
  
  // TODO: something's gotta be wrong here
  let rec repeat = (i, machines, minMakespan) => {
    if (i == 0) {
      machines
    } else {
      machines[i-1] = assign(jobs[0], machines[i-1])
      let result = bruteForce(jobs \ jobs[0], machines)
      let resultMakespan = getMakespan(result);
      machines[i-1] = unassign(jobs[0], machines[i-1])

      repeat(i - 1, machines, min(minMakespan, resultMakespan))
    }
  }
}
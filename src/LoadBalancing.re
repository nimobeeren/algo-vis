type job = int;
type machine = {
  id: int,
  jobs: list(job),
  load: int,
};

let create_machine: int => machine = id => {id, jobs: [], load: 0};

// Produces a machine that is identical to the given machine, but with the given job added
let assign: (job, machine) => machine =
  (job, machine) => {
    {...machine, jobs: [job, ...machine.jobs], load: machine.load + job};
  };

// Greedy algorithm that assigns each job to the machine with the smallest load
// at that time
// Running time: O(n^2 log n)
let greedy: (array(job), int) => array(machine) =
  (jobs, m) => {
    let machines: array(machine) = Array.init(m, create_machine);

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

// The makespan is the maximum load across all machines
let get_makespan: array(machine) => int =
  machines => {
    Array.fast_sort((a, b) => b.load - a.load, machines);
    machines[0].load;
  };

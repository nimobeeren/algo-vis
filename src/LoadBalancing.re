type job = int;
type machine = {
  jobs: list(job),
  load: int,
};

let create_machine: unit => machine = () => {jobs: [], load: 0};

// Creates a new machine with an added job
let assign: (job, machine) => machine =
  (job, machine) => {
    {jobs: [job, ...machine.jobs], load: machine.load + job};
  };

// Greedy algorithm that assigns each job to the machine with the smallest load
// at that time
let greedy: (array(job), int) => array(machine) =
  (jobs, m) => {
    let machines: array(machine) = Array.init(m, _ => create_machine());

    // Assign each job to the machine with smallest load
    Array.iter(
      job => {
        // TODO: machine with smallest load could be maintained using a min-heap
        Array.sort((a, b) => a.load - b.load, machines);
        machines[0] = assign(job, machines[0]);
      },
      jobs,
    );
    machines;
  };

// The makespan is the maximum load across all machines
let get_makespan: array(machine) => int =
  machines => {
    Array.sort((a, b) => b.load - a.load, machines);
    machines[0].load;
  };

open Components;

module Home = {
  [@bs.scope "performance"] [@bs.val] external now: unit => float = "now";

  [@react.component]
  let make = () => {
    let (algo, setAlgo) = React.useState(() => LoadBalancing.Greedy);
    let (numMachines, setNumMachines) = React.useState(() => 4);
    let (jobs, setJobs) = React.useState(() => [|1, 1, 2, 2, 3, 4|]);
    let (numJobs, setNumJobs) = React.useState(() => Array.length(jobs));
    let (result, setResult) = React.useState(() => None);
    let (makespan, setMakespan) = React.useState(() => None); // TODO: move out of state
    let (runningTime, setRunningTime) = React.useState(() => None);

    React.useEffect2(
      () => {
        let numJobsInState = Array.length(jobs);
        if (numJobsInState > numJobs) {
          // We have too many jobs, so we drop some jobs off the end
          setJobs(oldJobs =>
            Array.sub(oldJobs, 0, numJobs)
          );
        } else if (numJobsInState < numJobs) {
          // We don't have enough jobs, so we add more
          setJobs(oldJobs => {
            let defaultJobValue = 1;
            let jobsToAdd =
              Array.make(numJobs - numJobsInState, defaultJobValue);
            Array.append(oldJobs, jobsToAdd);
          });
        };
        None;
      },
      (numJobs, jobs),
    );

    React.useEffect3(
      () => {
        let startTime = now();

        let newResult =
          switch (algo) {
          | Greedy => Some(LoadBalancing.greedy(jobs, numMachines))
          | Ordered => Some(LoadBalancing.ordered(jobs, numMachines))
          | BruteForce => Some(LoadBalancing.bruteForce(jobs, numMachines))
          };
        setResult(_ => newResult);

        let newMakespan =
          switch (newResult) {
          | Some(res) => Some(LoadBalancing.getMakespan(res))
          | None => None
          };
        setMakespan(_ => newMakespan);

        let endTime = now();
        setRunningTime(_ => Some(endTime -. startTime));

        None;
      },
      (algo, jobs, numMachines),
    );

    <main>
      <aside>
        <form id="input-form" action="#" className="aside__scroll">
          <div className="aside__content" role="presentation">
            <div
              className="group" role="region" ariaLabelledby="algorithm-label">
              <label id="algorithm-label" htmlFor="algorithm">
                {React.string("Algorithm")}
              </label>
              <Select
                id="algorithm"
                value={LoadBalancing.algoToString(algo)}
                onChange={event => {
                  let newAlgo =
                    LoadBalancing.stringToAlgo(
                      ReactEvent.Form.target(event)##value,
                    );
                  switch (newAlgo) {
                  | Some(algo) => setAlgo(_ => algo)
                  | None => () // got invalid value, so don't set state
                  };
                }}>
                <option value="greedy"> {React.string("Greedy")} </option>
                <option value="ordered">
                  {React.string("Sorted Greedy")}
                </option>
                <option value="bruteForce">
                  {React.string("Brute Force")}
                </option>
              </Select>
              <div className="group__bottom-text">
                <p role="note">
                  {React.string("Worst-case running time: ")}
                  <span ariaLabel="Oh of n squared">
                    {React.string("O(n")}
                    <sup> {React.string("2")} </sup>
                    {React.string(")")}
                  </span>
                </p>
                <p role="note">
                  {React.string("Approximation ratio: 2 - 1/m")}
                </p>
              </div>
            </div>
            <div
              className="group"
              role="region"
              ariaLabelledby="num-machines-label">
              <label id="num-machines-label" htmlFor="num-machines">
                {React.string("Number of machines")}
                <span className="lowercase"> {React.string(" (m)")} </span>
              </label>
              <NumberInput
                id="num-machines"
                value=numMachines
                min=1
                max=4
                onChange={newValue => {setNumMachines(_ => newValue)}}
              />
            </div>
            <div
              className="group" role="region" ariaLabelledby="num-jobs-label">
              <label id="num-jobs-label" htmlFor="num-jobs">
                {React.string("Number of jobs")}
                <span className="lowercase"> {React.string(" (n)")} </span>
              </label>
              <NumberInput
                id="num-jobs"
                value=numJobs
                min=1
                max=15
                onChange={newValue => {setNumJobs(_ => newValue)}}
              />
            </div>
            <div
              className="group"
              role="region"
              ariaLabelledby="job-inputs-label">
              <label id="job-inputs-label" htmlFor="job-input">
                {React.string("Job sizes")}
              </label>
              <div className="job-inputs">
                <MultiNumberInput
                  value=jobs
                  id="job-input"
                  ariaLabelledby="job-inputs-label"
                  min=1
                  max=999
                  onChange={newValue => setJobs(_ => newValue)}
                />
              </div>
            </div>
          </div>
        </form>
      </aside>
      <section className="tube tube--large">
        <BarPlot machines=result />
      </section>
      <aside>
        <div className="aside__scroll" role="presentation">
          <div className="aside__content" role="presentation">
            <div className="group" role="region" ariaLabelledby="result-label">
              <label id="result-label" htmlFor="result">
                {React.string("Makespan")}
              </label>
              <output
                id="result" htmlFor="input-form" className="result-number">
                {switch (makespan) {
                 | Some(makespan) => React.int(makespan)
                 | None => React.null
                 }}
              </output>
              <p role="note">
                {switch (runningTime) {
                 | None => React.null
                 | Some(runningTime) =>
                   React.string(
                     "Actual running time: "
                     ++ Utils.durationToString(runningTime),
                   )
                 }}
              </p>
            </div>
          </div>
        </div>
      </aside>
    </main>;
  };
};

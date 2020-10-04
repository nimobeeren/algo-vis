open Components;

module Home = {
  [@react.component]
  let make = () => {
    let (algo, setAlgo) = React.useState(() => "greedy");
    let (numMachines, setNumMachines) = React.useState(() => 4);
    let (jobs, setJobs) = React.useState(() => [|4, 3, 3, 3, 2, 1|]);
    let (numJobs, setNumJobs) = React.useState(() => Array.length(jobs));

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

    let result = LoadBalancing.greedy(jobs, numMachines);
    let makespan = LoadBalancing.getMakespan(result);

    <article>
      <aside>
        <form id="input-form" action="#" className="aside">
          <div
            className="group" role="region" ariaLabelledby="algorithm-label">
            <label id="algorithm-label" htmlFor="algorithm">
              {React.string("Algorithm")}
            </label>
            <Select
              id="algorithm"
              value=algo
              onChange={event =>
                setAlgo(_ => ReactEvent.Form.target(event)##value)
              }>
              <option value="greedy"> {React.string("Greedy")} </option>
              <option value="sorted">
                {React.string("Sorted Greedy")}
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
          <div className="group" role="region" ariaLabelledby="num-jobs-label">
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
            className="group" role="region" ariaLabelledby="job-inputs-label">
            <label id="job-inputs-label" htmlFor="job-input">
              {React.string("Job sizes")}
            </label>
            <fieldset className="job-inputs">
              <MultiNumberInput
                value=jobs
                id="job-input"
                ariaLabelledby="job-inputs-label"
                min=1
                max=999
                onChange={newValue => setJobs(_ => newValue)}
              />
            </fieldset>
          </div>
        </form>
      </aside>
      <main className="tube tube--large">
        <div className="tube__cover tube__cover--large" role="presentation" />
        <BarPlot machines=result />
      </main>
      <aside className="aside">
        <div className="group" role="region" ariaLabelledby="result-label">
          <label id="result-label" htmlFor="result">
            {React.string("Result")}
          </label>
          <output id="result" htmlFor="input-form" className="result-number">
            {React.int(makespan)}
          </output>
          <p role="note"> {React.string("Actual running time: 69 ms")} </p>
        </div>
      </aside>
    </article>;
  };
};

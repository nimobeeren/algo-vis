open Components;

module Home = {
  [@react.component]
  let make = () => {
    let jobs = [|4, 3, 3, 3, 2, 1|];

    let (numMachines, setNumMachines) = React.useState(() => 4);
    let (numJobs, setNumJobs) = React.useState(() => 6);

    let result = LoadBalancing.greedy(jobs, numMachines);
    let makespan = LoadBalancing.getMakespan(result);

    <article>
      <aside>
        <div className="group">
          <label htmlFor="algorithm"> {React.string("Algorithm")} </label>
          <select id="algorithm">
            <option> {React.string("Greedy")} </option>
          </select>
          <div className="group__bottom-text">
            <p> {React.string("Worst-case running time: O(n")} <sup>{React.string("2")}</sup> {React.string(")")} </p>
            <p> {React.string("Approximation ratio: 2 - 1/m")} </p>
          </div>
        </div>
        <div className="group">
          <label htmlFor="num-machines">
            {React.string("Number of machines (m)")}
          </label>
          <input
            id="num-machines"
            type_="number"
            value={string_of_int(numMachines)}
            min="1"
            max="4"
            onChange={event => {
              setNumMachines(ReactEvent.Form.target(event)##value)
            }}
          />
        </div>
        <div className="group">
          <label htmlFor="num-jobs">
            {React.string("Number of jobs (n)")}
          </label>
          <input
            id="num-jobs"
            type_="number"
            value={string_of_int(numJobs)}
            min="1"
            max="15"
            onChange={event => {
              setNumJobs(ReactEvent.Form.target(event)##value)
            }}
          />
        </div>
        <div className="group">
          <label> {React.string("Job sizes")} </label>
          <div className="job-inputs">
            {React.array(
               Array.init(numJobs, i =>
                 <input
                   type_="number"
                   key={"job-" ++ string_of_int(i)}
                   defaultValue="1"
                   min="1"
                   max="999"
                 />
               ),
             )}
          </div>
        </div>
      </aside>
      <main className="bucket bucket--large">
        <div className="bucket__cover bucket__cover--large" />
        <BarPlot machines=result />
      </main>
      <aside>
        <div className="group">
          <label> {React.string("Result")} </label>
          <p className="result-number"> {React.int(makespan)} </p>
          <p> {React.string("Actual running time: 69 ms")} </p>
        </div>
      </aside>
    </article>;
  };
};

open Components;

module Home = {
  [@react.component]
  let make = () => {
    let jobs = [|4, 3, 3, 3, 2, 1|];

    let (numMachines, setNumMachines) = React.useState(() => 4);
    let (numJobs, setNumJobs) = React.useState(() => 6);

    let result = LoadBalancing.greedy(jobs, numMachines);
    let makespan = LoadBalancing.getMakespan(result);

    <Layout>
      <div
        style={ReactDOM.Style.make(
          ~width="272px",
          ~padding=Theme.space[3],
          (),
        )}>
        <div
          style={ReactDOM.Style.make(
            ~display="flex",
            ~flexFlow="column nowrap",
            (),
          )}>
          <label htmlFor="algorithm"> {React.string("Algorithm")} </label>
          <select id="algorithm">
            <option> {React.string("Greedy")} </option>
          </select>
          <p> {React.string("Worst-case running time: O(n^2)")} </p>
          <p> {React.string("Approximation ratio: 2 - 1/m")} </p>
        </div>
        <div>
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
            style={ReactDOM.Style.make(~display="block", ())}
          />
        </div>
        <div>
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
            style={ReactDOM.Style.make(~display="block", ())}
          />
        </div>
        <div>
          <label> {React.string("Job sizes")} </label>
          <div
            style={ReactDOM.Style.make(
              ~display="flex",
              ~flexFlow="row wrap",
              ~gridGap=Theme.space[1],
              (),
            )}>
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
      </div>
      <div
        style={ReactDOM.Style.make(
          ~flexGrow="1",
          ~display="flex",
          ~flexFlow="row nowrap",
          ~justifyContent="center",
          ~maxWidth="752px",
          ~padding=Theme.space[4],
          ~border=Theme.borders##regular,
          ~borderRadius=Theme.space[2],
          (),
        )}>
        <div
          style={ReactDOM.Style.make(~flexGrow="1", ~maxWidth="560px", ())}>
          <BarPlot machines=result />
        </div>
      </div>
      <div
        style={ReactDOM.Style.make(
          ~width="272px",
          ~padding=Theme.space[3],
          (),
        )}>
        <label> {React.string("Result")} </label>
        <p
          style={ReactDOM.Style.make(
            ~color=Theme.colors##primary,
            ~fontSize=Theme.fontSizes##xl,
            (),
          )}>
          {React.int(makespan)}
        </p>
        <p> {React.string("Actual running time: 69 ms")} </p>
      </div>
    </Layout>;
  };
};

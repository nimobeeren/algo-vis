[@react.component]
let make = () => {
  let jobs = [|4, 3, 3, 3, 2, 1|];

  let (numMachines, setNumMachines) = React.useState(() => 4);

  let result = LoadBalancing.greedy(jobs, numMachines);

  <Layout>
    <div
      style={ReactDOM.Style.make(~width="272px", ~padding=Theme.space[3], ())}>
      <input
        type_="number"
        value={string_of_int(numMachines)}
        min="1"
        max="100"
        onChange={event => {
          setNumMachines(ReactEvent.Form.target(event)##value)
        }}
      />
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
      <div style={ReactDOM.Style.make(~flexGrow="1", ~maxWidth="560px", ())}>
        <BarPlot machines=result />
      </div>
    </div>
    <div
      style={ReactDOM.Style.make(~width="272px", ~padding=Theme.space[3], ())}>
      {React.string("Result")}
    </div>
  </Layout>;
};

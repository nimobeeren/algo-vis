[@react.component]
let make = () => {
  let jobs = [|4, 3, 3, 3, 2, 1|];

  let (numMachines, setNumMachines) = React.useState(() => 4);
  
  let result = LoadBalancing.greedy(jobs, numMachines);

  <Layout>
    <input
      type_="number"
      value={string_of_int(numMachines)}
      min="1"
      max="100"
      onChange={event => {
        setNumMachines(ReactEvent.Form.target(event)##value);
      }}
    />
    <div style={ReactDOM.Style.make(
      ~margin=Theme.space[4],
      ~padding="0 " ++ Theme.space[3], 
      ()
    )}>
      <BarPlot machines=result />
    </div>
  </Layout>;
};

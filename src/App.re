[@react.component]
let make = () => {
  let jobs = [|3, 2, 1|];

  let (numMachines, setNumMachines) = React.useState(() => 2);
  
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
    <BarPlot machines=result />
  </Layout>;
};

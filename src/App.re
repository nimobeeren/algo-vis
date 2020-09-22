[@react.component]
let make = () => {
  let machine1: LoadBalancing.machine = {jobs: [1, 3], load: 4};
  let machine2: LoadBalancing.machine = {jobs: [2], load: 2};
  let test_machines = [|machine1, machine2|];

  <Layout>
    <BarPlot machines=test_machines />
    // <SimpleComponent name={myname} />
  </Layout>
};

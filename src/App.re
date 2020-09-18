[@react.component]
let make = () => {
  let machine1: LoadBalancing.machine = {jobs: [1, 2], load: 3};
  let machine2: LoadBalancing.machine = {jobs: [3], load: 3};
  let test_machines = [|machine1, machine2|];

  <Layout>
    <BarPlot machines=test_machines />
    // <SimpleComponent name={myname} />
  </Layout>
};

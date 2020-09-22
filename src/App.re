[@react.component]
let make = () => {
  let jobs = [|1, 2, 3|];
  let m = 2;
  let result = LoadBalancing.greedy(jobs, m);

  <Layout>
    <BarPlot machines=result />
  </Layout>
};

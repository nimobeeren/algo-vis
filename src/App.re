[@react.component]
let make = () => {
  let jobs = [|3, 2, 1|];
  let m = 2;
  let result = LoadBalancing.greedy(jobs, m);

  <Layout> <BarPlot machines=result /> </Layout>;
};

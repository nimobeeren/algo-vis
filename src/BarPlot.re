let style =
  ReactDOM.Style.make(~display="flex", ~height="500px", ~width="100%", ());

[@react.component]
let make = (~machines) => {
  let makespan = LoadBalancing.get_makespan(machines);

  <div style>
    // TODO
    // {React.array(Array.map(machine => {
    //   let height = machine##load / makespan;
    //   <div> {React.string("Test")} </div>
    // }, machines))}
  </div>;
};

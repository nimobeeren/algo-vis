// Need to open the module to avoid "unbound record field" on machine
open LoadBalancing;

let barPlotStyle =
  ReactDOM.Style.make(
    ~display="flex",
    ~alignItems="flex-end",
    ~height="500px",
    ~width="100%",
    (),
  );
let barStyle =
  ReactDOM.Style.make(~flexGrow="1", ~background="palevioletred", ());

[@react.component]
let make = (~machines: array(LoadBalancing.machine)) => {
  let makespan = LoadBalancing.get_makespan(machines);

  <div style=barPlotStyle>
    {React.array(
       Array.map(
         machine => {
           let height =
             float_of_int(machine.load) /. float_of_int(makespan) *. 100.;
           <div
             style={ReactDOM.Style.combine(
               barStyle,
               ReactDOM.Style.make(
                 ~height=Js.Float.toString(height) ++ "%",
                 (),
               ),
             )}
           />;
         },
         machines,
       ),
     )}
  </div>;
};

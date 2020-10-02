// Need to open the module to avoid "unbound record field" on machine
open LoadBalancing;

[@react.component]
let make = (~machines: array(LoadBalancing.machine)) => {
  let makespan = LoadBalancing.getMakespan(machines);

  <div
    style={ReactDOM.Style.make(
      ~display="flex",
      ~flexFlow="row nowrap",
      ~gridGap=Theme.space[3],
      ~alignItems="flex-end",
      ~height="480px",
      ~width="100%",
      (),
    )}>
    {React.array(
       Array.map(
         machine => {
           let height =
             float_of_int(machine.load) /. float_of_int(makespan) *. 100.;
           <div
             key={string_of_int(machine.id)}
             style={ReactDOM.Style.make(
               ~display="flex",
               ~flexFlow="column nowrap",
               ~flexGrow="1",
               ~height=Js.Float.toString(height) ++ "%",
               (),
             )}>
             {React.array(
                Array.init(List.length(machine.jobs), i => {
                  <Job size={List.nth(machine.jobs, i)} />
                }),
              )}
           </div>;
         },
         machines,
       ),
     )}
  </div>;
};

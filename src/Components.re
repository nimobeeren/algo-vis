module Job = {
  [@react.component]
  let make = (~size) => {
    <div
      className="job"
      style={ReactDOM.Style.make(
        ~flexBasis="0", // to ensure flexGrow determines relative size
        ~flexGrow=string_of_int(size),
        (),
      )}>
      {React.int(size)}
    </div>;
  };
};

module BarPlot = {
  // Need to open the module to avoid "unbound record field" on machine
  open LoadBalancing;

  [@react.component]
  let make = (~machines: array(machine)) => {
    let makespan = getMakespan(machines);

    <div className="barplot">
      {React.array(
         Array.map(
           machine => {
             let height =
               float_of_int(machine.load) /. float_of_int(makespan) *. 100.;
             <div
               className="machine"
               key={string_of_int(machine.id)}
               style={ReactDOM.Style.make(
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
};

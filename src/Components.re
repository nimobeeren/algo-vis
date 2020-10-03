module Job = {
  [@react.component]
  let make = (~size) => {
    <div
      className="job bucket"
      style={ReactDOM.Style.make(
        ~flexBasis="0", // to ensure flexGrow determines relative size
        ~flexGrow=string_of_int(size),
        (),
      )}>
      <div className="bucket__cover" />
      <div>{React.int(size)}</div>
    </div>;
  };
};

module BarPlot = {
  [@react.component]
  let make = (~machines: array(LoadBalancing.machine)) => {
    let makespan = LoadBalancing.getMakespan(machines);

    <div className="barplot">
      {React.array(
         Array.map(
           (machine: LoadBalancing.machine) => {
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

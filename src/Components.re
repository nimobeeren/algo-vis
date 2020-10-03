// Need to open the module to avoid "unbound record field" on machine
open LoadBalancing;

module Job = {
  [@react.component]
  let make = (~size) => {
    <div
      style={ReactDOM.Style.make(
        ~flexBasis="0", // to ensure flexGrow determines relative size
        ~flexGrow=string_of_int(size),
        ~display="flex",
        ~justifyContent="center",
        ~alignItems="center",
        ~border=Theme.borders##regular,
        ~borderRadius=Theme.space[1],
        ~fontSize=Theme.fontSizes##lg,
        ~lineHeight=Theme.fontSizes##lg,
        ~fontWeight="300",
        (),
      )}>
      {React.int(size)}
    </div>;
  };
};

module BarPlot = {
  [@react.component]
  let make = (~machines: array(machine)) => {
    let makespan = getMakespan(machines);

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
                 ~flexGrow="1",
                 ~display="flex",
                 ~flexFlow="column nowrap",
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

module Layout = {
  [@react.component]
  let make = (~children) => {
    <div
      style={ReactDOM.Style.make(
        ~display="flex",
        ~flexFlow="row nowrap",
        ~justifyContent="center",
        ~height="648px",
        ~margin="128px 72px",
        ~fontFamily=Theme.fonts##body,
        (),
      )}>
      children
    </div>;
  };
};

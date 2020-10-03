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
      <div> {React.int(size)} </div>
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
                    <Job
                      key={string_of_int(i)}
                      size={List.nth(machine.jobs, i)}
                    />
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

module MultiNumberInput = {
  // Returns the string from an option if it's not None, otherwise returns a fallback
  let getOptionalString = opt => {
    switch (opt) {
    | Some(opt) => opt
    | None => ""
    };
  };

  [@react.component]
  let make = (~value, ~id=?, ~min=?, ~max=?, ~onChange) => {
    <>
      {React.array(
         Array.init(Array.length(value), i => {
           <input
             type_="number"
             key={string_of_int(i)}
             value={string_of_int(value[i])}
             id={i == 0 ? getOptionalString(id) : ""}
             min={getOptionalString(min)}
             max={getOptionalString(max)}
             onChange={event => {
               let newValue = Array.copy(value);
               newValue[i] =
                 int_of_string(ReactEvent.Form.target(event)##value);
               onChange(newValue);
             }}
           />
         }),
       )}
    </>;
  };
};

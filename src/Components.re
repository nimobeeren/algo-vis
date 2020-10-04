open Utils;

module Job = {
  [@react.component]
  let make = (~size, ~isHighlighted) => {
    <div
      className={"job tube" ++ (isHighlighted ? " tube--primary" : "")}
      ariaLabel={"job of size " ++ string_of_int(size)}
      style={ReactDOM.Style.make(
        ~flexBasis="0", // to ensure flexGrow determines relative size
        ~flexGrow=string_of_int(size),
        (),
      )}>
      <div className="tube__cover" role="presentation" />
      <svg className="job__content" role="presentation" viewBox="0 -4 80 48">
        <text
          x="50%"
          y="50%"
          dominantBaseline="middle"
          textAnchor="middle"
          role="presentation">
          {React.int(size)}
        </text>
      </svg>
    </div>;
  };
};

module BarPlot = {
  [@react.component]
  let make = (~machines: array(LoadBalancing.machine)) => {
    let makespan = LoadBalancing.getMakespan(machines);

    <div
      className="barplot"
      role="figure"
      ariaLabel="Visualization of the computed solution to the load balancing problem">
      {React.array(
         Array.map(
           (machine: LoadBalancing.machine) => {
             let height =
               float_of_int(machine.load) /. float_of_int(makespan) *. 100.;
             let hasMaxMakespan = machine.load == makespan;
             <div
               className="machine"
               key={string_of_int(machine.id)}
               ariaLabel="machine"
               style={ReactDOM.Style.make(
                 ~height=Js.Float.toString(height) ++ "%",
                 (),
               )}>
               {React.array(
                  Array.init(List.length(machine.jobs), i => {
                    <Job
                      key={string_of_int(i)}
                      size={List.nth(machine.jobs, i)}
                      isHighlighted=hasMaxMakespan
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

module NumberInput = {
  [@react.component]
  let make = (~value, ~id=?, ~min=?, ~max=?, ~onChange) => {
    <div className="number-input tube" role="presentation">
      <div className="tube__cover tube__cover--bottom tube__cover--number-input" />
      <input
        type_="number"
        value
        id={getOptionValue(id, "")}
        min={getOptionValue(min, "")}
        max={getOptionValue(max, "")}
        onChange
      />
    </div>;
  };
};

module MultiNumberInput = {
  [@react.component]
  let make = (~value, ~id=?, ~ariaLabelledby=?, ~min=?, ~max=?, ~onChange) => {
    <>
      {React.array(
         Array.init(Array.length(value), i => {
           <input
             type_="number"
             key={string_of_int(i)}
             value={string_of_int(value[i])}
             id={i == 0 ? getOptionValue(id, "") : ""}
             ariaLabelledby={getOptionValue(ariaLabelledby, "")}
             min={getOptionValue(min, "")}
             max={getOptionValue(max, "")}
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

module Select = {
  [@react.component]
  let make = (~children, ~id, ~value, ~onChange) => {
    <div className="select tube" role="presentation">
      <div className="tube__cover tube__cover--bottom tube__cover--select" role="presentation" />
      <select id value onChange> children </select>
      <svg className="select__arrow" role="presentation" viewBox="0 0 12 12">
        <polygon points="1,3 11,3 6,11.66" />
      </svg>
    </div>;
  };
};

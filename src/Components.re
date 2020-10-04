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
  let make = (~value, ~id=?, ~ariaLabelledby=?, ~min=?, ~max=?, ~onChange) => {
    let minString =
      switch (min) {
      | Some(min) => string_of_int(min)
      | None => ""
      };
    let maxString =
      switch (max) {
      | Some(max) => string_of_int(max)
      | None => ""
      };

    <div className="number-input tube" role="presentation">
      <div
        className="tube__cover tube__cover--bottom tube__cover--number-input"
      />
      <input
        type_="number"
        value={string_of_int(value)}
        id={getOptionValue(id, "")}
        ariaLabelledby={getOptionValue(ariaLabelledby, "")}
        min=minString
        max=maxString
        onChange={event => {
          let newValue = ReactEvent.Form.target(event)##value;
          onChange(newValue == "" ? 0 : int_of_string(newValue));
        }}
      />
      <div className="number-input__buttons">
        <button
          className="number-input__button"
          onClick={_ =>
            switch (max) {
            | Some(max) =>
              if (value < max) {
                onChange(value + 1);
              }
            | None => onChange(value + 1)
            }
          }>
          <svg role="presentation" viewBox="0 0 14 14">
            <polygon points="6,6 2.54,12 9.46,12" />
          </svg>
        </button>
        <button
          className="number-input__button"
          onClick={_ =>
            switch (min) {
            | Some(min) =>
              if (value > min) {
                onChange(value - 1);
              }
            | None => onChange(value - 1)
            }
          }>
          <svg role="presentation" viewBox="0 0 14 14">
            <polygon points="6,8 2.54,2 9.46,2" />
          </svg>
        </button>
      </div>
    </div>;
  };
};

module MultiNumberInput = {
  [@react.component]
  // TODO: make min and max optional without breaking everything
  let make = (~value, ~id=?, ~ariaLabelledby, ~min, ~max, ~onChange) => {
    <>
      {React.array(
         Array.init(Array.length(value), i => {
           <NumberInput
             key={string_of_int(i)}
             value={Array.get(value, i)}
             id={i == 0 ? getOptionValue(id, "") : ""}
             ariaLabelledby
             min
             max
             onChange={changedValue => {
               let newValue = Array.copy(value);
               newValue[i] = changedValue;
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
      <div
        className="tube__cover tube__cover--bottom tube__cover--select"
        role="presentation"
      />
      <select id value onChange> children </select>
      <svg className="select__arrow" role="presentation" viewBox="0 0 12 12">
        <polygon points="1,3 11,3 6,11.66" />
      </svg>
    </div>;
  };
};

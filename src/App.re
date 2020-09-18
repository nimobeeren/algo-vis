let style = ReactDOM.Style.make(
  ~fontFamily="sans-serif",
  ()
);

[@react.component]
let make = () => {
  <div style> {React.string("sup")} </div>;
};

let style =
  ReactDOM.Style.make(
    ~maxWidth="800px",
    ~margin="0 auto",
    ~padding="32px",
    (),
  );

[@react.component]
let make = (~children) => {
  <div style> children </div>;
};

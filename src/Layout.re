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

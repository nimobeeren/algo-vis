[@react.component]
let make = (~size) => {
  <div
    style={ReactDOMRe.Style.make(
      ~display="flex",
      ~justifyContent="center",
      ~alignItems="center",
      ~fontSize="20px",
      ~flexBasis="0",
      ~flexGrow=string_of_int(size),
      ~border="1px solid red",
      (),
    )}>
    {React.int(size)}
  </div>;
};

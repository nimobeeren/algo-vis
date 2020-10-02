[@react.component]
let make = (~size) => {
  <div
    style={ReactDOM.Style.make(
      ~display="flex",
      ~justifyContent="center",
      ~alignItems="center",
      ~flexBasis="0", // to ensure flexGrow determines relative size
      ~flexGrow=string_of_int(size),
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

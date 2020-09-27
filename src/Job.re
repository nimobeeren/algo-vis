let possibleColors = [|
  "#ff0000",
  "#00ff00",
  "#0000ff",
  "#ff00ff",
  "#00ffff",
  "#ffff00",
|];

let getColorString: int => string =
  i => {
    let c = possibleColors[i mod Array.length(possibleColors)];
    Js.log(i);
    c;
  };

[@react.component]
// color: number which is mapped to a color
let make = (~size, ~color) => {
  <div
    style={ReactDOMRe.Style.make(
      ~display="flex",
      ~justifyContent="center",
      ~alignItems="center",
      ~flexBasis="0",
      ~flexGrow=string_of_int(size),
      ~background=getColorString(color),
      ~fontSize="20px",
      (),
    )}>
    {React.int(size)}
  </div>;
};

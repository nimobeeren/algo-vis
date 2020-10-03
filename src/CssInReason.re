// LEFT HERE
// Current implementation does not pass on props
// I guess styled should return a component (so a function that takes props and returns a react element)
// Read up on what a component really is:
// - https://reasonml.github.io/reason-react/docs/en/components
// - https://reasonml.github.io/reason-react/docs/en/jsx

// module Box = {
//   [@react.component]
//   let make = (~children, ~style=ReactDOM.Style.make()) => {
//     let boxStyle = ReactDOM.Style.make(~color="red", ());
//     // Does it help to only combine when a style is passed?
//     // But in order to test if style is passed, need to compare with make().
//     // Should test performance of make() vs combine()
//     let combinedStyle = ReactDOM.Style.combine(boxStyle, style);
//     <div style=combinedStyle> children </div>;
//   };
// };

module type MComponent = {
  let make: {. "style": ReactDOM.style} => React.element;
};

module type MStyle = {
  let style: ReactDOM.style;
};

module Styled = (BaseComponent: MComponent, BaseStyle: MStyle) => {
  [@react.component]
  let make = (~style) => {
    BaseComponent.make({
      "style": ReactDOM.Style.combine(BaseStyle.style, style),
    });
  };
};

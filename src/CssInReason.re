module type MComponent = {
  let make: {. "style": ReactDOM.style} => React.element;
};

module type MStyle = {let style: ReactDOM.style;};

// TODO: pass on props to BaseComponent
module Styled = (BaseComponent: MComponent, BaseStyle: MStyle) => {
  // Seems like there's no way to get all props and destructure the style prop from that
  // That means there would be no way to forward all props to the BaseComponent without
  // knowing exactly what those props would be
  let makeProps = (~style, _) => {
    "style": ReactDOM.Style.combine(BaseStyle.style, style),
  };

  let make = BaseComponent.make;
};

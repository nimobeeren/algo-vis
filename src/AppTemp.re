// This is a basic component that passes the `style` prop on to a HTML element
module BaseButton = {
  [@react.component]
  let make = (~style) => {
    <button style> {React.string("Click me")} </button>;
  };
};

// This component also takes a `style` prop, but also applies some default styles
module CoolButton = CssInReason.Styled(BaseButton, {
  let style = ReactDOM.Style.make(~color="blue", ~background="orange", ());
});

[@react.component]
// This style prop is merged with the default styles
let make = () => <CoolButton style={ReactDOM.Style.make(~color="red", ())} />;

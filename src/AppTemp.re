open Styled;

[@react.component]
// let make = () => <BaseButton style={ReactDOM.Style.make()} />;
let make = () => <CoolButton style={ReactDOM.Style.make(~color="red", ())} />;

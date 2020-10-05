open Components;

[@react.component]
let make = () => {
  <>
    <header>
      <ColorModeToggle />
      <a href="https://github.com/nimobeeren/algo-vis"> <Icons.GitHub /> </a>
    </header>
    <Pages.Home />
  </>;
};

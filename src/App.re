open Components;

[@react.component]
let make = () => {
  <>
    <header>
      <ColorModeToggle />
      <a href="https://github.com/nimobeeren/algo-vis" ariaLabel="Visit GitHub repository"> <Icons.GitHub /> </a>
    </header>
    <Pages.Home />
  </>;
};

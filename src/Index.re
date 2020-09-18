// Standard ReactDOM rendering
switch (ReactDOM.querySelector("#root")) {
| Some(root) => ReactDOM.render(<App />, root)
| None => raise(Not_found)
};

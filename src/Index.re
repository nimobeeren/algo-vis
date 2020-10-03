// Standard ReactDOM rendering
switch (ReactDOM.querySelector("#root")) {
| Some(root) => ReactDOM.render(<AppTemp />, root)
| None => raise(Not_found)
};

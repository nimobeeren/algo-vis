open Pages;

// Standard ReactDOM rendering
switch (ReactDOM.querySelector("#root")) {
| Some(root) => ReactDOM.render(<Home />, root)
| None => raise(Not_found)
};

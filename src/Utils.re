// Returns the value of an option if it's not None, otherwise returns a fallback
let getOptionValue: (option('a), 'a) => 'a =
  (opt, fallback) => {
    switch (opt) {
    | Some(opt) => opt
    | None => fallback
    };
  };

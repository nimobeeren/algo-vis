// Returns the value of an option if it's not None, otherwise returns a fallback
let getOptionValue: (option('a), 'a) => 'a =
  (opt, fallback) => {
    switch (opt) {
    | Some(opt) => opt
    | None => fallback
    };
  };

// Takes a duration in number of milliseconds and returns a human readable string
let durationToString: float => string = millis => {
  if (millis < 1.0) {
    let micros = millis *. 1000.0;
    if (micros == 0.0) {
      // If duration is exactly 0, we probably don't have high res timers,
      // so we can't give a better estimation than this
      "<1 ms";
    } else {
      Js.Float.toString(floor(micros)) ++ " us";
    }
  } else if (millis < 1000.0) {
    Js.Float.toString(floor(millis)) ++ " ms";
  } else {
    let secs = millis /. 1000.0;
    Js.Float.toString(floor(secs)) ++ " s";
  }
};

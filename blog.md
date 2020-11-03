## Strong types 💪

One of the biggest advantages of Reason is its strong type system. This allows the compiler to catch bugs before your code even runs. If you're familiar with languages like TypeScript, you may already be used to writing type annotations. While Reason supports this, you often don't even need to specify the types yourself. Instead types are automatically *inferred*. Check out this code:

```reasonml
type machine = {
  id: int,
  jobs: list(int),
  load: int,
};

let createMachine = id => {
  id,
  jobs: [], 
  load: 0
};
```

We created a type called `machine` and a function called `createMachine`. Notice that we never explicitly said that the `createMachine` function should return a `machine`, or what the type of the `id` parameter should be. However, Reason is smart enough to notice the relation between the function and the types we have defined, so it correctly *infers* `createMachine` to be a function that takes an `int` and returns a `machine`.


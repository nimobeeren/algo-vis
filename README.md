# Load Balancing Visualization ⚖️

<div align="center">
  <a href="https://algo-vis.vercel.app/">
    <img alt="Load Balancing Visualization" src="https://raw.githubusercontent.com/nimobeeren/algo-vis/master/images/screenshot.png" height="250px" />
  </a>
</div>


The load balancing problem is about distributing jobs over machines in order to minimize the total processing time, which is called the makespan. This app lets you play with the inputs and visualizes the results of a few different algorithms designed to provide a solution this problem.

Unfortunately, an efficient algorithm that always gives an optimal solution does not exist. This is what is known as an *NP-hard* problem. My friend Henrique wrote [an article on this topic](https://hacdias.com/articles/2020/09/take-approximation-algorithms/), check it out! Each of the algorithms implemented here comes with a different trade-off between running time and approximation ratio. The greedy algorithms will run on large inputs, but their solutions will not be optimal. The brute force algorithm on the other hand will always be optimal, but you'll quickly see running times rise until your browser crashes! 💣

This project was built using [Reason](https://reasonml.github.io/), which is a functional-style programming language that feels a bit like JavaScript. Take a look at the [implementation of the algorithms](https://github.com/nimobeeren/algo-vis/blob/master/src/LoadBalancing.re) to see how it is different from normal JavaScript code. I had never done any functional programming before this project, which made this an interesting experience!

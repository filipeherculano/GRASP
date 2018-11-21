# GRASP
This is a simple implementation of the metaheuristic called GRASP (Greedy Randomized Adaptive Search Procedure). This project tries to solve the Traveling Salesman Problem, given a set of topologies taken from TSPLIB. 

As you may know, the GRASP algorithm has two main parameters: the number of times GRASP is executed and the alpha value. For simplicity, those numbers are static and doesn't react throughout the entire process(alpha = 0.85 and kMaxIter = 30).

To run the project you just need to run
```
make
```
## The algorithm

At the beginnig, we construct a greedy solution for TSP, which is quite simple. From node 0 to node N-1 (N being the number of cities) we chose a neighbor city that is not visited yet and has the lowest traveling cost from our current city. We do this until we visit all N cities. This result is improved with the rest of the GRASP algorithm bellow.

A state on this implementation is defined as a permutation of numbers from 0 to N-1, where each adjacent value is connected, forming a sequence of visited cities. This state can be improved by swaping positions of two nodes. So, in order to know what are the neighbor states of our current one, we need to calculate all the costs of permutating an specific pair of nodes. Those costs may be useful or not regarding this formula:
```
Ci <= Cmin + alpha * (Cmax - Cmin)
```

```
Cmin = minimum solution found

Cmax = maximum solution found

alpha = tightness of candidate list

Ci = current neighbor solution
```

Only those solutions that respect the above formula may enter our Restricted List of Candidates (RLC). To filter even more our RLC, we only take the top 20 solutions, removing the rest. This gives us more quality on our next step (which is quite random :).

Now that we have at most 20 solutions (each one can improve our current one), randomly select a solution from RLC and apply that swap, giving us a new state. We repeat the process above how many times we want (remember this is one of the parameters of the algorithm, along side with the alpha value).

## The results

The results found were quite good, since we didn't implement a more savy alpha with reactive GRASP, and we chose 30 as the maximum number of iterations based on nothing at all.

| # of cities | Optimal solution | initial solution | execution time | best approximation | Difference from optimal |
|-------------|------------------|------------------|----------------|--------------------|-------------------------|
| 17          | 2085             | 2187             | 1.711 ms       | 2085               | 0.00%                   |
| 24          | 1272             | 1553             | 2.876 ms       | 1447               | 13.76%                  |
| 48          | 5046             | 6098             | 11.642 ms      | 5917               | 17.26%                  |
| 175         | 21407            | 22263            | 144.222 ms     | 22137              | 3.41%                   |
| 535         | 48450            | 50144            | 1721.72 ms     | 49898              | 2.99%                   |
| 1032        | 92650            | 94571            | 5898.96 ms     | 94534              | 2.03%                   |

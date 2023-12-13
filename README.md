# Compilation
Requirements for Windows:
- VSCode
- MinGW MSYS2
- Packages installed: gcc, pkg-config, mingw-w64-x86_64-jansson, mingw-w64-x86_64-graphviz

Requirements for Linux:
- Packages installed: gcc, pkg-config, jansson, graphviz

Run the `run.sh` script or press F5 to compile

# Usage
Arguments: `<mode>`

The program runs in following modes:
- 0 - `random` - simulated random activity with the data provided
- 1 - `brute` - tries to guess blocks needed to reach a state via brute force
- 2 - `greedy` - tries to guess blocks needed to reach a state via a greedy algorithm
- 3 - `greedy-randomized` - tries to guess blocks needed to reach a state via a randomized greedy algorithm
- 4 - `metaheuristic` - applies a heuristic algorithm to try and solve the problem



If not provided, the default mode is `random`.

The program accepts the following data:
- raw json text passed as a string
- a filename for a json file
- piped input (stdin)

There are several python scripts provided to help generate and prepare data for testing.\
Base data, such as one included in `examples/example.json` or generated by `scripts/random_input.py` needs to be turned into a valid test by piping it into one of the `scripts/test_` files. Then, the following test, or one of provided `examples/example_` files should be piped into the main program. The following output can be piped into `scripts/json_to_graphviz.py` to generate a DOT language file for visualization with software such as GraphViz.


Example usage:
```
cat examples/example.json | ./main.exe
```

Visualization example (GraphViz):
```
cat examples/example.json | python3 scripts/test_greedy_randomized.py 2 2 6 | tee tests/input.json | ./main.exe | tee tests/output.json | python3 scripts/json_to_graphviz.py | tee tests/viz.dot | dot -Tpng > tests/viz.png
```
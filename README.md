# Compilation
Requirements:
- VSCode
- MinGW MSYS2
- Packages installed: gcc, pkg-config, mingw-w64-x86_64-jansson, mingw-w64-x86_64-graphviz

Run the `run.sh` script or press F5 to compile

# Usage
Arguments: `<mode>`

The program runs in following modes:
- 0 - `random` - simulated random activity with the data provided
- 1 - `brute` - tries to guess blocks needed to reach a state

If not provided, the default mode is `random`.

The program accepts the following data:
- raw json text passed as a string
- a filename for a json file
- piped input (stdin)

There are several python scripts provided to help generate and prepare data for testing.

Example usage:
```
./main.exe random example.json
```

```
./main.exe '{"particles":[0],"blocks":[["ee->pp",2,0,10,[0,0,-1,-1],[2,2,-1,-1]],["qq->",2,1,20,[1,1,-1,-1],[-1,-1,-1,-1]],["p->qe",2,2,30,[2,-1,-1,-1],[1,0,-1,-1]],["eq->p",2,3,15,[0,1,-1,-1],[2,-1,-1,-1]]]}'
```

```
cat example.json | ./main.exe
```

Visualization example (GraphViz):
```
cat example.json | ./main.exe | python3 scripts/json_to_graphviz.py | dot -Tpng > viz.png
```
```
python3 scripts/random_input.py | tee tests/input.json | ./main.exe | tee tests/output.json | python3 scripts/json_to_graphviz.py | tee tests/viz.dot | dot -Tpng > tests/viz.png
```
```
cat example.json | python3 scripts/test_brute.py 2 2 6 | tee tests/input.json | ./main.exe | tee tests/output.json | python3 scripts/json_to_graphviz.py | tee tests/viz.dot | dot -Tpng > tests/viz.png
```
# Compilation
Requirements:
- VSCode
- MinGW MSYS2
- Packages installed: gcc, pkg-config, mingw-w64-x86_64-jansson, mingw-w64-x86_64-graphviz

Run the `run.sh` script or press F5 to compile

# Usage
Arguments: `<mode>`, `[data]`

The program runs in following modes:
- `random` - simulated random activity with the data provided
- `brute` - tries to guess blocks needed to reach a state

The program accepts the following data:
- raw json text passed as a string
- a filename for a json file
- piped input (stdin)

Example usage:
```
./main.exe random example.json
```

```
./main.exe random '{"particles":[0],"blocks":[["ee->pp",2,0,10,[0,0,-1,-1],[2,2,-1,-1]],["qq->",2,1,20,[1,1,-1,-1],[-1,-1,-1,-1]],["p->qe",2,2,30,[2,-1,-1,-1],[1,0,-1,-1]],["eq->p",2,3,15,[0,1,-1,-1],[2,-1,-1,-1]]]}'
```

```
cat example.json | ./main.exe random
```

Visualization example (GraphViz):
```
cat example.json | ./main.exe | python3 scripts/json_to_graphviz.py | dot -Tpng > viz.png
```
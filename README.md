# Compilation
Requirements:
- VSCode
- MinGW MSYS2
- Packages installed: gcc, pkg-config, mingw-w64-x86_64-jansson

Run the `run.sh` script or press F5

Example usage:
```
./run.sh '{"particles":[0],"blocks":[["ee->pp",2,0,10,[0,0,-1,-1],[2,2,-1,-1]],["qq->",2,1,20,[1,1,-1,-1],[-1,-1,-1,-1]],["p->qe",2,2,30,[2,-1,-1,-1],[1,0,-1,-1]],["eq->p",2,3,15,[0,1,-1,-1],[2,-1,-1,-1]]]}'
```
```
cat example_data.exe | ./run.sh
```

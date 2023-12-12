import subprocess
import os
import json
import collections

# Get random solution
input_data = subprocess.Popen(["python","scripts/random_input.py"], shell=True, stdout=subprocess.PIPE)
out1, err1 = input_data.communicate()

test_data = subprocess.Popen(["python", "scripts/test_random.py"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
out2, err2 = test_data.communicate(input=out1)

output = subprocess.Popen([os.path.join(os.path.dirname(__file__))+"/../main.exe"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
out3random, err3 = output.communicate(input=out2)

fparts_initial = [fp[0] for fp in json.loads(out1)["particles"]]
print(fparts_initial)

fparts = json.loads(out3random)["fparts"]
fparts = [fp["name"] for fp in fparts]
fparts_counter = collections.Counter(fparts)
print(fparts_counter)

desired_output = [fparts_counter[fp] if fp in fparts_counter else 0 for fp in fparts_initial]
print("DESIRED OUTPUT:", desired_output)

# Run brute force
test_data = subprocess.Popen(["python", "scripts/test_brute.py", *[str(x) for x in desired_output]], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
out2, err2 = test_data.communicate(input=out1)

output = subprocess.Popen([os.path.join(os.path.dirname(__file__))+"/../main.exe"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
out3, err3 = output.communicate(input=out2)

dot = subprocess.Popen(["python", "scripts/json_to_graphviz.py"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
out4, err4 = dot.communicate(input=out3)

viz = subprocess.Popen(["dot", "-Tpng"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
out5, err5 = viz.communicate(input=out4)

print(out3random, "\n", out2, "\n", out3)

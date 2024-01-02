import json
import collections
import subprocess
import sys
import os

args = sys.argv[1:]

# Get random solution
input_data = subprocess.Popen(["python","scripts/random_input.py", *args], shell=True, stdout=subprocess.PIPE)
out1, err1 = input_data.communicate()

test_data = subprocess.Popen(["python", "scripts/test_random.py"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
out2, err2 = test_data.communicate(input=out1)

output = subprocess.Popen([os.path.join(os.path.dirname(__file__))+"/../main.exe"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
out3random, err3 = output.communicate(input=out2)

fparts_initial = [fp[0] for fp in json.loads(out1)["particles"]]

fparts = json.loads(out3random)["fparts"]
fparts = [fp["name"] for fp in fparts if fp["deleted"] == 0]
fparts_counter = collections.Counter(fparts)

desired_output = [fparts_counter[fp] if fp in fparts_counter else 0 for fp in fparts_initial]

problem = json.loads(str(out2)[2:-5])
problem["test_data"] = desired_output

print(json.dumps(problem))

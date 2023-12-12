import subprocess
import os
import json
import collections
import statistics

log = False
results = []
repeats = 10

for i in range(repeats):

	# Get random solution
	input_data = subprocess.Popen(["python","scripts/random_input.py"], shell=True, stdout=subprocess.PIPE)
	out1, err1 = input_data.communicate()

	test_data = subprocess.Popen(["python", "scripts/test_random.py"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	out2, err2 = test_data.communicate(input=out1)

	output = subprocess.Popen([os.path.join(os.path.dirname(__file__))+"/../main.exe"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	out3random, err3 = output.communicate(input=out2)

	fparts_initial = [fp[0] for fp in json.loads(out1)["particles"]]
	if log: print(fparts_initial)

	fparts = json.loads(out3random)["fparts"]
	fparts = [fp["name"] for fp in fparts if fp["deleted"] == 0]
	fparts_counter = collections.Counter(fparts)
	if log: print(fparts_counter)

	desired_output = [fparts_counter[fp] if fp in fparts_counter else 0 for fp in fparts_initial]
	if log: print("DESIRED OUTPUT:", desired_output)



	# Run brute force
	test_data = subprocess.Popen(["python", "scripts/test_brute.py", *[str(x) for x in desired_output]], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	out2, err2 = test_data.communicate(input=out1)
	if log: print(out2)

	output = subprocess.Popen([os.path.join(os.path.dirname(__file__))+"/../main.exe"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
	out3, err3 = output.communicate(input=out2)
	if log: print(out3)

	print("=======================\n",out3)

	js = json.loads(out3)
	results.append({ "success": js["success"], "time": js["time"] }) # Only what's needed

print(results)
print("Average time:", statistics.mean([r["time"] for r in results]), "deviation", statistics.stdev([r["time"] for r in results]))
print("Success rate:", statistics.mean([r["success"] for r in results]))

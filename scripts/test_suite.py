import subprocess
import os
import json
import collections
import statistics


log = False


def get_desired_output(args):
	# Get random solution
	input_data = subprocess.Popen(["python","scripts/random_input.py", *args], shell=True, stdout=subprocess.PIPE)
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

	return out1, [str(x) for x in desired_output]


results = []
repeats = 2
args = [str(x) for x in [6, 4, 10, 12]]

test_types = ["scripts/test_brute.py", "scripts/test_greedy.py", "scripts/test_greedy_randomized.py", "scripts/test_metaheuristic.py"]

final_results = []

for test in test_types:
	for fpart_amount in range(4, 12+1, 2):
		for fblock_amount in range(4, 12+1, 2):
			args = [str(x) for x in [6, 4, fpart_amount, fblock_amount]]
			results = []

			for i in range(repeats):

				input, desired_output = get_desired_output(args)

				# Run brute force
				test_data = subprocess.Popen(["python", test, *desired_output], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
				test_data, _ = test_data.communicate(input=input)
				if log: print(test_data)

				output = subprocess.Popen([os.path.join(os.path.dirname(__file__))+"/../main.exe"], shell=True, stdin=subprocess.PIPE, stdout=subprocess.PIPE)
				test_results, _ = output.communicate(input=test_data)
				if log: print(test_results)

				try:
					js = json.loads(test_results)
				except:
					print("Error with data:", test_results)
					continue

				results.append({ "success": js["success"], "time": js["time"] }) # Only what's needed

			print("--------------------------------------------------")
			print(test, args)
			print(results)
			final_results.append((test, args, results))
			print("Average time:", statistics.mean([r["time"] for r in results]), "deviation", statistics.stdev([r["time"] for r in results]))
			print("Success rate:", statistics.mean([r["success"] for r in results]), "deviation", statistics.stdev([r["success"] for r in results]))
			print("--------------------------------------------------")

print(final_results)
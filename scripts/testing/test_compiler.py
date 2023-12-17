import json
import statistics

with open("scripts/testing/test_results.json", "r") as f:
	data = json.loads(f.readline())["results"]

test_types = ["scripts/test_brute.py", "scripts/test_greedy.py", "scripts/test_greedy_randomized.py", "scripts/test_metaheuristic.py"]
test_data = dict()

for test in test_types:
	tres = list(filter(lambda x: x["type"] == test, data))
	test_data[test] = [
		[t["fpart_amount"], t["fblock_amount"], statistics.mean([r["time"] for r in t["results"]]), statistics.stdev([r["time"] for r in t["results"]]), statistics.mean([r["success"] for r in t["results"]]), statistics.stdev([r["success"] for r in t["results"]])]
	for t in tres]

print(test_data)

import json
import statistics
import matplotlib.pyplot as plt

with open("test_results.json", "r") as f:
	data = json.loads(f.readline())["results"]

test_types = ["scripts/test_brute.py", "scripts/test_greedy.py", "scripts/test_greedy_randomized.py", "scripts/test_metaheuristic.py"]
test_data = dict()

for test in test_types:
	tres = list(filter(lambda x: x["type"] == test, data))
	test_data[test] = [
		[t["fpart_amount"], t["fblock_amount"], statistics.mean([r["time"] for r in t["results"]]), statistics.stdev([r["time"] for r in t["results"]]), statistics.mean([r["success"] for r in t["results"]]), statistics.stdev([r["success"] for r in t["results"]])]
	for t in tres]

#print(data)


# Results per fblock amount
plot_x = list(range(4, 50+1, 2))
plot_y_success = {}
plot_y_time = {}

fpart_amount= 12
for test in test_types:
	if test not in plot_y_success:
		plot_y_success[test] = {}
		plot_y_time[test] = {}

	tres = list(filter(lambda x: x["type"] == test and x["fpart_amount"] == fpart_amount, data))

	for d in tres:
		_type = d["type"]
		_fpart_amount = d["fpart_amount"]
		_fblock_amount = d["fblock_amount"]
		_results = d["results"]

		if _fblock_amount not in plot_y_success[test]:
			plot_y_success[test][_fblock_amount] = []
			plot_y_time[test][_fblock_amount] = []

		plot_y_success[test][_fblock_amount].append([x["success"] for x in _results])
		plot_y_time[test][_fblock_amount].append([x["time"] for x in _results])

# Replace results with mean and stdev
print(plot_y_success)
print(plot_y_time)
for test in plot_y_success:
	for count in plot_y_success[test]:
		plot_y_success[test][count] = (statistics.mean(*plot_y_success[test][count]), statistics.stdev(*plot_y_success[test][count]))
for test in plot_y_time:
	for count in plot_y_time[test]:
		plot_y_time[test][count] = (statistics.mean(*plot_y_time[test][count]), statistics.stdev(*plot_y_time[test][count]))

print(plot_y_success)
print(plot_y_time)

plt.figure()
for test in plot_y_success:
	x = plot_x[:len(plot_y_success[test].values())]
	y = [x[0] for x in plot_y_success[test].values()]
	err = [x[1]*0 for x in plot_y_success[test].values()]
	plt.errorbar(x, y, err)
plt.show()

plt.figure()
for test in plot_y_time:
	x = plot_x[:len(plot_y_time[test].values())]
	y = [x[0] for x in plot_y_time[test].values()]
	err = [x[1]*0 for x in plot_y_time[test].values()]
	plt.errorbar(x, y, err)
#plt.yscale('log')
plt.show()

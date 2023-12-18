import json
import statistics
import matplotlib.pyplot as plt

with open("test_results.json", "r") as f:
	data = json.loads(f.readline())["results"]

test_types = ["scripts/test_brute.py", "scripts/test_greedy.py", "scripts/test_greedy_randomized.py", "scripts/test_metaheuristic.py"]

# Results per fblock amount
plot_x = list(range(4, 100+1, 2))
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
		if len(*plot_y_success[test][count]) > 1:
			plot_y_success[test][count] = (statistics.mean(*plot_y_success[test][count]), statistics.stdev(*plot_y_success[test][count]))
		else:
			plot_y_success[test][count] = (*plot_y_success[test][count], 0)

for test in plot_y_time:
	for count in plot_y_time[test]:
		if len(*plot_y_time[test][count]) > 1:
			plot_y_time[test][count] = (statistics.mean(*plot_y_time[test][count]), statistics.stdev(*plot_y_time[test][count]))
		else:
			plot_y_time[test][count] = (*plot_y_time[test][count], 0)

print(plot_y_success)
print(plot_y_time)

colors = ["deepskyblue", "darkorchid", "springgreen", "red"]
colors_err = ["lightskyblue", "plum", "palegreen", "lightcoral"]

plt.figure()
for test in plot_y_success:
	x = plot_x[:len(plot_y_success[test].values())]
	y = [x[0] for x in plot_y_success[test].values()]
	err = [x[1] for x in plot_y_success[test].values()]
	plt.errorbar(x, y, err, linewidth=3, elinewidth=2, color=colors[test_types.index(test)], ecolor=colors_err[test_types.index(test)], capsize=6, capthick=2, label=test.split("_")[1].replace(".py", "").capitalize())
plt.legend()
plt.title("Poprawność algorytmów dla zmiennej liczby bloków")
plt.show()

plt.figure()
for test in plot_y_time:
	x = plot_x[:len(plot_y_time[test].values())]
	y = [x[0] for x in plot_y_time[test].values()]
	err = [x[1] for x in plot_y_time[test].values()]
	plt.errorbar(x, y, err, linewidth=3, elinewidth=2, color=colors[test_types.index(test)], ecolor=colors_err[test_types.index(test)], capsize=6, capthick=2, label=test.split("_")[1].replace(".py", "").capitalize())
#plt.yscale('log')
plt.ylim([0, 0.025])
plt.legend()
plt.title("Czas wykonania algorytmów dla zmiennej liczby bloków")
plt.show()



# Results per fpart amount
plot_x = list(range(4, 100+1, 2))
plot_y_success = {}
plot_y_time = {}

fblock_amount= 12
for test in test_types:
	if test not in plot_y_success:
		plot_y_success[test] = {}
		plot_y_time[test] = {}

	tres = list(filter(lambda x: x["type"] == test and x["fblock_amount"] == fblock_amount, data))

	for d in tres:
		_type = d["type"]
		_fpart_amount = d["fpart_amount"]
		_fblock_amount = d["fblock_amount"]
		_results = d["results"]

		if _fpart_amount not in plot_y_success[test]:
			plot_y_success[test][_fpart_amount] = []
			plot_y_time[test][_fpart_amount] = []

		plot_y_success[test][_fpart_amount].append([x["success"] for x in _results])
		plot_y_time[test][_fpart_amount].append([x["time"] for x in _results])

# Replace results with mean and stdev
print(plot_y_success)
print(plot_y_time)

for test in plot_y_success:
	for count in plot_y_success[test]:
		if len(*plot_y_success[test][count]) > 1:
			plot_y_success[test][count] = (statistics.mean(*plot_y_success[test][count]), statistics.stdev(*plot_y_success[test][count]))
		else:
			plot_y_success[test][count] = (*plot_y_success[test][count], 0)

for test in plot_y_time:
	for count in plot_y_time[test]:
		if len(*plot_y_time[test][count]) > 1:
			plot_y_time[test][count] = (statistics.mean(*plot_y_time[test][count]), statistics.stdev(*plot_y_time[test][count]))
		else:
			plot_y_time[test][count] = (*plot_y_time[test][count], 0)

print(plot_y_success)
print(plot_y_time)

colors = ["deepskyblue", "darkorchid", "springgreen", "red"]
colors_err = ["lightskyblue", "plum", "palegreen", "lightcoral"]

plt.figure()
for test in plot_y_success:
	x = plot_x[:len(plot_y_success[test].values())]
	y = [x[0] for x in plot_y_success[test].values()]
	err = [x[1] for x in plot_y_success[test].values()]
	plt.errorbar(x, y, err, linewidth=3, elinewidth=2, color=colors[test_types.index(test)], ecolor=colors_err[test_types.index(test)], capsize=6, capthick=2, label=test.split("_")[1].replace(".py", "").capitalize())
plt.legend()
plt.title("Poprawność algorytmów dla zmiennej liczby cząsteczek")
plt.show()

plt.figure()
for test in plot_y_time:
	x = plot_x[:len(plot_y_time[test].values())]
	y = [x[0] for x in plot_y_time[test].values()]
	err = [x[1] for x in plot_y_time[test].values()]
	plt.errorbar(x, y, err, linewidth=3, elinewidth=2, color=colors[test_types.index(test)], ecolor=colors_err[test_types.index(test)], capsize=6, capthick=2, label=test.split("_")[1].replace(".py", "").capitalize())
#plt.yscale('log')
plt.ylim([0, 0.025])
plt.legend()
plt.title("Czas wykonania algorytmów dla zmiennej liczby cząsteczek")
plt.show()

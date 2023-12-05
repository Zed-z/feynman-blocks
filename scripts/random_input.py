import sys
import json
import random

fpart_n = 6
fblock_n = 5
max_io = 4

fparts = random.choices(["e-", "e+", "q", "¬q", "g", "p", "¬p", "νμ", "α", "β", "γ"], k=fpart_n)


data = dict()
data["particles"] = [[fp, random.randint(0, 3)] for fp in fparts]

blocks = []
for i in range(fblock_n):
	input = random.choices(fparts, k=random.randint(0, max_io))
	output = random.choices(fparts, k=random.randint(0, max_io))
	count = random.randint(0, 3)
	name = " ".join(input) + " -> " + " ".join(output)
	blocks.append([name, count, input, output])
data["blocks"] = blocks


print(json.dumps(data))
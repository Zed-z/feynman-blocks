import sys
import json
import random

fpart_n = 3
fblock_n = 4

fparts = random.choices(["e", "q", "p", "n", "b"], k=fpart_n)


data = dict()
data["particles"] = [[fp, random.randint(0, 5)] for fp in fparts]

blocks = []
for i in range(fblock_n):
	input = random.choices(fparts, k=random.randint(0, fpart_n))
	output = random.choices(fparts, k=random.randint(0, fpart_n))
	count = random.randint(0, 3)
	name = "".join(input) + "->" + "".join(output)
	blocks.append([name, count, input, output])
data["blocks"] = blocks


print(json.dumps(data))
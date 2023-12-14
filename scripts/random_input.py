import sys
import json
import random


if len(sys.argv) > 1:
	fpart_types = int(sys.argv[1])
	fblock_types = int(sys.argv[2])
	fpart_amount = int(sys.argv[3])
	fblock_amount = int(sys.argv[4])
else:
	fpart_types = 6
	fblock_types = 4
	fpart_amount = 10
	fblock_amount = 10


max_io = 4
fpart_amounts_chosen = random.choices(range(fpart_types), k=fpart_amount)
fblock_amounts_chosen = random.choices(range(fblock_types), k=fblock_amount)

fparts = random.sample(["e-", "e+", "q", "¬q", "g", "p", "¬p", "νμ", "α", "β", "γ", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "Q", "P", "R", "S", "T", "U", "V", "W", "X", "Y", "Z"], k=fpart_types)


data = dict()
data["particles"] = [[fparts[i], fpart_amounts_chosen.count(i)] for i in range(len(fparts))]


blocks = []
for i in range(fblock_types):
	input = random.choices(fparts, k=random.randint(0, max_io))
	output = random.choices(fparts, k=random.randint(0, max_io))
	count = fblock_amounts_chosen.count(i)
	name = " ".join(input) + " -> " + " ".join(output)
	blocks.append([name, count, input, output])
data["blocks"] = blocks


print(json.dumps(data))
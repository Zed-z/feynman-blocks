import sys
import json
import random

for line in sys.stdin:
	line = line.rstrip()
	if not line.startswith("{"):
		continue

	data = json.loads(line)

	data["test_mode"] = 2
	if "test_data" not in data:
		data["test_data"] = [int(x) for x in sys.argv[1:]] if len(sys.argv[1:]) > 0 else [random.randint(0, parttype[1]) for parttype in data["particles"]]

	print(json.dumps(data))

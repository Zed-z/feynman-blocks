import sys
import json

for line in sys.stdin:
	line = line.rstrip()
	if not line.startswith("{"):
		continue

	data = json.loads(line)

	data["test_mode"] = 0

	print(json.dumps(data))

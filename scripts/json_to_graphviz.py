import sys
import json

for line in sys.stdin:
	line = line.rstrip()
	if not line.startswith("{"):
		continue

	data = json.loads(line)
	#print(data)

	fblocks = data["fblocks"]
	fparts = data["fparts"]


	print("digraph G {")

	# Print all particles possible
	for fp in fparts:
		print(f"fp{fp['id']} [label=\"{fp['name']}\"]")

	# Print blocks
	for fb in fblocks:
		print(f"fb{fb['id']} [label=\"{fb['name']}\", shape=box]")

	# Print block connections
	for fb in fblocks:
		for i in fb['input']:
			print(f"fp{i} -> fb{fb['id']}")
		for i in fb['output']:
			print(f"fb{fb['id']} -> fp{i}")

	print("}")

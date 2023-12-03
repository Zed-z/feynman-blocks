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

		# Deleted fparts
		color = "brown1"
		style = "dashed"
		shape = "diamond"

		# Final fparts
		if fp['deleted'] == 0:
			shape = "house"
			style = "filled"

		# Initial fparts
		if fp['source'] == -1:
			color = "white"
			style = "filled"
			shape = "invhouse"

		# Final fparts
		if fp['deleted'] == 0:
			color = "steelblue1"

		print(f"fp{fp['id']} [label=\"{fp['name']}\" style={style} fillcolor={color} shape={shape}]")

	# Print blocks
	for fb in fblocks:
		print(f"fb{fb['id']} [label=\"{fb['name']}\", shape=box style={'filled' if (len(fb['input']) > 0 or len(fb['output']) > 0) else 'dashed'}]")

	# Print block connections
	for fb in fblocks:
		for i in fb['input']:
			print(f"fp{i} -> fb{fb['id']}")
		for i in fb['output']:
			print(f"fb{fb['id']} -> fp{i}")

	print("}")

import sys
import json

for line in sys.stdin:
	line = line.rstrip()
	if not line.startswith("{"):
		continue

	data = json.loads(line)
	print(data)

	fblocks = data["fblocks"]
	fparts = data["fparts"]


	print("digraph G {")

	# Print literally all particles possible
	all_possible_fparts = set()
	for fp in fparts:
		all_possible_fparts.add(fp['id'])
	for fb in fblocks:
		for i in fb['input']:
			all_possible_fparts.add(i)
		for i in fb['output']:
			all_possible_fparts.add(i)

	for fp in all_possible_fparts:
		print(f"fp{fp}")

	# Print particles again, this time known ones so labels get added
	for fp in fparts:
		print(f"fp{fp['id']} [label=\"{fp['name']}\"]")

	# Print blocks
	for fb in fblocks:
		print(f"fb{fb['id']} [label=\"{fb['name']}\", shape=box]")

	# Print block connections, use them to update particle labels when unknown maybe?? TODO
	for fb in fblocks:
		for i in fb['input']:
			print(f"fp{i} -> fb{fb['id']}")
		for i in fb['output']:
			print(f"fb{fb['id']} -> fp{i}")

# maybe don't remove particles when "deleting" them, instead mark them as deleted
# so that figuring out this tree is easier
	print("}")

import sys
import os
import json
import subprocess
import glob

# Find all EXACT C files
c_files = glob.glob("src/server.dll/*.c")
exact_files = []

for f in c_files:
    with open(f, "r") as file:
        content = file.read()
        if "STATUS: EXACT" in content:
            exact_files.append((f, content))

print(f"Found {len(exact_files)} EXACT C files.")

# Create the data payload
data = "# server.dll EXACT C Files\n\n"
data += "These are the fully reversed, byte-for-byte exact C functions from the game server.dll.\n\n"

for name, content in exact_files:
    data += f"## File: {name}\n"
    data += f"```c\n{content}\n```\n\n"

# Use cognee-call.py
args = json.dumps({"data": data})

print("Calling cognify via cognee-call.py...")
subprocess.run([sys.executable, "scripts/cognee-call.py", "cognify", args])

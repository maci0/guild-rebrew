import sys
import json
import subprocess

search_query = "What functions use GetTickCount or deal with timeouts?"
args = json.dumps({
    "search_query": search_query,
    "search_type": "GRAPH_COMPLETION",
    "top_k": 5
})

print(f"Searching: {search_query}")
subprocess.run([sys.executable, "scripts/cognee-call.py", "search", args])

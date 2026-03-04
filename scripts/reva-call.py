#!/usr/bin/env python3
import sys
import json
import httpx

endpoint = "http://localhost:8080/mcp/message"
method = sys.argv[1]
args = json.loads(sys.argv[2]) if len(sys.argv) > 2 else {}

headers = {
    "Accept": "application/json, text/event-stream",
    "Content-Type": "application/json",
}

with httpx.Client(timeout=30.0) as client:
    resp = client.post(
        endpoint,
        json={"jsonrpc": "2.0", "id": 1, "method": "initialize", "params": {"protocolVersion": "2024-11-05", "capabilities": {}, "clientInfo": {"name": "cli", "version": "1"}}},
        headers=headers
    )
    if resp.status_code != 200:
        print("Init failed:", resp.text)
        sys.exit(1)
        
    sid = resp.headers.get("mcp-session-id")
    if not sid:
        print("No session ID in header:", resp.headers)
        sys.exit(1)
        
    msg_url = f"{endpoint}?sessionId={sid}"
    headers["mcp-session-id"] = sid
    
    client.post(msg_url, json={"jsonrpc": "2.0", "method": "notifications/initialized"}, headers=headers)
    
    res = client.post(msg_url, json={"jsonrpc": "2.0", "id": 2, "method": method, "params": args}, headers=headers)
    for line in res.text.split("\n"):
        if line.startswith("data: "):
            print(json.dumps(json.loads(line[6:]), indent=2))

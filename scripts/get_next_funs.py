#!/usr/bin/env python3
import sys
import json
import httpx

ENDPOINT = "http://localhost:8080/mcp/message"
PROGRAM = "/Europa1400Gold_TL.exe"

def main():
    headers = {"Accept": "application/json, text/event-stream", "Content-Type": "application/json"}
    with httpx.Client(timeout=60.0) as client:
        resp = client.post(ENDPOINT, json={"jsonrpc": "2.0", "id": 1, "method": "initialize", "params": {"protocolVersion": "2024-11-05", "capabilities": {}, "clientInfo": {"name": "cli", "version": "1"}}}, headers=headers)
        sid = resp.headers.get("mcp-session-id") or resp.json().get("sessionId")
        headers["mcp-session-id"] = sid
        client.post(f"{ENDPOINT}?sessionId={sid}", json={"jsonrpc": "2.0", "method": "notifications/initialized"}, headers=headers)
        
        # Get count
        msg_url = f"{ENDPOINT}?sessionId={sid}"
        
        found = []
        batch_size = 500
        # Start looking from roughly where we left off (address 0x00407800)
        # We can just iterate until we find 5 FUN_s
        for start in range(100, 5000, batch_size):
            res = client.post(msg_url, json={"jsonrpc": "2.0", "id": 2, "method": "tools/call", "params": {"name": "get-functions", "arguments": {"programPath": PROGRAM, "filterDefaultNames": False, "maxCount": batch_size, "startIndex": start}}}, headers=headers)
            for line in res.text.split("\n"):
                if line.startswith("data: "):
                    try:
                        data = json.loads(line[6:])
                        if "result" in data and "content" in data["result"]:
                            for content in data["result"]["content"]:
                                obj = json.loads(content["text"])
                                if "name" in obj and obj["name"].startswith("FUN_"):
                                    found.append(obj)
                                    if len(found) >= 5:
                                        for f in found:
                                            print(f"{f['address']} - {f['name']}")
                                        return
                    except Exception as e:
                        pass
                        
if __name__ == "__main__":
    main()

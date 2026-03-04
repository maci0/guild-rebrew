#!/usr/bin/env python3
import sys
import json
import time
import threading
import requests

BASE = "http://127.0.0.1:8080"

def main():
    print(f"[*] Connecting SSE to {BASE}...", flush=True)
    try:
        resp = requests.get(f"{BASE}/sse", stream=True, timeout=10)
    except Exception as e:
        print(f"Failed: {e}")
        sys.exit(1)
        
    session_id = None
    messages = []
    lock = threading.Lock()

    def listen():
        nonlocal session_id
        event_type = None
        data_lines = []
        for raw_line in resp.iter_lines(decode_unicode=True):
            line = raw_line.strip() if raw_line else ""
            if line.startswith("event:"):
                event_type = line[len("event:") :].strip()
            elif line.startswith("data:"):
                data_lines.append(line[len("data:") :].strip())
            elif line == "" and event_type:
                data = "\n".join(data_lines)
                if event_type == "endpoint" and "session_id=" in data:
                    session_id = data.split("session_id=")[1]
                    print(f"[*] Session: {session_id}", flush=True)
                elif event_type == "message":
                    try:
                        with lock:
                            messages.append(json.loads(data))
                    except json.JSONDecodeError:
                        pass
                event_type = None
                data_lines = []

    t = threading.Thread(target=listen, daemon=True)
    t.start()

    for _ in range(50):
        if session_id: break
        time.sleep(0.1)

    if not session_id:
        print("No session ID")
        return

    msg_url = f"{BASE}/message?sessionId={session_id}"
    req_id = 0

    def send(method, params=None):
        nonlocal req_id
        req_id += 1
        payload = {"jsonrpc": "2.0", "id": req_id, "method": method}
        if params: payload["params"] = params
        requests.post(msg_url, json=payload, timeout=10)
        return req_id

    def wait_response(rid, timeout=10):
        deadline = time.time() + timeout
        while time.time() < deadline:
            with lock:
                for m in messages:
                    if m.get("id") == rid:
                        messages.remove(m)
                        return m
            time.sleep(0.5)
        return None

    rid = send("initialize", {"protocolVersion": "2024-11-05", "capabilities": {}, "clientInfo": {"name": "cli", "version": "1"}})
    init_resp = wait_response(rid)
    requests.post(msg_url, json={"jsonrpc": "2.0", "method": "notifications/initialized"}, timeout=10)
    
    print("[*] Listing tools...", flush=True)
    rid = send("tools/list")
    result = wait_response(rid, timeout=10)
    if result:
        print(json.dumps(result, indent=2))
    else:
        print("Timeout")

if __name__ == "__main__":
    main()

#!/usr/bin/env python3
"""Call Cognee MCP tools via SSE transport with proper protocol handshake.
No external dependencies beyond stdlib + requests."""

import sys
import json
import time
import threading
import requests

BASE = "http://127.0.0.1:8000"


def main():
    tool_name = sys.argv[1] if len(sys.argv) > 1 else "cognify_status"
    tool_args = {}
    if len(sys.argv) > 2:
        tool_args = json.loads(sys.argv[2])

    print(f"[*] Connecting SSE...", flush=True)
    resp = requests.get(f"{BASE}/sse", stream=True, timeout=300)

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
        if session_id:
            break
        time.sleep(0.1)
    if not session_id:
        print("[!] Failed to get session ID", flush=True)
        sys.exit(1)

    msg_url = f"{BASE}/messages/?session_id={session_id}"
    req_id = 0

    def send(method, params=None):
        nonlocal req_id
        req_id += 1
        payload = {"jsonrpc": "2.0", "id": req_id, "method": method}
        if params:
            payload["params"] = params
        requests.post(msg_url, json=payload, timeout=60)
        return req_id

    def wait_response(rid, timeout=300):
        deadline = time.time() + timeout
        while time.time() < deadline:
            with lock:
                for m in messages:
                    if m.get("id") == rid:
                        messages.remove(m)
                        return m
            time.sleep(0.5)
        return None

    # Initialize
    print("[*] Initializing MCP session...", flush=True)
    rid = send(
        "initialize",
        {
            "protocolVersion": "2024-11-05",
            "capabilities": {},
            "clientInfo": {"name": "cognee-cli", "version": "1.0.0"},
        },
    )
    init_resp = wait_response(rid, timeout=60)
    if not init_resp:
        print("[!] Initialize timeout", flush=True)
        sys.exit(1)
    server_info = init_resp.get("result", {}).get("serverInfo", {})
    print(f"[*] Server: {server_info}", flush=True)

    # Send initialized notification (no id = notification)
    req_id += 1
    requests.post(
        msg_url, json={"jsonrpc": "2.0", "method": "notifications/initialized"}, timeout=60
    )
    time.sleep(0.5)

    # Call tool
    print(f"[*] Calling {tool_name}({json.dumps(tool_args)})...", flush=True)
    rid = send("tools/call", {"name": tool_name, "arguments": tool_args})
    result = wait_response(rid, timeout=300)
    if result:
        if "error" in result:
            print(f"[!] Error: {json.dumps(result['error'], indent=2)}", flush=True)
            sys.exit(1)
        content = result.get("result", {}).get("content", [])
        for item in content:
            print(f"\n--- Result ---", flush=True)
            print(item.get("text", json.dumps(item, indent=2)), flush=True)
    else:
        print("[!] Timeout waiting for response", flush=True)
        sys.exit(1)


if __name__ == "__main__":
    main()

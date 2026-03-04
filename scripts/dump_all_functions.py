#!/usr/bin/env python3
import sys
import json
import time
import httpx
import os
import threading

ENDPOINT = "http://localhost:8080/mcp/message"
PROGRAM = "/Europa1400Gold_TL.exe"

def create_client():
    headers = {"Accept": "application/json, text/event-stream", "Content-Type": "application/json"}
    client = httpx.Client(timeout=300.0)
    resp = client.post(ENDPOINT, json={"jsonrpc": "2.0", "id": 1, "method": "initialize", "params": {"protocolVersion": "2024-11-05", "capabilities": {}, "clientInfo": {"name": "cli", "version": "1"}}}, headers=headers)
    sid = resp.headers.get("mcp-session-id") or resp.json().get("sessionId")
    headers["mcp-session-id"] = sid
    client.post(f"{ENDPOINT}?sessionId={sid}", json={"jsonrpc": "2.0", "method": "notifications/initialized"}, headers=headers)
    return client, sid, headers

def call_tool_multiple(client, sid, headers, name, args):
    msg_url = f"{ENDPOINT}?sessionId={sid}"
    res = client.post(msg_url, json={"jsonrpc": "2.0", "id": 2, "method": "tools/call", "params": {"name": name, "arguments": args}}, headers=headers)
    results = []
    
    event_type = None
    data_lines = []
    
    for raw_line in res.iter_lines():
        line = raw_line.strip()
        if line.startswith("event:"):
            event_type = line[len("event:"):].strip()
        elif line.startswith("data:"):
            data_lines.append(line[len("data:"):].strip())
        elif line == "" and event_type:
            data = "\n".join(data_lines)
            if event_type == "message":
                try:
                    parsed = json.loads(data)
                    if "result" in parsed and "content" in parsed["result"]:
                        for content in parsed["result"]["content"]:
                            results.append(json.loads(content["text"]))
                except Exception as e:
                    pass
            event_type = None
            data_lines = []
            
    if not results and res.text:
        for line in res.text.split("\n"):
            if line.startswith("data: "):
                try:
                    data = json.loads(line[6:])
                    if "result" in data and "content" in data["result"]:
                        for content in data["result"]["content"]:
                            results.append(json.loads(content["text"]))
                except:
                    pass
                    
    return results

def worker(funcs, t_id):
    print(f"Thread {t_id} starting with {len(funcs)} functions...", flush=True)
    client, sid, headers = create_client()
    count = 0
    for func in funcs:
        addr = func.get("address")
        name = func.get("name")
        filename = f"decomp_dump/{name}_{addr}.c"
        if os.path.exists(filename): 
            count += 1
            continue
        
        try:
            decomp_res = call_tool_multiple(client, sid, headers, "get-decompilation", {"programPath": PROGRAM, "functionNameOrAddress": addr, "limit": 99999})
            if decomp_res:
                code = decomp_res[0].get("decompilation", "")
                with open(filename, "w") as f:
                    f.write(code)
            count += 1
            if count % 10 == 0:
                print(f"[{t_id}] Progress: {count}/{len(funcs)}", flush=True)
        except Exception as e:
            pass
            
    client.close()

def main():
    os.makedirs("decomp_dump", exist_ok=True)
    client, sid, headers = create_client()
    
    print("Fetching total count...", flush=True)
    res = call_tool_multiple(client, sid, headers, "get-function-count", {"programPath": PROGRAM, "filterDefaultNames": False})
    total = res[0].get("count", 0) if res else 5709
    print(f"Total: {total}", flush=True)
    
    all_funcs = []
    batch_size = 500
    for start in range(0, total, batch_size):
        print(f"Fetching manifest {start} to {min(start+batch_size, total)}...", flush=True)
        funcs_res = call_tool_multiple(client, sid, headers, "get-functions", {"programPath": PROGRAM, "filterDefaultNames": False, "maxCount": batch_size, "startIndex": start, "verbose": False})
        if funcs_res and len(funcs_res) > 1:
            all_funcs.extend(funcs_res[1:])
        time.sleep(0.5)
            
    client.close()
    print(f"Total functions identified: {len(all_funcs)}", flush=True)
    
    if len(all_funcs) == 0: return
        
    num_threads = 8
    chunks = [all_funcs[i::num_threads] for i in range(num_threads)]
    threads = []
    for i, chunk in enumerate(chunks):
        t = threading.Thread(target=worker, args=(chunk,i))
        t.start()
        threads.append(t)
        
    for t in threads: t.join()
    print("All decompilation complete!", flush=True)

if __name__ == "__main__":
    main()

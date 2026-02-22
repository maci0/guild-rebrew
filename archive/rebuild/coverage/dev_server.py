#!/usr/bin/env python3

import http.server
import json
import subprocess
from pathlib import Path
from urllib.parse import urlparse


def repo_root() -> Path:
    return Path(__file__).resolve().parents[2]


class Handler(http.server.SimpleHTTPRequestHandler):
    def do_POST(self):
        if urlparse(self.path).path == "/rebuild/coverage/regen":
            root = repo_root()
            try:
                subprocess.check_call(
                    ["python3", "rebuild/coverage/gen_coverage_data.py"], cwd=str(root)
                )
                body = json.dumps({"ok": True}).encode("utf-8")
                self.send_response(200)
                self.send_header("Content-Type", "application/json")
                self.send_header("Content-Length", str(len(body)))
                self.end_headers()
                self.wfile.write(body)
            except subprocess.CalledProcessError as e:
                body = json.dumps({"ok": False, "code": e.returncode}).encode("utf-8")
                self.send_response(500)
                self.send_header("Content-Type", "application/json")
                self.send_header("Content-Length", str(len(body)))
                self.end_headers()
                self.wfile.write(body)
            return

        self.send_response(404)
        self.end_headers()


def main() -> int:
    root = repo_root()
    server = http.server.ThreadingHTTPServer(
        ("127.0.0.1", 8000),
        lambda *args, **kwargs: Handler(*args, directory=str(root), **kwargs),
    )
    server.serve_forever()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

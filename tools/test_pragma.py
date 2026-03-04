import re
import subprocess
import os

target_file = "src/server.dll/func_10001a60.c"

with open(target_file, "r") as f:
    orig_code = f.read()

# insert pragma
pragma = """
#pragma optimize("s", on)
#pragma optimize("y", off)
"""

if "#pragma" not in orig_code:
    code = orig_code.replace("int func_10001a60", pragma + "\nint func_10001a60")
    with open(target_file, "w") as f:
        f.write(code)

cmd = "uv run --project /home/maci/Desktop/refactor/rebrew rebrew-match src/server.dll/func_10001a60.c --symbol _func_10001a60 --diff-only > diff_pragma.txt 2>&1 && head -n 35 diff_pragma.txt"
subprocess.run(cmd, shell=True)


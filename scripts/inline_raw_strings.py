"""Replace raw English string addresses by the string literals they stand for.

usage: uv run python scripts/inline_raw_strings.py <source>... [--apply]

Some recovered C passes a string as a raw address, e.g. `m_alloc(n, (const char*) 0x677750)`.
That compiles to an absolute operand without relocation, so it reproduces only the English
image and keeps every other target (the German twin) from matching. VC6 without /GF emits
each string literal into .data, so `push offset literal` with a relocation is the same
instruction the original produced.

A `(char *)`, `(const char *)` or `(void *)` cast of an address is rewritten only when
- the address lies in the English TL .data/.rdata and holds a NUL-terminated text string, and
- no other site in src/ names that address (a shared or written buffer stays a global).
Bytes >= 0x80 and control characters are written as three-digit octal escapes.
Verify the result with `rebrew test` on every affected target and audit literal contents
with `rebrew data audit-literals`.
"""

import re
import subprocess
import sys
from pathlib import Path

import lief

ROOT = Path(__file__).resolve().parent.parent
REFERENCE = ROOT / "original/Europa1400Gold_TL.exe"
CAST = re.compile(r"\(\s*(?:const\s+)?(?:char|void)\s*\*\s*\)\s*0x([0-9a-fA-F]{6,8})\b")


def string_reader():
    pe = lief.parse(str(REFERENCE))
    base = pe.optional_header.imagebase
    sections = [(base + s.virtual_address, bytes(s.content)) for s in pe.sections if s.name in (".data", ".rdata")]

    def read(va):
        for start, data in sections:
            if start <= va < start + len(data):
                off = va - start
                end = data.find(b"\0", off)
                if end <= off:
                    return None
                text = data[off:end]
                if all(32 <= c < 127 or c in (9, 10, 13) or c >= 0xA0 for c in text):
                    return text
        return None

    return read


def c_literal(text: bytes) -> str:
    out = []
    for c in text:
        ch = chr(c)
        if ch == "\\":
            out.append("\\\\")
        elif ch == '"':
            out.append('\\"')
        elif ch == "\n":
            out.append("\\n")
        elif ch == "\t":
            out.append("\\t")
        elif ch == "\r":
            out.append("\\r")
        elif 32 <= c < 127:
            out.append(ch)
        else:
            out.append("\\%03o" % c)
    return '"' + "".join(out) + '"'


def tree_sites(va: int) -> int:
    pattern = r"0x0*%x\b" % va
    r = subprocess.run(["git", "-C", str(ROOT), "grep", "-ciE", pattern, "--", "src"], capture_output=True, text=True)
    return sum(int(line.rsplit(":", 1)[1]) for line in r.stdout.splitlines() if line)


def main() -> int:
    apply = "--apply" in sys.argv
    files = [Path(a) for a in sys.argv[1:] if not a.startswith("--")]
    read = string_reader()
    rewritten = kept = 0
    for path in files:
        text = path.read_text(encoding="latin-1")

        def repl(m):
            nonlocal rewritten, kept
            va = int(m.group(1), 16)
            s = read(va)
            if s is None or tree_sites(va) != 1:
                kept += 1
                return m.group(0)
            rewritten += 1
            return c_literal(s)

        out = CAST.sub(repl, text)
        if apply and out != text:
            path.write_text(out, encoding="latin-1", newline="")
    print(f"{len(files)} files: {rewritten} sites rewritten, {kept} kept" + ("" if apply else " (dry run)"))
    return 0


if __name__ == "__main__":
    sys.exit(main())

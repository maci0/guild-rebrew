"""Byte-check the vendored-TU functions that `rebrew verify` skips.

The zlib TUs are annotated LIBRARY, so verify never compiles or compares them
and ~22 KB of the reference's `.text` goes unmeasured.  This walks the objects
the build already produced, matches each function symbol to its catalog entry
by normalized name, and diffs it against the target bytes with the same
instruction-sequence alignment scripts/seqdiff.py uses.

usage: zlibcheck.py [object-dir]
"""

import re
import subprocess
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "rebrew-project.toml").exists())
sys.path.insert(0, str(ROOT / "scripts"))

import seqdiff  # noqa: E402

DEFAULT_DIR = "build-sp6/CMakeFiles/server_dll.dir/references/zlib-1.1.3"
SYMBOL = re.compile(r"<(_?[A-Za-z][A-Za-z0-9_]*)>:\s*$")


def norm(name: str) -> str:
    return re.sub(r"^_+", "", name).lower()


def object_symbols(objdir: Path) -> dict[str, tuple[Path, str]]:
    """normalized name -> (object, symbol as objdump prints it)."""
    out: dict[str, tuple[Path, str]] = {}
    for obj in sorted(objdir.glob("*.obj")):
        txt = subprocess.run(["objdump", "-d", str(obj)], capture_output=True, text=True).stdout
        for line in txt.splitlines():
            if m := SYMBOL.search(line):
                out.setdefault(norm(m.group(1)), (obj, m.group(1)))
    return out


def catalog() -> dict[str, tuple[int, int]]:
    """normalized name -> (VA, size) for every LIBRARY entry."""
    out: dict[str, tuple[int, int]] = {}
    for line in (ROOT / "db/server.dll_functions.csv").read_text().splitlines():
        if not line or line.startswith(("#", "address")):
            continue
        addr, name, _sym, typ, size = line.split("|")
        if typ == "library":
            out.setdefault(norm(name), (int(addr, 16), int(size)))
    return out


def main() -> None:
    objdir = ROOT / (sys.argv[1] if len(sys.argv) > 1 else DEFAULT_DIR)
    syms, cat = object_symbols(objdir), catalog()
    target = ROOT / ".scratch" / "zlt.bin"

    checked = exact = 0
    differing = []
    for name, (va, size) in sorted(cat.items(), key=lambda kv: kv[1][0]):
        hit = syms.get(name)
        if hit is None:
            continue
        obj, raw = hit
        checked += 1
        seqdiff.extract(va, size, target)
        a, b = seqdiff.target_seq(target), seqdiff.cand_seq(obj, raw)
        import difflib

        same = sum(bl.size for bl in difflib.SequenceMatcher(None, a, b, autojunk=False).get_matching_blocks())
        if same == len(a) == len(b):
            exact += 1
        else:
            differing.append((va, name, same, len(a), len(b)))

    print(f"{objdir.name}: checked {checked} library functions, {exact} exact, {len(differing)} differing")
    for va, name, same, ta, tb in differing[:30]:
        print(f"  {va:#010x} {name:24s} aligned {same:5d} of target {ta:5d} / cand {tb:5d}")


if __name__ == "__main__":
    main()

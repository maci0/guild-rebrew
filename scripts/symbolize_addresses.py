"""Replace absolute data addresses in a game TU with the named global, where the reference relocates the operand.

The reference's base relocations mark every operand that the original code wrote as a symbol. Where our
source spells that operand as a bare address (`*(int*) 0x10034618`), the instruction bytes match but the
image has no relocation. For each such site in *FILE*'s functions whose target is the start of a named
reference data row that the current link also defines under that name, this rewrites `0xVA` to `&NAME` inside its cast. `--declare NAME` appends
`extern char NAME[];` to the TU's first extern line (keeping line numbers) for a name the TU does not declare (the compiler reports which). `--skip FUNC` leaves a
function's body alone: in a few functions the symbol changes register allocation, so run `rebrew test FILE`
afterwards and skip the functions it reports.

Usage: uv run scripts/symbolize_addresses.py FILE [--declare NAME]... [--skip FUNC]... [--dry-run]
Needs build/server.dll and build/server.map from a current build.
"""

import argparse
import re
import tomllib
from pathlib import Path

import pefile


def project_root() -> Path:
    here = Path(__file__).resolve()
    for parent in here.parents:
        if (parent / "rebrew-project.toml").exists():
            return parent
    raise SystemExit("rebrew-project.toml not found above " + str(here))


def missing_targets(root: Path, obj: str) -> dict[int, str]:
    """Target VA -> data row name for relocated operands the build lacks inside *obj*'s functions."""
    ref = pefile.PE(str(root / "original/Server/server.dll"))
    got = pefile.PE(str(root / "build/server.dll"))
    base = ref.OPTIONAL_HEADER.ImageBase
    ref_sites = {e.rva for b in ref.DIRECTORY_ENTRY_BASERELOC for e in b.entries if e.type == 3}
    got_sites = {e.rva for b in got.DIRECTORY_ENTRY_BASERELOC for e in b.entries if e.type == 3}
    funcs = []
    defined: set[str] = set()
    for line in (root / "build/server.map").read_text(errors="replace").splitlines():
        m = re.match(r"^ 0001:[0-9a-f]+\s+\S+\s+([0-9a-f]{8}) f\s+(\S+)", line)
        if m:
            funcs.append((int(m[1], 16), m[2]))
        d = re.match(r"^ 000[23]:[0-9a-f]+\s+_(\w+)\s+[0-9a-f]{8}", line)
        if d:
            defined.add(d[1])
    funcs.sort()
    rows = tomllib.loads((root / "rebrew-data.toml").read_text())
    names = {int(k[-8:], 16): r["name"] for k, r in rows.items() if k.startswith("SERVER.0x") and isinstance(r, dict) and r.get("name")}
    text = next(s for s in ref.sections if s.Name.startswith(b".text"))
    found: dict[int, str] = {}
    for rva in ref_sites - got_sites:
        if not text.VirtualAddress <= rva < text.VirtualAddress + text.Misc_VirtualSize:
            continue
        owner = max((f for f in funcs if f[0] <= base + rva), default=None)
        if owner is None or owner[1] != obj:
            continue
        value = int.from_bytes(ref.get_data(rva, 4), "little")
        name = names.get(value)
        if name in defined and not name.startswith("g_gap_"):
            found[value] = name
    return found


def body_span(text: str, func: str) -> tuple[int, int]:
    """Character span of *func*'s definition body (from its name to the matching closing brace)."""
    m = re.search(rf"\b{re.escape(func.lstrip('_'))}\s*\([^;{{()]*\)\s*\{{", text)
    if m is None:
        raise SystemExit(f"no definition of {func}")
    depth, i = 0, m.end() - 1
    while i < len(text):
        depth += {"{": 1, "}": -1}.get(text[i], 0)
        if depth == 0:
            return m.start(), i
        i += 1
    raise SystemExit(f"unbalanced braces in {func}")


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("file")
    parser.add_argument("--declare", action="append", default=[])
    parser.add_argument("--skip", action="append", default=[])
    parser.add_argument("--dry-run", action="store_true")
    args = parser.parse_args()
    root = project_root()
    path = root / args.file
    targets = missing_targets(root, path.name + ".obj")
    text = path.read_text()
    changed = 0
    for va, name in sorted(targets.items()):
        skipped = [body_span(text, func) for func in args.skip]
        pattern = re.compile(rf"(\([^()]*\*\s*\)\s*)0x0*{va:x}\b", re.I)

        def rewrite(m: re.Match[str], name: str = name) -> str:
            if any(lo <= m.start() < hi for lo, hi in skipped):
                return m[0]
            return f"{m[1]}&{name}"

        new = pattern.sub(rewrite, text)
        n = sum(1 for _ in re.finditer(rf"&{name}\b", new)) - sum(1 for _ in re.finditer(rf"&{name}\b", text))
        text = new
        changed += n
        print(f"0x{va:08x} {name}: {n}")
    if args.declare:
        # Append to an existing extern line: a new line shifts line numbers, which changes codegen in some TUs.
        anchor = re.search(r"^extern [^\n]*;$", text, re.M)
        if anchor is None:
            raise SystemExit(f"no top-level extern line in {args.file} to append declarations to")
        decls = "".join(f" extern char {name}[];" for name in args.declare)
        text = text[: anchor.end()] + decls + text[anchor.end() :]
    if not args.dry_run:
        path.write_text(text)
    print(f"{changed} operands in {path.relative_to(root)}")


if __name__ == "__main__":
    main()

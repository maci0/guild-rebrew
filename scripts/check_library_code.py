#!/usr/bin/env python3
"""Flag reversed functions whose bytes are already supplied by a linked library.

Reversing a function that the linker will provide anyway is wasted work: the
result is committed as game code, shows up in coverage, and can be "improved"
for weeks before anyone notices it was never ours. This happened to the whole
crt_region tree: all 68 annotated functions there are byte-identical to stock
LIBCMT.

Detection is byte-level, not name-level. For each annotated VA in the target
binary, every COFF section body in every library that defines a symbol at that
offset is compared against the binary. Relocation slots are zero-filled in a
.LIB, so a match means "identical outside the object's own .reloc entries",
which is exactly what linked-in library code looks like.

Two details that a name-based or naive scan gets wrong, both learned the hard
way:

  * MSVC marks CRT helpers such as _initterm and _parse_cmdline static (COFF
    storage class 3). They never appear in the archive symbol index, so a scan
    that walks only external symbols reports them as absent from the library.
    Storage class 3 is included here.

  * A body that is mostly relocation slots (a pointer table such as
    __sys_errlist) trivially "matches" anything once its slots are masked.
    Candidates must be at least half fixed bytes.

Exit status: 0 when no unexpected library code is found, 1 otherwise, so this
works as a pre-commit hook or CI gate.
"""

from __future__ import annotations

import argparse
import re
import struct
import sys
import tomllib
from pathlib import Path

try:
    import pefile
except ImportError:
    sys.exit("check_library_code: pefile is required (uv pip install pefile)")

MIN_BYTES = 8
MIN_FIXED_FRACTION = 0.5
PREFIX_BYTES = 32


def find_root(start: Path) -> Path:
    for cand in [start, *start.parents]:
        if (cand / "rebrew-project.toml").exists():
            return cand
    sys.exit("check_library_code: project root (rebrew-project.toml) not found")


ROOT = find_root(Path(__file__).resolve())


def ar_members(data: bytes) -> list[tuple[str, bytes]]:
    if data[:8] != b"!<arch>\n":
        return []
    pos, out = 8, []
    while pos + 60 <= len(data):
        header = data[pos : pos + 60]
        if len(header) < 60:
            break
        name = header[0:16].decode("ascii", "replace").strip()
        try:
            size = int(header[48:58].decode().strip())
        except ValueError:
            break
        out.append((name, data[pos + 60 : pos + 60 + size]))
        pos += 60 + size + (size & 1)
    return out


def make_name_resolver(members: list[tuple[str, bytes]]):
    longnames = next((body for name, body in members if name.startswith("//")), None)

    def resolve(name: str) -> str:
        if name.startswith("/") and name[1:].isdigit() and longnames is not None:
            off = int(name[1:])
            return longnames[off : longnames.find(b"\0", off)].decode()
        return name.rstrip("/")

    return resolve


def coff_sections(obj: bytes) -> list[dict]:
    count = struct.unpack_from("<H", obj, 2)[0]
    sections = []
    for i in range(count):
        off = 20 + i * 40
        name = obj[off : off + 8].rstrip(b"\0").decode("ascii", "replace")
        raw_size, raw_ptr = struct.unpack_from("<II", obj, off + 16)
        reloc_ptr = struct.unpack_from("<I", obj, off + 24)[0]
        reloc_count = struct.unpack_from("<H", obj, off + 32)[0]
        sections.append(
            {
                "name": name,
                "raw_ptr": raw_ptr,
                "raw_size": raw_size,
                "reloc_ptr": reloc_ptr,
                "reloc_count": reloc_count,
            }
        )
    return sections


def coff_symbols(obj: bytes) -> list[tuple[str, int, int, int]]:
    ptr, count = struct.unpack_from("<II", obj, 8)
    if ptr == 0 or count == 0 or ptr + count * 18 > len(obj):
        return []
    strtab = ptr + count * 18
    out, i = [], 0
    while i < count:
        entry = obj[ptr + i * 18 : ptr + i * 18 + 18]
        raw = entry[0:8]
        if raw[0:4] == b"\0\0\0\0":
            off = struct.unpack_from("<I", raw, 4)[0]
            end = obj.find(b"\0", strtab + off)
            name = obj[strtab + off : end].decode("ascii", "replace")
        else:
            name = raw.rstrip(b"\0").decode("ascii", "replace")
        value = struct.unpack_from("<I", entry, 8)[0]
        section = struct.unpack_from("<h", entry, 12)[0]
        storage_class = entry[16]
        out.append((name, value, section, storage_class))
        i += 1 + entry[17]
    return out


def reloc_mask(obj: bytes, section: dict) -> set[int]:
    """Section-relative byte offsets covered by a relocation field."""
    mask: set[int] = set()
    for i in range(section["reloc_count"]):
        off = section["reloc_ptr"] + i * 10
        if off + 10 > len(obj):
            break
        addr = struct.unpack_from("<I", obj, off)[0]
        mask.update(range(addr, addr + 4))
    return mask


def index_library(path: Path) -> dict[str, list[tuple[str, bytes, dict, int]]]:
    members = ar_members(path.read_bytes())
    resolve = make_name_resolver(members)
    index: dict[str, list[tuple[str, bytes, dict, int]]] = {}
    for raw_name, obj in members:
        name = resolve(raw_name)
        if not name.endswith(".obj") or len(obj) < 20:
            continue
        try:
            sections = coff_sections(obj)
            symbols = coff_symbols(obj)
        except (struct.error, IndexError):
            continue
        for sym, value, section, storage_class in symbols:
            # class 2 = external, class 3 = static. Static CRT helpers are
            # absent from the archive symbol index but still linked in.
            if section > 0 and storage_class in (2, 3) and section <= len(sections):
                # Section symbols (.text/.rdata) alias real function symbols at
                # the same offset; keep the function name for the report.
                if sym.startswith("."):
                    continue
                index.setdefault(sym, []).append(
                    (name, obj, sections[section - 1], value)
                )
    return index


def match_at(index, data: bytes) -> tuple[str, str] | None:
    """Return (symbol, object) when data is a library body, else None."""
    if len(data) < MIN_BYTES:
        return None
    for sym, entries in index.items():
        for obj_name, obj, section, value in entries:
            body = obj[section["raw_ptr"] + value : section["raw_ptr"] + section["raw_size"]]
            if len(body) < len(data):
                continue
            candidate = body[: len(data)]
            mask = {
                x - value
                for x in reloc_mask(obj, section)
                if value <= x < value + len(data)
            }
            if len(data) - len(mask) < MIN_FIXED_FRACTION * len(data):
                continue
            diff = {i for i in range(len(data)) if candidate[i] != data[i]}
            if diff <= mask:
                return sym, obj_name.split("\\")[-1]
    return None


def collect_annotations(src_root: Path) -> list[tuple[Path, int]]:
    out = []
    for path in sorted(src_root.rglob("*.c")):
        text = path.read_text(errors="replace")
        for m in re.finditer(r"^// FUNCTION: \w+ (0x[0-9a-fA-F]+)", text, re.M):
            out.append((path, int(m.group(1), 16)))
    return out


DEFAULT_LIB_IMAGE = "rebrew/msvc:6.0-sp6-win32"
DEFAULT_LIB_PATH = "/opt/msvc6.0/VC98/Lib/LIBCMT.LIB"


def extract_reference_lib(dest: Path) -> None:
    """Copy the stock CRT out of the toolchain image, so the check needs no
    committed binary and no manual setup."""
    import shutil
    import subprocess

    if shutil.which("docker") is None:
        return
    dest.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        [
            "docker", "run", "--rm", "--entrypoint", "sh",
            "-v", f"{dest.parent}:/out", DEFAULT_LIB_IMAGE,
            "-c", f"cp {DEFAULT_LIB_PATH} /out/{dest.name}",
        ],
        capture_output=True,
        timeout=120,
        check=False,
    )


def assert_library_is_stock(path: Path) -> None:
    """Refuse to run against a hand-modified library.

    The build once linked a LIBCMT with 22 objects stripped out, kept in
    gitignored scratch, so a fresh clone could not reproduce it. Checking a
    reversed function against a doctored library would also mask exactly the
    duplication this script exists to find.
    """
    import shutil
    import subprocess

    if shutil.which("docker") is None:
        return
    proc = subprocess.run(
        [
            "docker", "run", "--rm", "--entrypoint", "sh",
            "-v", f"{path.parent}:/out", DEFAULT_LIB_IMAGE,
            "-c", f"md5sum {DEFAULT_LIB_PATH} /out/{path.name}",
        ],
        capture_output=True,
        text=True,
        timeout=120,
        check=False,
    )
    sums = [ln.split()[0] for ln in proc.stdout.splitlines() if ln.strip()]
    if len(sums) == 2 and sums[0] != sums[1]:
        sys.exit(
            f"check_library_code: {path} differs from the toolchain's stock "
            f"{DEFAULT_LIB_PATH}.\n"
            "Libraries must not be patched. Delete it and re-run to re-extract."
        )


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--binary", default="original/Server/server.dll")
    ap.add_argument("--src", default="src/server.dll")
    ap.add_argument(
        "--lib",
        action="append",
        default=[],
        help="library to check against (repeatable). Default: .scratch/libcmt_stock.LIB",
    )
    ap.add_argument(
        "--allow",
        default="scripts/library_code_allowlist.txt",
        help="file of VAs known to be library code and deliberately kept",
    )
    ap.add_argument(
        "--va",
        help="check a single VA (hex) instead of every annotation. Use this "
        "before starting work on a function.",
    )
    ap.add_argument("--json", action="store_true")
    args = ap.parse_args()

    libs = [Path(p) for p in (args.lib or [ROOT / ".scratch/libcmt_stock.LIB"])]
    libs = [p if p.is_absolute() else ROOT / p for p in libs]
    for lib in libs:
        if not lib.exists():
            extract_reference_lib(lib)
        elif lib == ROOT / ".scratch/libcmt_stock.LIB":
            assert_library_is_stock(lib)
    missing = [p for p in libs if not p.exists()]
    if missing:
        print(
            "check_library_code: skipped, reference library unavailable: "
            + ", ".join(str(p) for p in missing),
            file=sys.stderr,
        )
        return 0

    index: dict = {}
    for lib in libs:
        for sym, entries in index_library(lib).items():
            index.setdefault(sym, []).extend(entries)

    allow_path = ROOT / args.allow
    allowed = set()
    if allow_path.exists():
        for line in allow_path.read_text().splitlines():
            line = line.split("#", 1)[0].strip()
            if line:
                allowed.add(int(line, 16))

    meta_path = ROOT / "src/rebrew-functions.toml"
    sizes: dict[int, int] = {}
    if meta_path.exists():
        for key, value in tomllib.load(meta_path.open("rb")).items():
            try:
                va = int(key.split(".")[-1], 16)
            except ValueError:
                continue
            if value.get("size"):
                sizes[va] = value["size"]

    pe = pefile.PE(str(ROOT / args.binary))
    base = pe.OPTIONAL_HEADER.ImageBase

    if args.va:
        va = int(args.va, 16)
        size = sizes.get(va)
        try:
            data = pe.get_data(va - base, size or PREFIX_BYTES)
        except Exception:
            print(f"check_library_code: 0x{va:08x} is not in the image")
            return 2
        hit = match_at(index, data) or match_at(
            index, pe.get_data(va - base, PREFIX_BYTES)
        )
        if hit:
            print(f"0x{va:08x} is library code: {hit[0]} in {hit[1]}")
            print("Do not reverse it; the linker supplies these bytes.")
            return 1
        print(f"0x{va:08x} is not in the checked libraries. Safe to reverse.")
        return 0

    findings = []
    for path, va in collect_annotations(ROOT / args.src):
        if va in allowed:
            continue
        size = sizes.get(va)
        try:
            data = pe.get_data(va - base, size or PREFIX_BYTES)
        except Exception:
            continue
        hit = match_at(index, data)
        if hit is None and size:
            # A wrong size in the metadata overruns the function and hides a
            # real match; retry on a prefix.
            try:
                hit = match_at(index, pe.get_data(va - base, PREFIX_BYTES))
            except Exception:
                hit = None
        if hit:
            findings.append(
                {
                    "va": f"0x{va:08x}",
                    "file": str(path.relative_to(ROOT)),
                    "symbol": hit[0],
                    "object": hit[1],
                }
            )

    if args.json:
        import json

        print(json.dumps({"findings": findings}, indent=1))
    elif findings:
        print("Reversed functions whose bytes come from a linked library:\n")
        for f in findings:
            print(f"  {f['va']}  {f['file']}")
            print(f"              {f['symbol']} in {f['object']}")
        print(
            f"\n{len(findings)} function(s). These do not need reversing: the linker\n"
            "supplies them. Delete the source, or add the VA to\n"
            f"{args.allow} with a reason if the file must stay for link reasons."
        )
    else:
        print("No library code found among reversed functions.")

    return 1 if findings else 0


if __name__ == "__main__":
    sys.exit(main())

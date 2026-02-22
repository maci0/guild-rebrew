#!/usr/bin/env python3

import json
import math
import re
import hashlib
import subprocess
import tempfile
from dataclasses import dataclass
from pathlib import Path
from typing import Dict, List, Optional, Tuple


IMAGE_BASE = 0x10000000
TEXT_FILE_OFF = 0x1000


@dataclass
class Fn:
    name: str
    va_start: int
    va_end: int
    size: int
    description: str
    doc_rel: str
    file_offset: int
    text_offset: int
    asm_rel: Optional[str]
    c_rel: Optional[str]


def is_db_heavy_asm(path: Path) -> bool:
    try:
        txt = path.read_text(encoding="utf-8", errors="ignore")
    except OSError:
        return False

    lines: List[str] = []
    for raw in txt.splitlines():
        ln = raw.strip()
        if not ln:
            continue
        if ln.startswith(";"):
            continue
        lines.append(ln)

    if len(lines) < 10:
        return False

    db_lines = sum(1 for ln in lines if ln.startswith("db "))
    return (db_lines / len(lines)) >= 0.50


def disasm_pretty(va_start: int, code: bytes) -> str:
    with tempfile.NamedTemporaryFile(delete=False) as f:
        f.write(code)
        tmp_name = f.name

    try:
        res = subprocess.run(
            ["ndisasm", "-b", "32", "-o", hex(va_start), tmp_name],
            check=True,
            stdout=subprocess.PIPE,
            stderr=subprocess.PIPE,
            text=True,
        )
        return res.stdout
    finally:
        try:
            Path(tmp_name).unlink(missing_ok=True)
        except Exception:
            pass


def parse_hex(s: str) -> int:
    s = s.strip()
    if s.lower().startswith("0x"):
        return int(s, 16)
    return int(s)


def find_repo_root(this_file: Path) -> Path:
    return this_file.resolve().parents[2]


def parse_function_list(md: str) -> List[Tuple[str, int, int, int, str, str]]:
    rows: List[Tuple[str, int, int, int, str, str]] = []
    in_table = False

    for raw in md.splitlines():
        line = raw.strip()
        if line.startswith("| Function | Start Address"):
            in_table = True
            continue
        if not in_table:
            continue
        if not line.startswith("|"):
            continue
        if line.startswith("|----------"):
            continue

        parts = [p.strip() for p in line.strip("|").split("|")]
        if len(parts) < 7:
            continue

        name = parts[0]
        start = parse_hex(parts[1])
        end = parse_hex(parts[2])
        size_m = re.match(r"^(\d+)B$", parts[3])
        if not size_m:
            continue
        size = int(size_m.group(1))
        desc = parts[4]

        link_m = re.search(r"\(([^)]+)\)", parts[6])
        if not link_m:
            continue
        doc_rel = link_m.group(1)

        rows.append((name, start, end, size, desc, doc_rel))

    return rows


def guess_asm_path(name: str) -> Optional[str]:
    if name == "Init":
        return "rebuild/asm/_init.asm"
    if name == "Exit":
        return "rebuild/asm/_exit.asm"
    if name.startswith("fcn_"):
        return f"rebuild/asm/_{name}.asm"
    return None


def guess_c_path(name: str) -> Optional[str]:
    if name == "Init":
        return "rebuild/c/init.c"
    if name == "Exit":
        return "rebuild/c/exit.c"
    if name.startswith("fcn_"):
        return f"rebuild/c/{name}.c"
    return None


def raw_asm_url(root: Path, name: str) -> Optional[str]:
    rel = guess_asm_path(name)
    if not rel:
        return None
    p = root / rel
    if not p.exists():
        return None
    if not is_db_heavy_asm(p):
        return None
    return "/" + rel


def merge_ranges(ranges: List[Tuple[int, int]]) -> List[Tuple[int, int]]:
    if not ranges:
        return []
    ranges = sorted(ranges)
    out = [list(ranges[0])]
    for s, e in ranges[1:]:
        last = out[-1]
        if s <= last[1]:
            last[1] = max(last[1], e)
        else:
            out.append([s, e])
    return [(a, b) for a, b in out]


def main() -> int:
    root = find_repo_root(Path(__file__))
    function_list = (root / "rebuild/docs/FUNCTION_LIST.md").read_text(encoding="utf-8")
    text_size = int((root / "rebuild/sections/text_raw.bin").stat().st_size)
    dll_bytes = (root / "original/Server/server.dll").read_bytes()

    fns: Dict[str, Fn] = {}
    asm_pretty_dir = root / "rebuild/coverage/asm_pretty"
    asm_pretty_dir.mkdir(parents=True, exist_ok=True)

    for name, va_start, va_end, size, desc, doc_rel in parse_function_list(
        function_list
    ):
        file_off = va_start - IMAGE_BASE
        text_off = file_off - TEXT_FILE_OFF
        asm_rel = guess_asm_path(name)
        c_rel = guess_c_path(name)

        if asm_rel and not (root / asm_rel).exists():
            asm_rel = None
        if c_rel and not (root / c_rel).exists():
            c_rel = None

        raw_asm_rel = guess_asm_path(name)
        if (
            raw_asm_rel
            and (root / raw_asm_rel).exists()
            and is_db_heavy_asm(root / raw_asm_rel)
        ):
            pretty_rel = f"rebuild/coverage/asm_pretty/{name}.asm"
            pretty_path = root / pretty_rel
            code = dll_bytes[file_off : file_off + size]
            pretty = disasm_pretty(va_start, code)
            pretty_path.write_text(
                (
                    f"; pretty disassembly for {name}\n"
                    f"; VA: {hex(va_start)}..{hex(va_end)} ({size} bytes)\n" + pretty
                ),
                encoding="utf-8",
            )
            asm_rel = pretty_rel

        fns[name] = Fn(
            name=name,
            va_start=va_start,
            va_end=va_end,
            size=size,
            description=desc,
            doc_rel=f"/rebuild/docs/{doc_rel}",
            file_offset=file_off,
            text_offset=text_off,
            asm_rel=asm_rel,
            c_rel=c_rel,
        )

    ranges = []
    for fn in fns.values():
        s = max(0, fn.text_offset)
        e = min(text_size, fn.text_offset + fn.size)
        if s < e:
            ranges.append((s, e))
    merged = merge_ranges(ranges)
    covered_bytes = sum(e - s for s, e in merged)
    coverage_percent = (covered_bytes / text_size * 100.0) if text_size else 0.0

    c_rebuilt = [fn for fn in fns.values() if fn.c_rel is not None]

    unit_bytes = 128
    default_gap_bytes = 128
    columns = 64

    fn_by_start: Dict[int, Fn] = {fn.text_offset: fn for fn in fns.values()}
    fn_starts = sorted(fn_by_start.keys())

    segments: List[Tuple[int, int, str, List[str]]] = []
    off = 0
    idx = 0
    while off < text_size:
        while idx < len(fn_starts) and fn_starts[idx] < off:
            idx += 1

        if idx < len(fn_starts) and fn_starts[idx] == off:
            fn = fn_by_start[off]
            s = off
            e = min(text_size, off + fn.size)
            state = "c" if fn.c_rel is not None else "asm"
            segments.append((s, e, state, [fn.name]))
            off = e
            continue

        next_fn_off = fn_starts[idx] if idx < len(fn_starts) else text_size
        gap_end = min(text_size, off + default_gap_bytes, next_fn_off)
        segments.append((off, gap_end, "none", []))
        off = gap_end

    cells = []
    col = 0
    for seg_start, seg_end, state, seg_fns in segments:
        remaining = seg_end - seg_start
        seg_cols = int(math.ceil(remaining / unit_bytes))
        cur = seg_start
        cols_left = seg_cols

        while cols_left > 0:
            take_cols = min(cols_left, columns - col)
            take_bytes = min(seg_end - cur, take_cols * unit_bytes)
            span = int(math.ceil(take_bytes / unit_bytes))
            cell_end = cur + take_bytes
            cells.append(
                {
                    "start": cur,
                    "end": cell_end,
                    "span": span,
                    "state": state,
                    "functions": seg_fns,
                }
            )
            col = (col + span) % columns
            cols_left -= span
            cur = cell_end

    out = {
        "textSize": text_size,
        "unitBytes": unit_bytes,
        "defaultGapBytes": default_gap_bytes,
        "columns": columns,
        "summary": {
            "documentedFunctions": len(fns),
            "cRebuiltFunctions": len(c_rebuilt),
            "coveredBytes": covered_bytes,
            "coveragePercent": coverage_percent,
        },
        "paths": {
            "originalDll": "/original/Server/server.dll",
        },
        "functions": {
            fn.name: {
                "name": fn.name,
                "vaStart": hex(fn.va_start),
                "vaEnd": hex(fn.va_end),
                "size": fn.size,
                "description": fn.description,
                "fileOffset": fn.file_offset,
                "textOffset": fn.text_offset,
                "md5": hashlib.md5(
                    dll_bytes[fn.file_offset : fn.file_offset + fn.size]
                ).hexdigest(),
                "sha256": hashlib.sha256(
                    dll_bytes[fn.file_offset : fn.file_offset + fn.size]
                ).hexdigest(),
                "docPath": fn.doc_rel,
                "asmPath": ("/" + fn.asm_rel) if fn.asm_rel else None,
                "asmRawPath": raw_asm_url(root, fn.name),
                "cPath": ("/" + fn.c_rel) if fn.c_rel else None,
            }
            for fn in sorted(fns.values(), key=lambda f: f.va_start)
        },
        "cells": cells,
    }

    (root / "rebuild/coverage/data.json").write_text(
        json.dumps(out, indent=2) + "\n", encoding="utf-8"
    )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())

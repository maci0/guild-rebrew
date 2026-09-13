#!/usr/bin/env python3
"""Hill-climb a function's statement order against the reference bytes.

The notes on the remaining non-matching functions all say the same thing: the
residue is statement order and the register allocation that follows from it, and
the wins came from moving one statement a few lines (gm_AllocSpieler 734 -> 858
on exactly that move class, "relocating single statements by one to three lines
moves the score by tens of bytes").  Those climbs were done by hand, one compile
per guess.  `scripts/probe_function.py` makes one guess cost about 1.5s, so the
same search can run unattended.

This splits the function body into top-level statements and repeatedly applies
the best single move until no move improves the masked byte match.  Moves are
relocations by up to `--reach` positions, with declarations kept inside the
declaration region (C89) and statements kept out of it.

The objective is the reference's bytes, so the search cannot "cheat": a move is
kept only when it makes the compiled function more identical to the target, and
the source is rewritten in place only on an improvement.

Usage:
    python3 scripts/hillclimb.py --va 0x10015f70 \\
        --file src/server.dll/DieGildeAddOn/game/spiel_c/gm_ObjectsAvailble.c
    python3 scripts/hillclimb.py --va 0x10015f70 --file ... --rounds 3 --jobs 6
    python3 scripts/hillclimb.py --va 0x10015f70 --file ... --dry-run   # list

`--dry-run` prints the statements it found and exits: the cheap way to check the
splitter on a new function before spending compiles on it.
"""

from __future__ import annotations

import argparse
import concurrent.futures as cf
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
PROBE = ROOT / "scripts/probe_function.py"
PYTHON = sys.executable

DECL_NAME = re.compile(r"[A-Za-z_]\w*(?:\[[^\]]*\])*$")
# A label is a jump target: moving it moves what a `goto` reaches, and
# moving a statement across it changes what falls into it.  (Measured:
# vfs_OpenStream's `cleanup:` block was lifted above `result = stream;`, so
# its four `goto cleanup` sites fell through into the wrong return -- and it
# scored 23 bytes better.)
LABEL = re.compile(r"^(?:case\b[^:]*|default|[A-Za-z_]\w*)\s*:")
KEYWORDS = {"return", "goto", "break", "continue", "if", "else", "while", "for",
            "do", "switch", "case", "default"}


def strip_literals(text: str) -> str:
    """Same length as `text`, with string/char/comment bodies blanked out."""
    out = list(text)
    i, n = 0, len(text)
    while i < n:
        c = text[i]
        if c in "\"'":
            q, i = c, i + 1
            while i < n:
                if text[i] == "\\":
                    out[i] = " "
                    i += 2
                    continue
                if text[i] == q:
                    break
                out[i] = " "
                i += 1
        elif c == "/" and i + 1 < n and text[i + 1] == "*":
            j = text.find("*/", i + 2)
            j = n if j < 0 else j + 2
            for k in range(i, j):
                out[k] = " "
            i = j
            continue
        elif c == "/" and i + 1 < n and text[i + 1] == "/":
            j = text.find("\n", i)
            j = n if j < 0 else j
            for k in range(i, j):
                out[k] = " "
            i = j
            continue
        i += 1
    return "".join(out)


def symbol_for(va: int) -> str | None:
    for line in (ROOT / "build/split_poc.map").read_text().splitlines():
        m = re.match(r"^\s*[0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8})\s+f\s", line)
        if m and int(m.group(2), 16) == va:
            return re.sub(r"^_|@\d+$", "", m.group(1))
    return None


def function_body(text: str, name: str) -> tuple[int, int]:
    """Range of the text between the function's outer braces.

    Searched in the comment/string-blanked copy (a doc comment mentioning the
    name is not the definition) and required to have `{` where a prototype has
    `;`.
    """
    s = strip_literals(text)
    for m in re.finditer(rf"\b{re.escape(name)}\s*\(", s):
        # skip the parameter list, then demand the opening brace
        j = m.end() - 1
        depth = 0
        while j < len(s):
            if s[j] == "(":
                depth += 1
            elif s[j] == ")":
                depth -= 1
                if depth == 0:
                    break
            j += 1
        k = j + 1
        while k < len(s) and s[k].isspace():
            k += 1
        if k >= len(s) or s[k] != "{":
            continue
        depth = 0
        for i in range(k, len(s)):
            if s[i] == "{":
                depth += 1
            elif s[i] == "}":
                depth -= 1
                if depth == 0:
                    return k + 1, i
    sys.exit(f"definition of {name} not found")


def statements(body: str) -> list[tuple[int, int]]:
    """Spans of the body's top-level statements; a braced block counts as one.

    Spans tile the body (`[0, len(body))`) rather than covering only the code:
    the whitespace and comments *before* a statement belong to it, so moving a
    statement carries its indentation and its explanatory comment along and a
    reordered body is a permutation of the original text.
    """
    s = strip_literals(body)
    spans: list[tuple[int, int]] = []
    i, n, prev = 0, len(s), 0
    while i < n:
        while i < n and s[i].isspace():
            i += 1
        if i >= n:
            break
        start, depth = prev, 0
        while i < n:
            c = s[i]
            if c == "{":
                depth += 1
            elif c == "}":
                depth -= 1
                if depth == 0:
                    i += 1
                    j = i
                    while j < n and s[j].isspace():
                        j += 1
                    if s.startswith(("while", "else"), j):
                        continue
                    break
            elif c == ";" and depth == 0:
                i += 1
                break
            i += 1
        spans.append((start, i))
        prev = i
    if spans:
        spans[-1] = (spans[-1][0], n)  # the tail whitespace rides the last one
    return spans


def is_decl(unit: str) -> bool:
    """A declaration is type-ish words and a name, with no call or assignment."""
    u = strip_literals(unit).strip().rstrip(";").strip()
    if any(c in u for c in "(=,:"):
        return False
    toks = u.replace("*", " ").split()
    if not toks or toks[0] in KEYWORDS:
        return False
    return all(DECL_NAME.fullmatch(t) for t in toks)


def target_size(va: str) -> int:
    """The reference function's size, from the same metadata probe reads."""
    text = (ROOT / "src/rebrew-functions.toml").read_text()
    m = re.search(rf'\["SERVER\.0x{int(va, 0):08x}"\]\n(?:.*\n)*?size\s*=\s*(\d+)', text)
    if not m:
        sys.exit("no metadata size for that VA")
    return int(m.group(1))


# What a statement writes (cast-stripped destination text, plus the base object
# it writes through) and what it reads.  A move is refused when the moved
# statement touches anything it crosses: reordering past a read or a write of
# the same object changes what the program does, and the climb only sees bytes.
# (Measured: without this, gm_AllocGebaeude lifted a `gm_SetupEntityQuery` block
# above the `gm_ff_Objekt` block that writes the same `geb+0x29` field, so
# whichever ran second won -- and it scored better.)
CAST = re.compile(r"\(\s*(?:\w+\s+)*\w+\s*\*+\s*\)")
IDENT = re.compile(r"[A-Za-z_]\w*")
# Names that are not object references: statement keywords plus type words.
# (A separate set from the statement KEYWORDS above, which `is_decl` uses --
# redefining that one silently stopped declarations being recognised.)
NOISE = {
    "if", "else", "while", "for", "do", "switch", "case", "default", "return",
    "goto", "break", "continue", "sizeof", "void", "char", "short", "int",
    "long", "float", "double", "unsigned", "signed", "const", "static",
    "volatile", "struct", "union", "enum", "NULL",
}
ASSIGN_OPS = ("<<=", ">>=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=")


def _lhs_of(line: str) -> str | None:
    """Text left of an assignment (or the whole line for ++/--), else None."""
    i = 0
    while True:
        i = line.find("=", i)
        if i < 0:
            return line if ("++" in line or "--" in line) else None
        nxt = line[i + 1] if i + 1 < len(line) else ""
        prv = line[i - 1] if i else ""
        if nxt == "=" or prv in "<>!":
            i += 1
            continue
        if any(line.endswith(op, 0, i) for op in ASSIGN_OPS):
            i += 1
            continue
        return line[:i]


def accesses(unit: str) -> tuple[set[str], set[str], set[str]]:
    """(destinations, base identifiers written through, identifiers read)."""
    code = strip_literals(unit)
    dests: set[str] = set()
    touched: set[str] = set()
    for line in code.splitlines():
        if "=" not in line and "++" not in line and "--" not in line:
            continue
        lhs = _lhs_of(line)
        if not lhs:
            continue
        flat = CAST.sub("", lhs)
        dests.add(re.sub(r"\s+", "", flat))
        touched |= {t for t in IDENT.findall(flat) if t not in NOISE}
    reads = {t for t in IDENT.findall(CAST.sub("", code)) if t not in NOISE}
    return dests, touched, reads


def conflicts(moved: str, other: str) -> bool:
    """Would reordering these two change what the program does?"""
    dm, bm, rm = accesses(moved)
    do, bo, ro = accesses(other)
    return bool(
        (dm & do)      # same destination
        or (bm & bo)   # writes through the same base object
        or (bm & ro)   # ... that the other reads
        or (bo & rm)   # the other writes something this one reads
    )


def score(path: Path, va: str) -> tuple[int, int, int, int]:
    """(size agrees with the target, matched, -insn delta, object size)."""
    r = subprocess.run([PYTHON, str(PROBE), "--va", va, "--file", str(path)],
                       capture_output=True, text=True, cwd=ROOT)
    m = re.search(r"size (\d+):.*matched (\d+)/(\d+).*instructions (\d+) vs (\d+)"
                  r".*object size (\d+)", r.stdout, re.S)
    if not m:
        # A candidate that does not compile must lose to every real score: the
        # size key is negative, so a plain -1 would outrank it.
        return -1 << 30, -1, -1, -1
    target, matched = int(m.group(1)), int(m.group(2))
    delta = -abs(int(m.group(4)) - int(m.group(5)))
    obj = int(m.group(6))
    # A function must never come out SHORTER than the reference's, and that is
    # the only size rule the composition imposes: it places each function at its
    # reference VA and trims an object that overruns (crt_region/dllmain.c links
    # a 203-byte object into the reference's 157-byte slot byte-perfectly), but
    # it cannot pad a gap.  Measured the hard way: a 13-byte-short
    # cm_ExSellObjekt took the linked image from 11,336 to 89,509 differing
    # bytes while its object-level score rose 387 -> 615, whereas the same climb
    # at +16 bytes was harmless.  Growth therefore ranks equal to an exact size;
    # only a shortfall loses.
    return (1 if obj >= target else 0), matched, delta, obj


def move(order: list[int], i: int, j: int) -> list[int]:
    """Take the unit at i and put it where the unit at j is now."""
    o = order[:]
    u = o.pop(i)
    o.insert(j if j < i else j - 1, u)
    return o


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--va", required=True)
    ap.add_argument("--file", required=True)
    ap.add_argument("--symbol", default=None)
    ap.add_argument("--rounds", type=int, default=10)
    ap.add_argument("--reach", type=int, default=3, help="max displacement")
    ap.add_argument("--jobs", type=int, default=4)
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()

    src = ROOT / args.file
    text = src.read_text()
    name = args.symbol or symbol_for(int(args.va, 0))
    if not name:
        sys.exit("pass --symbol (no map entry for that VA)")

    lo, hi = function_body(text, name)
    head, body, tail = text[:lo], text[lo:hi], text[hi:]
    spans = statements(body)
    units = [body[a:b] for a, b in spans]
    barrier = [bool(LABEL.match(strip_literals(u).strip())) for u in units]
    ndec = 0
    while ndec < len(units) and is_decl(units[ndec]):
        ndec += 1
    print(f"{name}: {len(units)} statements ({ndec} declarations), "
          f"{len(body)} body bytes")
    if args.dry_run:
        for k, u in enumerate(units):
            print(f"  [{k:3d}] {'decl' if k < ndec else '    '} "
                  f"{strip_literals(u).strip().splitlines()[0][:72]}")
        return 0

    order = list(range(len(units)))
    original = list(range(len(units)))
    from collections import Counter
    counts = Counter(strip_literals(u).strip() for u in units)

    def order_violations(o) -> list[tuple[int, int]]:
        """Conflicting pairs whose relative order changed.

        Checking only the span a move crosses is not enough: a sequence of
        individually safe moves can still end up with a unit on the far side of
        a unit it conflicts with.  (Measured: gm_AllocSpieler's two-step move of
        `g_next_object_id++` landed it *above* the store that reads it, so the
        store read the incremented value.)
        """
        pos = {u: k for k, u in enumerate(o)}
        bad = []
        for a in range(len(units)):
            for b in range(a + 1, len(units)):
                # Only pairs whose units are textually unique can be traced
                # across the run: repeated statements (a field set the same way
                # in several branches) cannot be matched to their original
                # occurrence, and guessing there reports inversions that are not
                # there.
                ua, ub = strip_literals(units[a]).strip(), strip_literals(units[b]).strip()
                if counts[ua] != 1 or counts[ub] != 1:
                    continue
                if pos[a] > pos[b] and conflicts(units[a], units[b]):
                    bad.append((a, b))
        return bad

    def render(o) -> str:
        return "".join(units[k] for k in o)

    # A candidate is a whole source file in the real file's directory (the
    # includes are relative to it), so a run that dies leaves `_hc_*.c` behind.
    # The identity header is dropped from the copies: without a `// FUNCTION:`
    # line a stray is invisible to lint (no duplicate-VA error) while
    # `probe_function.py` still finds the function by its map symbol.
    def header(text: str) -> str:
        return re.sub(r"^// FUNCTION: SERVER .*\n", "", text, flags=re.M)

    def submit(i: int, j: int) -> tuple[tuple[int, int], tuple[int, ...]]:
        tmp = src.with_name(f"_hc_{name}_{i}_{j}.c")
        tmp.write_text(header(head) + render(move(order, i, j)) + tail)
        return (i, j), score(tmp, args.va)

    def seq(o):
        """The units in the order they currently appear.

        Candidates are positions in the *current* sequence.  Checking them
        against `units` (which is indexed by original position) instead was the
        bug that let an unsafe arrangement through: after the first accepted
        move every barrier and conflict test looked at the wrong pair.
        """
        return [units[k] for k in o]

    base = score(src, args.va)
    tgt = target_size(args.va)
    print(f"baseline {base[1]} matched, instruction delta {base[2]:+d}, "
          f"object size {base[3]} vs target {tgt}")
    try:
        for rnd in range(args.rounds):
            cur = seq(order)
            cur_barrier = [barrier[k] for k in order]
            cands = [(i, i + d) for i in range(len(units))
                     for d in range(-args.reach, args.reach + 1) if d
                     and 0 <= i + d < len(units)
                     and not (i < ndec <= i + d)          # no decl after a stmt
                     and not (i >= ndec > i + d)          # no stmt before a decl
                     # no crossing a label, in either direction
                     and not any(cur_barrier[min(i, i + d):max(i, i + d) + 1])
                     # and no crossing anything that touches what we touch
                     # every unit between the two positions, excluding the
                     # moved one itself.  For a NEGATIVE move the old range
                     # started at min+1, which skipped the destination -- so a
                     # conflict with the unit being crossed was never seen, and
                     # gm_AllocSpieler's `g_next_object_id++` landed above the
                     # store that reads it.
                     and not any(conflicts(cur[i], cur[k])
                                 for k in range(min(i, i + d), max(i, i + d) + 1)
                                 if k != i)]
            with cf.ThreadPoolExecutor(max_workers=args.jobs) as ex:
                results = list(ex.map(lambda ij: submit(*ij), cands))
            for p in src.parent.glob(f"_hc_{name}_*.c"):
                p.unlink(missing_ok=True)
            best, best_move = base, None
            for mv, sc in results:
                if sc > best:
                    best, best_move = sc, mv
            if best_move is None:
                print(f"round {rnd}: no improving move among {len(cands)}; "
                      f"converged at {base[1]}")
                break
            i, j = best_move
            order = move(order, i, j)
            base = best
            src.write_text(head + render(order) + tail)
            print(f"round {rnd}: {i} -> {j}   {base[1]} matched "
                  f"(insn {base[2]:+d})  "
                  f"{strip_literals(cur[i]).strip().splitlines()[0][:46]!r}")
    finally:
        for p in src.parent.glob(f"_hc_{name}_*.c"):
            p.unlink(missing_ok=True)
    bad = order_violations(order)
    if bad:
        # Never leave a reordering that changed what a conflicting pair does:
        # restore the input and say so.
        src.write_text(head + render(original) + tail)
        print(f"REJECTED: the climb inverted {len(bad)} conflicting pair(s), "
              f"e.g. {bad[:3]}; source restored")
        return 1
    print(f"final {base[1]} matched, instruction delta {base[2]:+d}, "
          f"object size {base[3]} vs target {tgt}")
    return 0


if __name__ == "__main__":
    sys.exit(main())

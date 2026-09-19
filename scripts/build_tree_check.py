#!/usr/bin/env python3
"""Is build/ still the tree CMake generated?

Why this exists (round 1051).  ``build/`` is gitignored, so no tracked-file check,
no lint run and no `git status` can see it.  ``scripts/linktest.sh`` recompiles
with the exact command ``build.make`` records -- that is what makes its deltas
comparable to the real build -- and ``scripts/split_link.sh`` consumes the objects
that command produced.  Both therefore treat ``build.make`` as ground truth.

That trust is only sound while ``build.make`` still says what CMake wrote.  A round
that hand-edits it -- to sweep a per-file flag, a toolchain pin, an ``/O`` option,
anything -- changes what every later measurement MEANS while the source tree stays
clean and every other check in ``gate.sh`` keeps passing.  Round 1051 did exactly
that while sweeping msvc6 toolchain pins and left the tree reporting 58% residue
and a 290,816-byte deliverable, against the correct 286,720 / 8628.

The test is self-contained: CMake regenerates ``flags.make`` alongside
``build.make``, and records each object's custom flags there as

    # Custom flags: ...<obj>_FLAGS = /O2 /Gd /Oa
    # Custom options: ...<obj>_OPTIONS = /REBREW_TOOLCHAIN:msvc-6.0-sp5-pp

So every codegen flag token in ``build.make``'s compile line must appear in the
corresponding ``Custom`` comment.  A token in one and not the other was hand-added.

Usage:
    python3 scripts/build_tree_check.py            # human summary
    python3 scripts/build_tree_check.py --json     # structured
Exit status: 0 clean, 1 drift found, 3 not configured.
"""
import json
import pathlib
import re
import sys

BUILD = pathlib.Path("build/CMakeFiles/server_dll.dir")
# Tokens CMake emits for every object that are not codegen flags and are never
# listed in the Custom comments.
BOILERPLATE = ("/nologo", "/c", "/W3")
# Prefixes for output/layout switches rather than codegen ones.
PREFIX_SKIP = ("/F", "/Y", "/Z")
FLAG = re.compile(r"^/[A-Z]")


def parse_recorded(flags_text):
    """obj path -> set of flag tokens CMake recorded for it."""
    rec = {}
    # re.M is required: without it `$` anchors to end-of-STRING, so this matches
    # only if the whole file were one line -- it returned 0 objects on a flags.make
    # containing 202 Custom comments, and the checker then reported "agrees" while
    # comparing nothing.  Measured both ways while writing the guard.
    pat = re.compile(r"Custom (?:flags|options): \S*?(\S+\.obj)_(?:FLAGS|OPTIONS) = (.*)$",
                     re.M)
    for m in pat.finditer(flags_text):
        rec.setdefault(m.group(1), set()).update(m.group(2).split())
    return rec


def parse_actual(build_text):
    """[(obj path, compile line)] for every non-listing compile rule."""
    out = []
    for line in build_text.split("\n"):
        if "rebrew-cmake-cl" not in line or "/FAs" in line:
            continue
        mo = re.search(r"(CMakeFiles/server_dll\.dir/\S+?\.obj)\b", line)
        if mo:
            out.append((mo.group(1), line))
    return out


def check():
    bm, fl = BUILD / "build.make", BUILD / "flags.make"
    if not bm.exists() or not fl.exists():
        return 3, ["(not configured -- skipped)"], []
    recorded = parse_recorded(fl.read_text(errors="replace"))
    drift = []
    checked = 0
    for obj, line in parse_actual(bm.read_text(errors="replace")):
        # An object with NO Custom comment has no per-file flags: it compiles with
        # the global C_FLAGS and `rebrew cmake-flags` wrote nothing for it.  That is
        # the normal case for most of the tree and is not drift.  Compare only where
        # CMake recorded something -- which is exactly where a hand-edit shows up.
        if obj not in recorded:
            continue
        checked += 1
        known = recorded[obj]
        for tok in line.split():
            if not FLAG.match(tok) or tok in BOILERPLATE or tok.startswith(PREFIX_SKIP):
                continue
            if tok not in known:
                drift.append({"obj": obj, "flag": tok})
    lines = []
    if drift:
        lines.append(f"DRIFT: {len(drift)} unrecorded flag token(s) in build.make")
        for d in drift[:8]:
            lines.append(f"  {d['obj']}: {d['flag']}")
    else:
        lines.append("build.make agrees with flags.make "
                     f"({checked} object(s) with recorded flags)")
    return (1 if drift else 0), lines, drift


def main():
    rc, lines, drift = check()
    if "--json" in sys.argv:
        print(json.dumps({"status": "drift" if drift else "ok", "drift": drift}, indent=1))
    else:
        for l in lines:
            print(l)
    return rc


if __name__ == "__main__":
    sys.exit(main())

"""Instruction-level sequence diff between a compiled function and the target.

`rebrew diff` aligns by byte offset, so a size difference desynchronises it and
reports every later instruction as structural.  This aligns by instruction
sequence (difflib), which answers the question that matters for a stuck
function: how far is it really, and which instructions still differ.

usage:
    # target bytes for the function
    python scripts/seqdiff.py --extract 0x100093a0 2434 /tmp/target.bin
    # compile the candidate (any way; rebrew test / the CMake build both work)
    python scripts/seqdiff.py <candidate.obj> <symbol> <target.bin>

Run it with the project venv (capstone): .venv/bin/python scripts/seqdiff.py
"""

import difflib
import re
import subprocess
import sys
from pathlib import Path

import capstone

ABS = re.compile(r"0x[0-9a-f]{6,}")
PTR = re.compile(r"\b(byte|word|dword|qword|tbyte|xmmword)\s+ptr\s+")
BRANCH = re.compile(r"^(j\w+|call|loop\w*)\s+.*$")


def project_root() -> Path:
    for parent in Path(__file__).resolve().parents:
        if (parent / "rebrew-project.toml").exists():
            return parent
    raise SystemExit("project root not found")


def norm(text: str) -> str:
    """Fold operands that cannot match textually but denote the same slot."""
    text = ABS.sub("g", text)
    text = PTR.sub(lambda m: m.group(1).upper() + " ", text)
    text = text.replace("0x0,", "0,").replace(", 0x0", ", 0")
    # objdump prints the raw displacement (0) for a relocation against a
    # symbol, while the target side has the resolved address.  Both are the
    # same instruction, so fold the empty-reloc operands onto the symbol.
    text = re.sub(r"\[0\]", "[g]", text)
    text = re.sub(r"\[0 \+ ", "[g + ", text)
    text = re.sub(r"\bpush 0\b", "push g", text)
    text = re.sub(r"\s+", " ", text).strip()
    return BRANCH.sub(lambda m: m.group(1) + " <t>", text)


def target_seq(bin_path: Path) -> list[str]:
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    data = bin_path.read_bytes()
    return [norm(f"{i.mnemonic} {i.op_str}".strip()) for i in md.disasm(data, 0)]


def cand_seq(obj: Path, sym: str) -> list[str]:
    txt = subprocess.run(
        ["objdump", "-d", "--insn-width=12", str(obj)], capture_output=True, text=True
    ).stdout
    out, active = bytearray(), False
    for line in txt.splitlines():
        if line.rstrip().endswith(f"<{sym}>:"):
            active = True
            continue
        if not active:
            continue
        if not line.strip():
            break
        parts = line.split("\t")
        if len(parts) < 2:
            continue
        out += bytes.fromhex(parts[1].strip().replace(" ", ""))
    while out and out[-1] == 0x90:
        out.pop()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    return [norm(f"{i.mnemonic} {i.op_str}".strip()) for i in md.disasm(bytes(out), 0)]


def extract(va: int, size: int, out: Path) -> None:
    import pefile

    pe = pefile.PE(str(project_root() / "original" / "Server" / "server.dll"), fast_load=True)
    out.write_bytes(pe.get_data(va - pe.OPTIONAL_HEADER.ImageBase, size))


def classify(t: list[str], c: list[str]) -> str:
    """Group a diff hunk by what would have to change to close it.

    sched   the same instructions in a different order (scheduler/layout)
    operand the same mnemonics with different operands (register allocation)
    instr   a genuinely different instruction (a spelling change can move it)

    ``instr`` over-counts: difflib substitutes across a shifted hunk, so a
    hunk that is really the same instructions shifted lands here too.  Read it
    as an upper bound on spelling-level work, and ``sched``/``operand`` as the
    reliable part.
    """
    tm = [x.split()[0] for x in t]
    cm = [x.split()[0] for x in c]
    if sorted(tm) == sorted(cm):
        return "sched"
    if set(tm) == set(cm):
        return "operand"
    return "instr"


def main() -> None:
    argv = sys.argv[1:]
    triage = "--triage" in argv
    argv = [x for x in argv if x != "--triage"]
    if argv[0] == "--extract":
        extract(int(argv[1], 16), int(argv[2]), Path(argv[3]))
        return
    obj, sym, tbin = Path(argv[0]), argv[1], Path(argv[2])
    a, b = target_seq(tbin), cand_seq(obj, sym)
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    same = sum(bl.size for bl in sm.get_matching_blocks())
    print(f"target {len(a)} insns, candidate {len(b)} insns, aligned identical {same}")

    hunks = []
    ops: dict[str, int] = {}
    differing = 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            continue
        ops[tag] = ops.get(tag, 0) + 1
        differing += max(i2 - i1, j2 - j1)
        hunks.append((tag, i1, i2, j1, j2))
    print(f"opcode groups: {ops}  differing insns: {differing}")

    if triage:
        kinds: dict[str, list] = {"sched": [], "operand": [], "instr": []}
        for h in hunks:
            tag, i1, i2, j1, j2 = h
            kinds[classify(a[i1:i2], b[j1:j2])].append(h)
        for k, v in kinds.items():
            print(f"{k}: {len(v)}")
        for tag, i1, i2, j1, j2 in kinds["instr"]:
            print(f"--- {tag} T[{i1}:{i2}] C[{j1}:{j2}]")
            for x in a[i1:i2]:
                print(f"  T {x}")
            for x in b[j1:j2]:
                print(f"  C {x}")
        return

    for tag, i1, i2, j1, j2 in hunks:
        print(f"--- {tag} T[{i1}:{i2}] C[{j1}:{j2}]")
        for x in a[i1:i2]:
            print(f"  T {x}")
        for x in b[j1:j2]:
            print(f"  C {x}")


if __name__ == "__main__":
    main()

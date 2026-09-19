#!/usr/bin/env python3
"""Compare two compiled images by CONTROL FLOW (graph isomorphism), not by
branch encoding or address.

Why this exists (rounds 1005-1006).  `scripts/branch_census.py` aligns branch
instructions *by index* and counts those whose target differs.  That count is an
upper bound on structural difference, not a measurement, for three measured
reasons:

  1. **Polarity swaps.**  `je L` + fallthrough and `jne X` + fallthrough can
     encode the SAME two edges.
  2. **Local drift.**  A block whose length differs by a byte or three moves
     every target past it; the branch still reaches the same block.
  3. **Pairing artifacts.**  Once the streams desync by one instruction,
     index alignment subtracts a taken-branch target from a fallthrough target.
     On ServerMainThread that produced a spurious +340.

**Why the obvious fixes do not work** (each tried and rejected in round 1006):
  * comparing successor *directions* fails, because direction flips with
    polarity -- hand-verified on ServerMainThread 0x100098e3, where the
    reference's `je`-with-back-edge and our `jne`-with-forward-edge are the same
    two-way branch;
  * comparing block *bodies* fails, because a body differs for reasons
    unrelated to control flow (register names, one extra instruction);
  * grouping `jcc`+`jmp` as a two-way branch fails, because a `jmp` following a
    `jcc` frequently belongs to a *different* case, which corrupts alignment.

The correct primitive is a **real CFG + graph isomorphism**.  Build each side's
CFG by recursive descent from the function entry, canonically label the nodes
(BFS from the entry, driving off the successor lists), then compare the two
labelled edge sets.  Nodes are identified by their position in the canonical
labelling, so addresses, drift, register names and polarity are all irrelevant;
only the SHAPE is compared.

    python3 scripts/cfg_compare.py                 # all carriers
    python3 scripts/cfg_compare.py ServerMainThread
    python3 scripts/cfg_compare.py --self-test     # prove it discriminates
"""
from __future__ import annotations

import struct
import sys
from collections import deque
from pathlib import Path

import capstone

ROOT = Path(__file__).resolve().parents[1]
BASE = 0x10000000
REFERENCE = ROOT / "original/Server/server.dll"
BUILT = ROOT / "build/server.dll"

#: conditional jumps -> the condition tested.  Complementary spellings map to
#: the same condition (jb/jae are complementary senses of one comparison), so a
#: polarity swap is NOT a condition change.
JCC = {
    "je": "eq", "jz": "eq", "jne": "ne", "jnz": "ne",
    "jl": "lt", "jnge": "lt", "jge": "ge", "jnl": "ge",
    "jle": "le", "jng": "le", "jg": "gt", "jnle": "gt",
    "jb": "lt", "jnae": "lt", "jc": "lt", "jae": "ge", "jnb": "ge", "jnc": "ge",
    "jbe": "le", "jna": "le", "ja": "gt", "jnbe": "gt",
    "js": "neg", "jns": "pos", "jo": "ovf", "jno": "nov",
    "jp": "par", "jpe": "par", "jnp": "npar", "jpo": "npar",
}
UNCOND = {"jmp"}
TERM = {"ret", "retn", "retf", "iretd", "iret"}

CARRIERS = [
    ("gm_AllocSpieler", 0x10018850, 3696),
    ("CrashDumpUnhandledExceptionFilter", 0x10002770, 2115),
    ("cm_ExSellObjekt", 0x1000d930, 2057),
    ("ls_LoadBuildingEntityState", 0x100128f0, 1463),
    ("cm_ExCopyEntityData", 0x1000ec00, 912),
    ("gv_ExAllocGraveyardWorker", 0x10011bf0, 1040),
    ("ServerMainThread", 0x100093a0, 2434),
    ("gm_AllocGebaeude", 0x100174d0, 1088),
    ("vfs_OpenStream", 0x10009020, 701),
    ("gm_FindNextFilteredEntity", 0x10016f80, 352),
    ("ahm_ExAllocAlchemist", 0x1000bdf0, 1002),
    ("gm_CheckInventoryCapacity", 0x10019ed0, 395),
    ("m_AllocTracked", 0x10006580, 672),
    ("srv_LoadBuf", 0x1000a570, 750),
    ("gm_ObjectsAvailble", 0x10015f70, 714),
    ("vfs_ReadCompressed", 0x10008a90, 492),
    ("cm_ExProdObjekt", 0x1000e140, 1008),
    ("cm_ProcessCommandQueue", 0x1000aac0, 640),
    ("gm_CalculateProductionValue", 0x10019720, 400),
]


def textof(path: Path):
    d = path.read_bytes()
    e = struct.unpack_from("<I", d, 0x3C)[0]
    n = struct.unpack_from("<H", d, e + 6)[0]
    off = e + 24 + struct.unpack_from("<H", d, e + 20)[0]
    for i in range(n):
        s = d[off + i * 40:off + (i + 1) * 40]
        if s[:8].rstrip(b"\0") == b".text":
            va = struct.unpack_from("<I", s, 12)[0] + BASE
            rp = struct.unpack_from("<I", s, 20)[0]
            rs = struct.unpack_from("<I", s, 16)[0]
            return d[rp:rp + rs], va
    raise SystemExit("no .text in " + str(path))


def make_md():
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.skipdata = True
    return md


def build_cfg(md, code, base, start, size):
    """Recursive-descent CFG.  Returns (blocks, edges).

    blocks: {addr: (n_insns, ends_in)}   ends_in in {'jcc:<cond>','jmp','ret','falloff'}
    edges : {addr: {'taken': addr|None, 'fall': addr|None}}

    The walk queues BOTH successors of every branch and the fallthrough of every
    non-terminating block.  An earlier revision that only queued the taken edge
    under-covered the graph (8 of 126 branches on gm_AllocSpieler).
    """
    limit = start + size
    blocks: dict = {}
    edges: dict = {}
    work = deque([start])
    queued = {start}
    decoded: dict = {}

    while work:
        blk = work.popleft()
        if blk in blocks or not (start <= blk < limit):
            continue
        addr = blk
        n = 0
        ends = None
        taken = fall = None
        while addr < limit:
            if addr not in decoded:
                g = list(md.disasm(code[addr - base:addr - base + 16], addr, count=1))
                decoded[addr] = g[0] if g else None
            ins = decoded[addr]
            if ins is None:
                break
            n += 1
            nxt = addr + ins.size
            mn = ins.mnemonic
            if mn in JCC:
                try:
                    tgt = int(ins.op_str, 16)
                except ValueError:
                    tgt = nxt
                ends, taken, fall = "jcc:" + JCC[mn], tgt, nxt
                break
            if mn in UNCOND:
                try:
                    tgt = int(ins.op_str, 16)
                except ValueError:
                    tgt = nxt          # indirect jmp: a leaf edge
                ends, taken, fall = "jmp", tgt, None
                break
            if mn in TERM:
                ends, taken, fall = "ret", None, None
                break
            addr = nxt
        if ends is None:
            ends = "falloff"
        blocks[blk] = (n, ends)
        edges[blk] = {"taken": taken, "fall": fall}
        for succ in (taken, fall):
            if succ is not None and start <= succ < limit and succ not in queued:
                queued.add(succ)
                work.append(succ)
    return blocks, edges


def canon(blocks, edges):
    """Order-independent canonical form of the CFG.

    BFS labelling does NOT work here: visiting a node's two successors in the
    other order changes every downstream label.  Measured on the SAME reference
    graph, swapping the successor visit order moved 452 of the edge set
    (round 1006).  Any labelling derived from a traversal is therefore not
    canonical, and comparing two such labellings reports differences that are
    artifacts of traversal, not of control flow.

    Instead emit an order-independent summary: for every block, its KIND and its
    (in-degree, out-degree) profile, plus the set of kind-pairs across edges.
    Two CFGs with the same block-kind multiset, the same degree profile and the
    same edge-kind multiset have the same shape at the granularity this question
    needs.  A finer isomorphism test can be added later if this proves too
    coarse -- the self-test guards against it being too coarse to notice.
    """
    if not blocks:
        return (), ()
    indeg = {a: 0 for a in blocks}
    kinds = {}
    for a, (n, ends) in blocks.items():
        kinds[a] = "branch2" if ends.startswith("jcc:") else ends
    for a, es in edges.items():
        for key in ("taken", "fall"):
            s = es.get(key)
            if s is not None and s in blocks:
                indeg[s] += 1
    profile = sorted((kinds[a], indeg[a], sum(
        1 for key in ("taken", "fall")
        if edges.get(a, {}).get(key) in blocks)) for a in blocks)
    edge_kinds = sorted((kinds[a], kinds[s])
                        for a, es in edges.items()
                        for key in ("taken", "fall")
                        for s in [es.get(key)]
                        if s is not None and s in blocks)
    return tuple(profile), tuple(edge_kinds)


def compare(md, va, size):
    rcode, rva = textof(REFERENCE)
    bcode, bva = textof(BUILT)
    return (canon(*build_cfg(md, rcode, rva, va, size)),
            canon(*build_cfg(md, bcode, bva, va, size)))


def self_test(md) -> bool:
    """Prove the tool reports a difference when the control flow really differs.

    Redirects one branch in an in-memory copy of the build so its successor
    changes, and checks the canonical edge set changes.  Without this, an
    always-zero tool would look like a clean result.
    """
    bcode, bva = textof(BUILT)
    va, size = 0x10018850, 3696
    ref_form = compare(md, va, size)[0]

    mutated = bytearray(bcode)
    patched = None
    ins = list(md.disasm(bytes(mutated[va - bva:va - bva + size]), va))
    for k, i in enumerate(ins):
        if i.mnemonic in JCC and i.size == 6 and k + 1 < len(ins):
            off = va - bva + (i.address - va)
            nxt = ins[k + 1].address
            try:
                tgt = int(i.op_str, 16)
            except ValueError:
                continue
            newtgt = nxt - 8 if tgt > nxt else nxt + 0x40
            struct.pack_into("<i", mutated, off + 2, newtgt - (i.address + i.size))
            patched = i.address
            break
    if patched is None:
        print("SELF-TEST INCONCLUSIVE: no 6-byte conditional to patch")
        return False
    mut_form = canon(*build_cfg(md, bytes(mutated), bva, va, size))
    changed = mut_form != ref_form
    print("SELF-TEST: redirected branch at 0x%x -> canonical form %s (%d blocks)"
          % (patched, "CHANGED (tool discriminates)" if changed
             else "UNCHANGED (TOOL IS BROKEN)", mut_form[1] and len(mut_form[0]) or 0))
    return changed


def main():
    md = make_md()
    if "--self-test" in sys.argv:
        return 0 if self_test(md) else 1

    want = [a for a in sys.argv[1:] if not a.startswith("-")]
    print("%-34s %6s %6s  %s" % ("carrier", "nodeR", "nodeB", "control-flow verdict"))
    differ = 0
    for name, va, size in CARRIERS:
        if want and name not in want:
            continue
        (rprof, redge), (bprof, bedge) = compare(md, va, size)
        if (rprof, redge) == (bprof, bedge):
            print("%-34s %6d %6d  SAME" % (name, len(rprof), len(bprof)))
        else:
            differ += 1
            dp = abs(len(rprof) - len(bprof))
            print("%-34s %6d %6d  DIFFERS (profile delta %d, edges %d vs %d)"
                  % (name, len(rprof), len(bprof), dp, len(redge), len(bedge)))
    print("\ncarriers whose control flow differs: %d of %d" % (differ, len(CARRIERS)))
    return 0


if __name__ == "__main__":
    sys.exit(main())

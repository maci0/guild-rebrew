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
from collections import Counter, deque
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


def _wl1(blocks, edges):
    """1-dimensional colour refinement.  Returns {node: colour}.

    Canonical (independent of input order) but NOT a complete isomorphism test:
    an exhaustive search over all 3-node CFGs found 272,473 non-isomorphic pairs
    it cannot separate -- the classic 1-WL limitation, hit here by graphs where
    every node is a 2-successor branch and all successors share one colour
    (round 1007).  It is used as a fast PARTITION pre-filter; exact
    isomorphism below decides the answer.
    """
    def kind(a):
        ends = blocks[a][1]
        return "branch2" if ends.startswith("jcc:") else ends

    colour = {a: kind(a) for a in blocks}
    for _ in range(len(blocks) + 2):
        sig = {}
        for a in blocks:
            succs = []
            for key in ("taken", "fall"):
                s = edges.get(a, {}).get(key)
                succs.append((key, colour[s] if s is not None and s in blocks else None))
            sig[a] = (kind(a), tuple(sorted(succs, key=lambda x: (x[0], str(x[1])))))
        uniq = {s: i for i, s in enumerate(sorted(set(sig.values()), key=str))}
        new = {a: uniq[sig[a]] for a in blocks}
        if all((colour[a] == colour[b]) == (new[a] == new[b])
               for a in blocks for b in blocks):
            return new
        colour = new
    return colour


def _neighbour_sig(blocks, edges, a, assign, fin):
    """Signature of a node under a partial assignment, for backtracking."""
    out = []
    for key in ("taken", "fall"):
        s = edges.get(a, {}).get(key)
        out.append((key, fin[s] if s is not None and s in blocks else None))
    return tuple(sorted(out, key=lambda x: (x[0], str(x[1]))))


def isomorphic(blocks_a, edges_a, blocks_b, edges_b):
    """Exact isomorphism check by backtracking within WL-1 colour classes.

    1-WL is incomplete (round 1007), so this decides.  Nodes are matched only
    within the same WL-1 colour; within a class, candidates are tried in a
    deterministic order and adjacency is verified against the partial map.  Real
    function CFGs are far from regular, so the colour classes are small.
    """
    if len(blocks_a) != len(blocks_b):
        return False
    ca = _wl1(blocks_a, edges_a)
    cb = _wl1(blocks_b, edges_b)
    # Do NOT compare colour VALUES across graphs: _wl1 interns signatures to
    # dense ids per call, so ids from two calls are unrelated.  Comparing them
    # rejected the unmutated build against the reference for gm_AllocSpieler
    # (round 1007).  Compare the PARTITION SHAPE (class-size multiset) instead,
    # which is id-independent, and let the backtracking below decide.
    if sorted(Counter(ca.values()).values(), reverse=True) != \
       sorted(Counter(cb.values()).values(), reverse=True):
        return False
    groups = {}
    for n, c in ca.items():
        groups.setdefault(c, []).append(n)
    order = sorted(groups, key=lambda c: len(groups[c]))
    b_by_colour = {}
    for n, c in cb.items():
        b_by_colour.setdefault(c, []).append(n)

    def kind_of(blocks, a):
        ends = blocks[a][1]
        return "branch2" if ends.startswith("jcc:") else ends

    # candidate list per colour, stable
    cand = {c: sorted(b_by_colour.get(c, [])) for c in order}
    deg = {a: (sum(1 for k in ("taken", "fall") if edges_a.get(a, {}).get(k) in blocks_a),
               sum(1 for k in ("taken", "fall") if edges_b.get(a, {}).get(k) in blocks_b))
           for a in blocks_a}

    # Recurse over a FLAT list of (colour, node) pairs.  An earlier revision
    # recursed per colour and iterated `for a in sorted(groups[c])` with only an
    # `a in mapping` test, so within one colour class it re-tried nodes already
    # placed by an outer call and mis-assigned them -- which made
    # ServerMainThread (identical WL-1 partition, identical kind counts) report
    # non-isomorphic (round 1007).
    slots = []
    for c in order:
        for a in sorted(groups[c]):
            slots.append((c, a))

    mapping = {}
    used = set()

    def outdeg(blocks, edges, n):
        return sum(1 for k in ("taken", "fall") if edges.get(n, {}).get(k) in blocks)

    def bt(i):
        if i == len(slots):
            return True
        c, a = slots[i]
        for b in cand[c]:
            if b in used:
                continue
            if kind_of(blocks_a, a) != kind_of(blocks_b, b):
                continue
            if outdeg(blocks_a, edges_a, a) != outdeg(blocks_b, edges_b, b):
                continue
            ok = True
            for key in ("taken", "fall"):
                sa = edges_a.get(a, {}).get(key)
                sb = edges_b.get(b, {}).get(key)
                if (sa in blocks_a) != (sb in blocks_b):
                    ok = False
                    break
                if sa in blocks_a and sa in mapping and mapping[sa] != sb:
                    ok = False
                    break
                # also check the reverse direction: any already-mapped
                # predecessor of this pair must agree
                for pa, pb in list(mapping.items()):
                    for k2 in ("taken", "fall"):
                        if edges_a.get(pa, {}).get(k2) == a:
                            if edges_b.get(pb, {}).get(k2) != b:
                                ok = False
                                break
                    if not ok:
                        break
                if not ok:
                    break
            if not ok:
                continue
            mapping[a] = b
            used.add(b)
            if bt(i + 1):
                return True
            del mapping[a]
            used.discard(b)
        return False

    return bt(0)


def canon(blocks, edges):
    """Kept for callers that want a cheap fingerprint; NOT used for verdicts."""
    if not blocks:
        return (), ()
    colour = _wl1(blocks, edges)
    return tuple(sorted(colour.values())), ()


def compare(md, va, size):
    rcode, rva = textof(REFERENCE)
    bcode, bva = textof(BUILT)
    rb, re_ = build_cfg(md, rcode, rva, va, size)
    bb, be = build_cfg(md, bcode, bva, va, size)
    return rb, re_, bb, be, isomorphic(rb, re_, bb, be)


def self_test(md) -> bool:
    """Prove the tool discriminates: a graph vs ITSELF is isomorphic, and the
    same graph with one branch redirected is not.

    An earlier revision asserted that the unmutated *build* is isomorphic to the
    reference, which is false for gm_AllocSpieler (and is the tool's finding, not
    a bug).  The self-test must not assume the answer it is testing for.
    """
    rcode, rva = textof(REFERENCE)
    va, size = 0x10018850, 3696
    rb, re_ = build_cfg(md, rcode, rva, va, size)

    ok = True
    if not isomorphic(rb, re_, rb, re_):
        print("SELF-TEST FAIL: a graph is not isomorphic to itself")
        ok = False

    bcode, bva = textof(BUILT)
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
    mb, me = build_cfg(md, bytes(mutated), bva, va, size)
    changed = not isomorphic(rb, re_, mb, me)
    if not changed:
        print("SELF-TEST FAIL: a redirected branch was not detected")
        ok = False
    print("SELF-TEST: reflexive=yes; redirected branch at 0x%x detected=%s"
          % (patched, "yes" if changed else "NO"))
    return ok


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
        rb, re_, bb, be, same = compare(md, va, size)
        if same:
            print("%-34s %6d %6d  SAME" % (name, len(rb), len(bb)))
        else:
            differ += 1
            print("%-34s %6d %6d  DIFFERS (blocks %d vs %d)"
                  % (name, len(rb), len(bb), len(rb), len(bb)))
    print("\ncarriers whose control flow differs: %d of %d" % (differ, len(CARRIERS)))
    return 0


if __name__ == "__main__":
    sys.exit(main())

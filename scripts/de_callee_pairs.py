"""Pair English and German functions through the code references of already matched twins.

usage: uv run --frozen python scripts/de_callee_pairs.py [client|server] > docs/de/map-en-de-callee.csv
       (server: > docs/de/map-server-en-de-callee.csv)

A German twin that measures EXACT or RELOC against its English definition has the same instruction
stream up to relocated operands. Zipping both disassemblies, every operand that points into .text
on both sides (call/jmp targets, pushed or stored function pointers) names an English address and
its German counterpart. A pair is kept when it targets an English function row (GOLDTL or SERVER), every
matched twin that references it agrees on the German address (no conflicts in either direction),
and the German address is not already bound to a different definition (look-alike duplicates).
"""
import collections, csv, sys
import capstone, lief
from rebrew.cli import require_config
from rebrew.metadata.functions import load_metadata

md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32); md.detail = True
def image(path):
    pe = lief.parse(path); base = pe.optional_header.imagebase
    t = next(s for s in pe.sections if s.name == ".text"); lo = base + t.virtual_address
    return bytes(t.content), lo, lo + t.virtual_size
MODES = {"client": ("GildeGold_TL.exe", "GOLDTL", "GOLDDE", "original/Europa1400Gold_TL.exe", "original/de/GildeGold_TL.exe"),
         "server": ("server_de.dll", "SERVER", "SERVERDE", "original/Server/server.dll", "original/de/server.dll")}
TARGET, EN_MOD, DE_MOD, EN_BIN, DE_BIN = MODES[sys.argv[1] if len(sys.argv) > 1 else "client"]
EN, DE = image(EN_BIN), image(DE_BIN)
def refs(img, va, size):
    code, lo, hi = img
    out = []
    for i in md.disasm(code[va - lo: va - lo + size], va):
        vals = [op.imm for op in i.operands if op.type == capstone.x86.X86_OP_IMM]
        vals += [op.mem.disp & 0xffffffff for op in i.operands if op.type == capstone.x86.X86_OP_MEM and op.mem.base == 0]
        out.append((i.mnemonic, [v for v in vals if lo <= v < hi]))
    return out

meta = load_metadata(require_config(target=TARGET, json_mode=True).metadata_dir)
en_rows = {va: r for (m, va), r in meta.items() if m == EN_MOD}
en_by_def = {(r.get("file"), r.get("name")): va for va, r in en_rows.items() if r.get("kind") == "FUNCTION"}
votes = collections.defaultdict(collections.Counter)
for (m, de_va), r in meta.items():
    if m != DE_MOD or r.get("status") not in ("EXACT", "RELOC"): continue
    en_va = en_by_def.get((r.get("file"), r.get("name")))
    if en_va is None: continue
    a, b = refs(EN, en_va, en_rows[en_va]["size"]), refs(DE, de_va, r["size"])
    if len(a) != len(b): continue
    for (ma, va), (mb, vb) in zip(a, b):
        if ma != mb or len(va) != len(vb): break
        for x, y in zip(va, vb): votes[x][y] += 1
de_claims = collections.defaultdict(set)
for x, c in votes.items():
    for y in c: de_claims[y].add(x)
w = csv.writer(sys.stdout); w.writerow(["en_va", "de_va", "method", "references"])
for x, c in sorted(votes.items()):
    if len(c) != 1 or x not in en_rows or en_rows[x].get("kind") != "FUNCTION": continue
    (y, n), = c.items()
    if len(de_claims[y]) != 1: continue
    bound = meta.get((DE_MOD, y))
    if bound and (bound.get("file"), bound.get("name")) != (en_rows[x].get("file"), en_rows[x].get("name")): continue
    w.writerow(["%08x" % x, "%08x" % y, "callee", n])

"""Pair the remaining unbound German client rows with English definitions that have no German twin.

usage: uv run --frozen python scripts/de_global_align.py > docs/de/map-en-de-global.csv

Unlike de_gap_align.py this ignores link order: every unbound German inventory row (game code,
below the external range) is compared with every English GOLDTL function row that has a C
definition and no German binding, by capstone mnemonic similarity (size ratio 0.8..1.25). A pair is
kept when its score is >= 0.9 and at least 0.05 above the next candidate on both sides, so
look-alike siblings are not paired. Binding and measuring decides.
"""
import csv, difflib, json, sys
import capstone, lief
from rebrew.cli import require_config
from rebrew.metadata.functions import load_metadata
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
def loader(path):
    pe = lief.parse(path); b = pe.optional_header.imagebase
    t = next(s for s in pe.sections if s.name == ".text"); lo = b + t.virtual_address; c = bytes(t.content)
    return lambda va, n: [i.mnemonic for i in md.disasm(c[va - lo: va - lo + n], va)]
DE, EN = loader("original/de/GildeGold_TL.exe"), loader("original/Europa1400Gold_TL.exe")
meta = load_metadata(require_config(target="GildeGold_TL.exe", json_mode=True).metadata_dir)
de_bound = {va for (m, va) in meta if m == "GOLDDE"}
bound_defs = {(r.get("file"), r.get("name")) for (m, va), r in meta.items() if m == "GOLDDE"}
inv = [e for e in json.load(open("db/inventory-GildeGold_TL.exe.json")) if e["va"] not in de_bound and e["va"] < 0x5cb000 and e["size"] >= 16]
ens = [(va, r["size"]) for (m, va), r in meta.items() if m == "GOLDTL" and r.get("kind") == "FUNCTION" and r.get("file") and r.get("size")
       and r.get("status") in ("EXACT", "RELOC", "NEAR_MATCHING", "SIZE_MISMATCH") and (r["file"], r["name"]) not in bound_defs]
enm = {va: EN(va, n) for va, n in ens}
scores = {}
for e in inv:
    d = DE(e["va"], e["size"])
    for va, n in ens:
        if 0.8 <= e["size"] / n <= 1.25:
            scores[(e["va"], va)] = difflib.SequenceMatcher(None, d, enm[va], autojunk=False).ratio()
best_de, best_en = {}, {}
for (d, e), s in scores.items():
    best_de.setdefault(d, []).append((s, e)); best_en.setdefault(e, []).append((s, d))
w = csv.writer(sys.stdout); w.writerow(["en_va", "de_va", "method", "similarity", "margin"])
for d, lst in sorted(best_de.items()):
    lst.sort(reverse=True); s, e = lst[0]
    second = lst[1][0] if len(lst) > 1 else 0
    other = sorted(best_en[e], reverse=True); second_en = other[1][0] if len(other) > 1 else 0
    if s >= 0.9 and s - second >= 0.05 and other[0][1] == d and s - second_en >= 0.05:
        w.writerow(["%08x" % e, "%08x" % d, "global-mnemonic", "%.3f" % s, "%.3f" % min(s - second, s - second_en)])

"""Pair unpaired German client rows with unpaired English rows inside link-order gaps.

usage: uv run --frozen python scripts/de_gap_align.py > docs/de/map-en-de-gapmnem.csv

German and English link the same objects in the same order, so a German row between two paired
neighbours a < x < b has its twin, if any, among the unpaired English rows between pair(a) and
pair(b). Inside each such gap, German units (1..3 contiguous inventory rows, since the German
inventory splits some functions at early exits) are matched to English rows by capstone mnemonic
similarity (>= 0.9, size ratio 0.8..1.25), best first, keeping link order. Look-alike siblings\n(scores within 0.01) pair only as a whole cluster in link order with equal counts on both sides. Inputs: the other
docs/de/map-en-de*.csv maps and both inventories. The pairs are candidates: binding them and
measuring decides; fragment rows of a unit are merged only after the head measures RELOC.
"""
import json, csv, glob, collections, bisect, difflib, sys
import lief, capstone
from rebrew.cli import require_config
from rebrew.metadata.functions import load_metadata
meta = load_metadata(require_config(target="GildeGold_TL.exe", json_mode=True).metadata_dir)
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
def loader(path):
    pe = lief.parse(path); base = pe.optional_header.imagebase
    t = next(s for s in pe.sections if s.name == ".text"); lo = base + t.virtual_address; b = bytes(t.content)
    return lambda va, n: [i.mnemonic for i in md.disasm(b[va-lo:va-lo+n], va)]
dem, enm = loader("original/de/GildeGold_TL.exe"), loader("original/Europa1400Gold_TL.exe")
inv = sorted(json.load(open("db/inventory-GildeGold_TL.exe.json")), key=lambda e: e["va"])
eninv = sorted(json.load(open("db/inventory-Europa1400Gold_TL.exe.json")), key=lambda e: e["va"])
pair = {}
for f in [p for p in glob.glob("docs/de/map-en-de*.csv") if "gapmnem" not in p]:
    for r in csv.DictReader(open(f)): pair.setdefault(int(r["de_va"],16), int(r["en_va"],16))
used_en = set(pair.values()); paired_de = sorted(pair); envas = [e["va"] for e in eninv]
gaps = collections.defaultdict(list)
for idx, e in enumerate(inv):
    v = e["va"]
    if v in pair or v >= 0x5cb000: continue
    i = bisect.bisect(paired_de, v)
    if i == 0 or i == len(paired_de): continue
    a, b = paired_de[i-1], paired_de[i]
    if pair[a] < pair[b]: gaps[(a, b)].append(idx)
def sim(x, y):
    return difflib.SequenceMatcher(None, x, y, autojunk=False).ratio()
w = csv.writer(sys.stdout); w.writerow(["en_va", "de_va", "method", "de_rows", "de_size", "en_size", "similarity"])
for (a, b), idxs in sorted(gaps.items()):
    lo, hi = bisect.bisect_right(envas, pair[a]), bisect.bisect_left(envas, pair[b])
    ens = [x for x in eninv[lo:hi] if x["va"] not in used_en]
    if not ens: continue
    # German units: start at each unpaired row, extend over contiguous unpaired rows
    units = []
    for k, idx in enumerate(idxs):
        rows = [inv[idx]]
        for nxt in idxs[k+1:k+3]:
            if inv[nxt]["va"] == rows[-1]["va"] + rows[-1]["size"]: rows = rows + [inv[nxt]]
            else: break
            units.append(list(rows))
        units.insert(len(units) - (len(rows) - 1), [inv[idx]])
    # near-best edges (within 0.01 of a unit's or an English row's best score) form clusters of
    # look-alike siblings; a cluster is paired in link order only if both sides have the same number
    # of German starts and English rows, otherwise it is ambiguous and dropped
    edges = {}
    for u in units:
        size = u[-1]["va"] + u[-1]["size"] - u[0]["va"]
        dm = dem(u[0]["va"], size)
        for en in ens:
            if not 0.8 <= size / en["size"] <= 1.25: continue
            s = sim(dm, enm(en["va"], en["size"]))
            if s >= 0.9:
                key = (u[0]["va"], en["va"])
                if key not in edges or (s, -abs(size - en["size"])) > edges[key][:2]:
                    edges[key] = (s, -abs(size - en["size"]), u, size, en)
    best_de, best_en = collections.defaultdict(float), collections.defaultdict(float)
    for (d, e), (s, *_ ) in edges.items():
        best_de[d] = max(best_de[d], s); best_en[e] = max(best_en[e], s)
    near = [(d, e) for (d, e), (s, *_ ) in edges.items() if s >= best_de[d] - 0.01 and s >= best_en[e] - 0.01]
    parent = {}
    def find(x):
        while parent.setdefault(x, x) != x: x = parent[x]
        return x
    for d, e in near: parent[find(("d", d))] = find(("e", e))
    clusters = collections.defaultdict(lambda: (set(), set()))
    for d, e in near: clusters[find(("d", d))][0].add(d); clusters[find(("d", d))][1].add(e)
    proposals = []
    for ds, es in clusters.values():
        if len(ds) != len(es): continue
        for d, e in zip(sorted(ds), sorted(es)):
            if (d, e) not in edges: break
        else:
            proposals += [edges[(d, e)] for d, e in zip(sorted(ds), sorted(es))]
    proposals.sort(key=lambda t: (t[0], t[1]), reverse=True)
    taken_de, taken_en, chosen = set(), set(), []
    for s, _, u, size, en in proposals:
        rv = {r["va"] for r in u}
        if rv & taken_de or en["va"] in taken_en: continue
        if any((u[0]["va"] < c[0]) != (en["va"] < c[1]) for c in chosen): continue
        taken_de |= rv; taken_en.add(en["va"]); chosen.append((u[0]["va"], en["va"]))
        w.writerow(["%08x" % en["va"], "%08x" % u[0]["va"], "gap-mnemonic", " ".join("%x" % r["va"] for r in u), size, en["size"], "%.3f" % s])

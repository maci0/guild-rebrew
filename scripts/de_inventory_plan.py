"""Plan German client inventory repairs from German twins that measure EXACT or RELOC.

usage: uv run --frozen python scripts/de_inventory_plan.py [client|server] > plan.json

A German row that measures EXACT/RELOC proves that the function occupies [va, va+size): the
compiled English definition, SIZE bytes long and ending in its own last instruction, matches those
German bytes. Its inventory extent is that range (a row that only runs on into 0x90/0xcc alignment
padding is left as it is). The plan, applied in order with
`rebrew binary repair-extents`, makes the inventory agree:
  shrink    a row that starts before a proven start and runs into it ends there;
  admit     a proven start that is no inventory row is added (--add-missing);
  merge     rows that begin inside a proven extent are absorbed into it (--merge, in order);
  resize    the proven row gets its proven extent;
  remainder when a row ran past a proven end into code after the padding, and the proven function
            ends in ret/jmp, that code is a separate function: it is admitted with the rest of the
            old row's extent.
A proven extent that would end inside a later row that starts after it is skipped (needs review).
Apply every phase of one plan, in this order: shrink, trim (resizes that make a row smaller),
admit, remainder (both --add-missing), merge, grow (the other resizes). Do not re-plan between
phases: a trimmed row's remainder is only known from the plan made before the trim.
"""
import bisect, json, sys
import capstone, lief
from rebrew.cli import require_config
from rebrew.metadata.functions import load_metadata

MODES = {"client": ("GildeGold_TL.exe", "GOLDDE", "db/inventory-GildeGold_TL.exe.json", "original/de/GildeGold_TL.exe"),
         "server": ("server_de.dll", "SERVERDE", "db/inventory-server_de.dll.json", "original/de/server.dll")}
TARGET, DE_MOD, INVENTORY, BINARY = MODES[sys.argv[1] if len(sys.argv) > 1 else "client"]
meta = load_metadata(require_config(target=TARGET, json_mode=True).metadata_dir)
inv = sorted(json.load(open(INVENTORY)), key=lambda e: e["va"])
pe = lief.parse(BINARY); base = pe.optional_header.imagebase
md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
read = lambda va, n: bytes(pe.get_content_from_virtual_address(va - base, n)) if n > 0 else b""
proven = {va: r["size"] for (m, va), r in meta.items()
          if m == DE_MOD and r.get("status") in ("EXACT", "RELOC") and r.get("size")}

def is_pad(va, n):
    return read(va, n).strip(b"\x90\xcc") == b""

def code_after(end, limit):
    while end < limit and read(end, 1) in (b"\x90", b"\xcc"):
        end += 1
    return end

def last_is_exit(va, size):
    last = None
    for i in md.disasm(read(va, size), va):
        last = i
    return last is not None and last.address + last.size == va + size and last.mnemonic in ("ret", "jmp")

rows = {e["va"]: e["size"] for e in inv}
plan = {"shrink": {}, "admit": {}, "merge": [], "resize": {}, "remainder": {}, "skipped": []}  # resize -> trim/grow
for va in sorted(proven):
    starts = sorted(rows)
    end = va + proven[va]
    i = bisect.bisect_right(starts, va) - 1
    container = starts[i] if i >= 0 and starts[i] < va and starts[i] + rows[starts[i]] > va else None
    inner = [s for s in starts if va < s < end]
    # how far the old rows covering this extent reach
    reach = max([s + rows[s] for s in inner] + ([container + rows[container]] if container is not None else [])
                + ([va + rows[va]] if va in rows else []) + [end])
    resume = code_after(end, reach)
    if resume < reach and not last_is_exit(va, proven[va]):
        plan["skipped"].append([hex(va), "old rows run on past the proven end, which is no ret/jmp"]); continue
    if any(s < resume and s + rows[s] > reach for s in starts if s > end):
        plan["skipped"].append([hex(va), "extent overlaps a later row"]); continue
    if container is not None:
        created = next((k for k in ("admit", "remainder") if hex(container) in plan[k]), None)
        plan[created or "shrink"][hex(container)] = va - container
        rows[container] = va - container
    if va not in rows:
        first = inner[0] if inner else end
        plan["admit"][hex(va)] = first - va
        rows[va] = first - va
    for s in inner:
        if va + rows[va] != s:  # merges need contiguity: close a gap by resizing first
            plan["resize"].setdefault("pre", {})[hex(va)] = s - va
            rows[va] = s - va
        plan["merge"].append([hex(va), hex(s)])
        rows[va] = s + rows.pop(s) - va
    if resume < reach:
        if resume not in rows:  # the old inventory also has overlapping rows; an existing start stays as it is
            limit = resume + proven[resume] if resume in proven else reach
            later = [s for s in rows if resume < s < limit]
            stop = min(later) if later else limit
            rem = "admit" if resume in proven else "remainder"
            plan[rem][hex(resume)] = stop - resume
            rows[resume] = plan[rem][hex(resume)]
        plan["resize"][hex(va)] = proven[va]
        rows[va] = proven[va]
    elif va + rows[va] < end:
        plan["resize"][hex(va)] = proven[va]
        rows[va] = proven[va]
orig = {e["va"]: e["size"] for e in inv}
resize = {k: v for k, v in plan.pop("resize").items() if k != "pre"}
plan["trim"] = {k: v for k, v in resize.items() if int(k, 16) in orig and v < orig[int(k, 16)]}
plan["grow"] = {k: v for k, v in resize.items() if k not in plan["trim"]}
json.dump(plan, sys.stdout, indent=1)
print({k: len(v) for k, v in plan.items()}, file=sys.stderr)

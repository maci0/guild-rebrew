"""Apply a plan from scripts/de_inventory_plan.py with rebrew binary repair-extents, phase by phase.

usage: uv run --frozen python scripts/de_inventory_apply.py <plan.json> [client|server]

Order: shrink, trim, admit, remainder, merge, grow (see de_inventory_plan.py). Every phase is
previewed first and applied with the preview's --expected-digest; each row's reason names the rule.
"""
import json, subprocess, sys

plan = json.load(open(sys.argv[1]))
target = {"client": "GildeGold_TL.exe", "server": "server_de.dll"}[sys.argv[2] if len(sys.argv) > 2 else "client"]
REASONS = {
    "shrink": "Row ran into a German function that measures EXACT/RELOC against its English twin; it now ends where that function starts (scripts/de_inventory_plan.py)",
    "trim": "Extent of a German function that measures EXACT/RELOC against its English twin: SIZE bytes ending in its own last instruction (scripts/de_inventory_plan.py)",
    "admit": "Start of a German function that measures EXACT/RELOC against its English twin (admitted extent up to the next row; scripts/de_inventory_plan.py)",
    "remainder": "Code after the alignment padding that follows a proven German function ending in ret/jmp, up to where the old row ended: a separate function (scripts/de_inventory_plan.py)",
    "merge": "Row begins inside the extent of a German function that measures EXACT/RELOC against its English twin (scripts/de_inventory_plan.py)",
    "grow": "Extent of a German function that measures EXACT/RELOC against its English twin: SIZE bytes ending in its own last instruction (scripts/de_inventory_plan.py)",
}
def run(args, reason):
    base = ["uv", "run", "--frozen", "rebrew", "binary", "repair-extents", *args, "--reason", reason, "--target", target, "--json"]
    pre = json.loads(subprocess.run(base + ["--dry-run"], capture_output=True, text=True, check=True).stdout)
    out = json.loads(subprocess.run(base + ["--expected-digest", pre["input_digest"]], capture_output=True, text=True, check=True).stdout)
    return {k: len(v) for k, v in out.items() if isinstance(v, list)}
for phase in ("shrink", "trim", "admit", "remainder", "merge", "grow"):
    items = plan.get(phase) or {}
    if not items: continue
    if phase == "merge": args = [a for h, t in items for a in ("--merge", f"{h}={t}")]
    else: args = [f"{k}={v}" for k, v in items.items()]
    if phase in ("admit", "remainder"): args = ["--add-missing"] + args
    print(phase, run(args, REASONS[phase]))

#!/usr/bin/env python3
"""Insert the GOLD FUNCTION marker for each GOLDTL->GOLD twin and test it.

Most of the 99 candidates `rebrew cross-import` skipped as unverified are
bodies that ARE byte-identical between the clients: the import's verify failed
only because the destination marker did not exist yet, or because the source
hardcoded a GOLDTL absolute address.  This script does the mechanical first
half — insert `// FUNCTION: GOLD 0x<dst>` + `// SIZE:` (from the GOLD
inventory) above the GOLDTL marker — then runs `rebrew test --no-promote` for
each and prints the result plus the first diff offsets.

A `RELOC`/`EXACT` row is done: re-run that file without `--no-promote` to
promote it.  A row with three differing bytes at consecutive offsets is one
absolute address: read the target's bytes there (little-endian) for the GOLD
address, and add

    // GLOBAL: GOLDTL 0x<src>
    extern char g_<src>[];
    // GLOBAL: GOLD 0x<dst>
    extern char g_<src>[];

with the literal replaced by the symbol.  See docs/TODO.md round 1413.

Usage: python3 scripts/twin_marker.py [limit]
Reads .scratch/ci_gold.json (rebrew cross-import --dry-run --shared --json).
"""
import json, re, subprocess, sys, pathlib

inv = {e['va']: e['size'] for e in json.load(open('db/inventory-Europa1400Gold.exe.json'))}
d = json.load(open('.scratch/ci_gold.json'))
rows = [r for r in d['results'] if r['action'] == 'skipped-unverified']
def ndiff(r):
    m = re.search(r'(\d+) byte diffs', r.get('message') or '')
    return int(m.group(1)) if m else 999
rows.sort(key=ndiff)
# VAs proven NOT to be shippable twins — divergent source or an unresolved
# symbol — so later runs do not re-add markers that must then be reverted.
SKIP = {
    '0x0045d950',  # fcn_00459940: symbol form swaps two FPU instructions
    '0x00468850',  # fcn_00465920: GOLD stride 0x2ec/count 0x2ff vs 0x2f4/0x3ff
    '0x00411bb0',  # fcn_00413160: GOLD stride 0x3e0 and a different bound
    '0x004e6f30',  # fcn_004e8af0: address-of global resolves to 0 for GOLD
}
done = {'0x00401000', '0x00497620', '0x0042c1c0', '0x004284a0', *SKIP}
limit = int(sys.argv[1]) if len(sys.argv) > 1 else 10
out = []
n = 0
for r in rows:
    if r['dst_va'] in done:
        continue
    if n >= limit:
        break
    dst = int(r['dst_va'], 16)
    path = pathlib.Path('src') / r['filepath']
    if not path.is_file():
        out.append((r['dst_va'], r['filepath'], 'MISSING'))
        continue
    t = path.read_text()
    if re.search(r'^// FUNCTION: GOLD ', t, re.M):
        continue  # already paired; not part of the budget
    m = re.search(r'^// FUNCTION: GOLDTL 0x[0-9a-f]+$', t, re.M)
    if not m:
        out.append((r['dst_va'], r['filepath'], 'NO_GOLDTL_MARKER'))
        continue
    size = inv.get(dst, 0)
    blk = "// FUNCTION: GOLD 0x%08x\n// SIZE: %d\n" % (dst, size)
    path.write_text(t[:m.start()] + blk + t[m.start():])
    p = subprocess.run(['rebrew', 'test', str(path), '--target', 'Europa1400Gold.exe',
                        '--va', r['dst_va'], '--no-promote'],
                       capture_output=True, text=True, timeout=180)
    txt = p.stdout + p.stderr
    line = next((l for l in txt.splitlines()
                 if l.startswith(('RELOC', 'EXACT', 'NEAR', 'SIZE_MISMATCH', 'STUB', 'error'))), '')
    diffs = [l.strip() for l in txt.splitlines() if l.strip().startswith('[')]
    if not line.startswith(('RELOC', 'EXACT')):
        # An unverified marker must not survive: revert the probe's insertion.
        subprocess.run(['git', 'checkout', '--', str(path)], timeout=120)
        line += '  (reverted)'
    out.append((r['dst_va'], r['filepath'], line, diffs[:4]))
    n += 1
for o in out:
    print(' | '.join(str(x) for x in o), flush=True)

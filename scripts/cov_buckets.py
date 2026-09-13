#!/usr/bin/env python3
"""Bucket postlink's failing layout-map entries by reference function.

`rebrew postlink` reports one number (entries that validate / total) and the
number is what gates the build, so when it refuses, this says *where* the
failures are: it applies postlink's own rule (`_map_coverage`) to every
`layout/<target>/operands.txt` and `calls.txt` entry and attributes the failures
to the reference function that contains the offset.

    python3 scripts/cov_buckets.py build/split_poc.dll

Sanity check: run it on `original/Server/server.dll` and it reports 100% - if it
does not, the rule has been reimplemented wrongly.  Two traps in doing that:
the span test compares an RVA (`value - image_base`) against
`meta.section(".rdata").va`, which is an RVA, **not** an absolute VA; and a call
entry also validates when the site sits on an E8/E9 whose two-byte contexts
match, which is what lets a correctly-linked call survive a differing target.
"""
import re, struct, sys
from pathlib import Path

ROOT = Path('.')

def secs(p):
    d = Path(p).read_bytes(); pe = struct.unpack_from('<I', d, 0x3c)[0]
    n = struct.unpack_from('<H', d, pe+6)[0]; opt = pe+24
    base = struct.unpack_from('<I', d, opt+28)[0]
    out = {}
    for i in range(n):
        o = opt + struct.unpack_from('<H', d, pe+20)[0] + i*40
        name = d[o:o+8].rstrip(b'\0').decode()
        vs, va, rs, ro = struct.unpack_from('<IIII', d, o+8)
        out[name] = (base, va, vs, ro, rs)
    return d, out

ref, R = secs('original/Server/server.dll')
bld, B = secs(sys.argv[1] if len(sys.argv) > 1 else 'build/split_poc.dll')
rbase, rva, rvs, rro, rrs = R['.rdata']; dbase, dva, dvs, dro, drs = R['.data']
spans = [(rva, rva+rvs), (dva, dva+dvs)]
tbase, tva, tvs, tro, trs = B['.text']

ops = []
for l in Path('layout/server.dll/operands.txt').read_text().splitlines():
    if l.startswith('#') or not l.strip(): continue
    a, b = l.split()
    ops.append((int(a, 16), int(b, 16)))
calls = []
for l in Path('layout/server.dll/calls.txt').read_text().splitlines():
    if l.startswith('#') or not l.strip(): continue
    p = l.split()
    calls.append((int(p[0], 16), int(p[1], 16), int(p[2], 16), int(p[3], 16)))

# reference function lookup
funcs = []
for l in Path('src/server.dll/functions.txt').read_text().splitlines():
    p = l.split()
    if len(p) >= 3 and p[0].startswith('0x'):
        funcs.append((int(p[0], 16) - (0x10001000), p[1], int(p[2])))
funcs.sort()
starts = [f[0] for f in funcs]
import bisect
def owner(off):
    i = bisect.bisect_right(starts, off) - 1
    if i < 0: return '?'
    return funcs[i][1]

bad_ops, bad_calls = {}, {}
for off, val in ops:
    cur = struct.unpack_from('<I', bld, tro+off)[0]
    if cur == val or any(lo <= cur - 0x10000000 < hi for lo, hi in spans): continue
    k = owner(off); bad_ops[k] = bad_ops.get(k, 0) + 1
for off, val, pre, suf in calls:
    pos = tro+off
    cur = struct.unpack_from('<I', bld, pos)[0]
    ctx = (pos >= 3 and pos+6 <= len(bld) and bld[pos-1] in (0xE8, 0xE9)
           and bld[pos-3:pos-1] == pre.to_bytes(2, 'big')
           and bld[pos+4:pos+6] == suf.to_bytes(2, 'big'))
    if cur == val or ctx: continue
    k = owner(off); bad_calls[k] = bad_calls.get(k, 0) + 1

tot_ops = sum(bad_ops.values()); tot_calls = sum(bad_calls.values())
print(f'failing operand entries {tot_ops}/{len(ops)}, call entries {tot_calls}/{len(calls)} '
      f'-> coverage {(len(ops)+len(calls)-tot_ops-tot_calls)/(len(ops)+len(calls))*100:.1f}%')
agg = {}
for k, v in bad_ops.items(): agg[k] = agg.get(k, 0) + v
for k, v in bad_calls.items(): agg[k] = agg.get(k, 0) + v
print(f'{"function":34s} {"entries":>8s} {"ops":>6s} {"calls":>6s}')
for k, v in sorted(agg.items(), key=lambda x: -x[1])[:30]:
    print(f'{k[:34]:34s} {v:8d} {bad_ops.get(k,0):6d} {bad_calls.get(k,0):6d}')

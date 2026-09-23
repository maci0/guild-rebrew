#!/usr/bin/env python3
"""Shape-B pass for GOLDTL->GOLD twins: turn hardcoded GOLDTL addresses into
paired GLOBAL/GOLD symbols.

For every destination VA whose file already carries `// FUNCTION: GOLD ...`
but does not match, compile it for GOLD, read the differing byte runs, and
recover both addresses of each run:

  * the candidate object at a run start holds the GOLDTL literal (no
    relocation, so the printed bytes are real), and
  * the target holds the GOLD address.

The pairing is therefore exact — no ordering heuristic.  A run is only applied
when the candidate value appears as a literal in the source, which is what
keeps an unrelated difference from being "fixed" into a wrong address.

Substitutes the literal with `g_<golctl addr>`, adds the two GLOBAL markers with
the same symbol name (a repeat of an address another file already annotates
gets a plain `extern`, because lint W021 counts a duplicate annotation), sets the
sections in rebrew-data.toml, and re-tests.  A file that still does not match is
reverted with `git checkout --` so the tree never keeps a claim that fails.

Usage: python3 scripts/twin_fix.py [limit]
Reads .scratch/ci_gold.json (rebrew cross-import --dry-run --shared --json).
"""
from __future__ import annotations

import glob
import json
import pathlib
import re
import subprocess
import sys

TARGET = 'Europa1400Gold.exe'
SRC_TARGET = 'Europa1400Gold_TL.exe'
SKIP = {
    '0x0045d950',  # fcn_00459940: symbol form swaps two FPU instructions
    '0x00468850',  # fcn_00465920: GOLD stride 0x2ec/count 0x2ff vs 0x2f4/0x3ff
    '0x00411bb0',  # fcn_00413160: GOLD stride 0x3e0 and a different bound
}
HEX_RE = re.compile(r'0x[0-9a-f]{5,7}\b')


def test(path: pathlib.Path, va: str, promote: bool = False) -> tuple[str, bytes, bytes]:
    cmd = ['rebrew', 'test', str(path), '--target', TARGET, '--va', va]
    if not promote:
        cmd.append('--no-promote')
    p = subprocess.run(cmd, capture_output=True, text=True, timeout=300)
    txt = p.stdout + p.stderr
    line = next((l for l in txt.splitlines()
                 if l.startswith(('RELOC', 'EXACT', 'NEAR', 'SIZE_MISMATCH', 'STUB', 'error'))), '')
    lines = txt.splitlines()
    ti = next((i for i, l in enumerate(lines) if l.startswith('Target (')), None)
    oi = next((i for i, l in enumerate(lines) if l.startswith('Output (')), None)
    tb = ob = b''
    if ti is not None and oi is not None:
        try:
            tb = bytes.fromhex(lines[ti + 1].strip())
            ob = bytes.fromhex(lines[oi + 1].strip())
        except (ValueError, IndexError):
            tb = ob = b''
    return line, tb, ob


def runs_in(txt_bytes: bytes) -> list[tuple[int, int, int]]:
    return []


def diff_runs(path: pathlib.Path, va: str) -> tuple[str, list[tuple[int, int, int]], bytes, bytes]:
    line, tb, ob = test(path, va)
    if tb and ob:
        p = subprocess.run(['rebrew', 'test', str(path), '--target', TARGET, '--va', va,
                            '--no-promote'], capture_output=True, text=True, timeout=300)
        offs = [int(m.group(1)) for m in re.finditer(r'^  \[\s*(\d+)\]', p.stdout + p.stderr, re.M)]
        runs: list[list[int]] = []
        for o in offs:
            if runs and o == runs[-1][-1] + 1:
                runs[-1].append(o)
            else:
                runs.append([o])
        out = []
        for r in runs:
            s = r[0]
            cv = int.from_bytes(ob[s:s + 4], 'little')
            tv = int.from_bytes(tb[s:s + 4], 'little')
            out.append((s, cv, tv))
        return line, out, tb, ob
    return line, [], b'', b''


def owners() -> dict[int, str]:
    own: dict[int, str] = {}
    for f in glob.glob('src/**/*.c', recursive=True):
        t = open(f, encoding='utf-8', errors='ignore').read()
        for m in re.finditer(r'^// GLOBAL: GOLDTL 0x([0-9a-f]+)$', t, re.M):
            own.setdefault(int(m.group(1), 16), f)
    return own


def main() -> int:
    limit = int(sys.argv[1]) if len(sys.argv) > 1 else 20
    data = json.load(open('.scratch/ci_gold.json'))
    rows = [r for r in data['results'] if r['action'] == 'skipped-unverified']
    # Skip destinations that already match (earlier rounds closed them).
    v = subprocess.run(['rebrew', 'verify', '--full', '--target', TARGET, '--json'],
                       capture_output=True, text=True, timeout=900)
    matched = set()
    try:
        for row in json.loads(v.stdout).get('results', []):
            if row.get('status') in ('EXACT', 'RELOC'):
                matched.add('0x%08x' % int(row.get('va'), 16))
    except (ValueError, TypeError):
        pass
    rows = [r for r in rows if r['dst_va'] not in matched]
    own = owners()
    done = promoted = failed = 0
    for r in rows:
        if done >= limit:
            break
        if r['dst_va'] in SKIP:
            continue
        path = pathlib.Path('src') / r['filepath']
        if not path.is_file():
            continue
        text = path.read_text()
        if not re.search(r'^// FUNCTION: GOLD ', text, re.M):
            continue
        line, runs, tb, ob = diff_runs(path, r['dst_va'])
        if line.startswith(('RELOC', 'EXACT')):
            test(path, r['dst_va'], promote=True)
            print('%-34s %s -> promoted' % (r['filepath'], r['dst_va']), flush=True)
            promoted += 1
            continue
        if not runs:
            continue
        # A run start is not always address-aligned (the first differing byte
        # can be inside the imm32), so slide a 4-byte window over the run and
        # accept the offset whose CANDIDATE value is a literal in the source —
        # that is the GOLDTL address, and the same window in the target is the
        # GOLD one.
        pairs = []
        unresolved = []
        for s, _cv, _tv in runs:
            hit = None
            for off in range(-4, 5):
                st = s + off
                if st < 0 or st + 4 > len(ob) or st + 4 > len(tb):
                    continue
                cv = int.from_bytes(ob[st:st + 4], 'little')
                tv = int.from_bytes(tb[st:st + 4], 'little')
                if tv == 0 or not (0x10000 <= tv <= 0xffffff):
                    continue
                if ('0x%x' % cv) in text:
                    hit = (cv, tv)
                    break
            if hit:
                pairs.append(hit)
            else:
                unresolved.append((s, hex(int.from_bytes(ob[s:s + 4], 'little'))))
        if not pairs:
            subprocess.run(['git', 'checkout', '--', str(path)], timeout=120)
            print('%-34s %s MANUAL %s (reverted)' % (r['filepath'], r['dst_va'], unresolved), flush=True)
            failed += 1
            continue
        seen = []
        for gl, gd in pairs:
            if gl in [p[0] for p in seen]:
                continue
            seen.append((gl, gd))
        new = text
        block = ''
        for gl, gd in seen:
            name = 'g_%x' % gl
            new = new.replace('0x%x' % gl, name)
            if own.get(gl) not in (None, str(path)):
                block += 'extern char %s[];\n' % name
            else:
                own.setdefault(gl, str(path))
                block += ('// GLOBAL: GOLDTL 0x%x\nextern char %s[];\n'
                          '// GLOBAL: GOLD 0x%x\nextern char %s[];\n' % (gl, name, gd, name))
        m = re.search(r'^// (?:FUNCTION|GLOBAL): ', new, re.M)
        new = new[:m.start()] + block + new[m.start():]
        path.write_text(new)
        for gl, gd in seen:
            for t in (TARGET, SRC_TARGET):
                for a in ('0x%x' % gl, '0x%x' % gd):
                    subprocess.run(['rebrew', 'data', '--set-section', a + '=.data',
                                    '--target', t], capture_output=True, timeout=120)
        line, _tb, _ob = test(path, r['dst_va'])
        if line.startswith(('RELOC', 'EXACT')):
            test(path, r['dst_va'], promote=True)
            print('%-34s %s FIXED %s' % (r['filepath'], r['dst_va'],
                  ' '.join('%x->%x' % p for p in seen)), flush=True)
            promoted += 1
        else:
            subprocess.run(['git', 'checkout', '--', str(path)], timeout=120)
            print('%-34s %s still %s (reverted)' % (r['filepath'], r['dst_va'], line[:40]), flush=True)
            failed += 1
        done += 1
    print('promoted %d, failed %d' % (promoted, failed))
    return 0


if __name__ == '__main__':
    raise SystemExit(main())

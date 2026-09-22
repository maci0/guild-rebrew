"""Whole-image per-function mnemonic census: our OBJECT body vs the reference.

Alignment comes from build/split_poc.map (`_sym  VA  f  obj`), which is
regenerated on every link and is exact -- unlike decoding the linked image at
the reference's VA, which is wrong whenever our object places the body at a
different internal offset (round 923, gm_AllocSpieler).

Usage: python3 .scratch/census2.py [mnemonic ...]
"""
import re, sys, struct, glob, collections, capstone

BASE = 0x10000000
REF = "original/Server/server.dll"
OBJDIR = "build/CMakeFiles/server_dll.dir/src/shared"
MAP = "build/split_poc.map"


def reftext():
    d = open(REF, 'rb').read()
    e = int.from_bytes(d[0x3c:0x40], 'little')
    nsec = int.from_bytes(d[e+6:e+8], 'little')
    off = e + 24 + int.from_bytes(d[e+20:e+22], 'little')
    for i in range(nsec):
        s = d[off+i*40:off+(i+1)*40]
        if s[:8].rstrip(b'\0') == b'.text':
            raw = int.from_bytes(s[20:24], 'little')
            rs = int.from_bytes(s[16:20], 'little')
            return int.from_bytes(s[12:16], 'little') + BASE, d[raw:raw+rs]
    raise SystemExit("no .text")


def objfuncs():
    """symbol -> (bytes, size) from every object's COFF symbol table."""
    out = {}
    for obj in glob.glob(OBJDIR + "/**/*.obj", recursive=True):
        d = open(obj, 'rb').read()
        nsec = struct.unpack_from('<H', d, 2)[0]
        psym = struct.unpack_from('<I', d, 8)[0]
        nsym = struct.unpack_from('<I', d, 12)[0]
        optsz = struct.unpack_from('<H', d, 16)[0]
        secoff = 20 + optsz
        secs = []
        for i in range(nsec):
            raw = d[secoff+i*40:secoff+(i+1)*40]
            secs.append((raw[:8].rstrip(b'\0').decode('latin1'),
                         struct.unpack_from('<I', raw, 20)[0],
                         struct.unpack_from('<I', raw, 16)[0]))
        strbase = psym + nsym * 18
        i = 0
        while i < nsym:
            o = psym + i*18
            nm = d[o:o+8]
            val, secn, typ, scl, naux = struct.unpack_from('<IhHBB', d, o+8)
            if nm[:4] == b'\0\0\0\0':
                p = strbase + struct.unpack_from('<I', d, o+4)[0]
                q = p
                while d[q]:
                    q += 1
                name = d[p:q].decode('latin1')
            else:
                name = nm.rstrip(b'\0').decode('latin1')
            if secn > 0 and typ == 0x20 and scl in (2, 3):
                sname, sroff, srsize = secs[secn-1]
                if sname.startswith('.text'):
                    out[name] = (d[sroff+val:sroff+srsize], srsize-val)
            i += 1 + naux
    return out


LIBPREFIX = ('__', '___', '_malloc', '_free', '_calloc', '_realloc', '_mem',
             '_str', '_wcs', '_set', '_get', '_except', '_global', '_initterm',
             '_onexit', '_atexit', '_controlfp', '_lock', '_unlock', '_fil',
             '_fwrite', '_fread', '_fflush', '_fclose', '_fopen', '_sprintf',
             '_vsprintf', '_printf', '_scanf', '_findfirst', '_stat', '_time',
             '_ctime', '_localtime', '_exit', '_abort', '_assert', '_crtset',
             '_adjust', '_heap', '_flsbuf', '_output', '_input', '_open', '_read',
             '_write', '_close', '_lseek', '_commit', '_isatty', '_pipe', '_dup',
             '_crt', '_RTC', '_chkstk', '_allmul', '_alldiv', '_aulldiv',
             '_allrem', '_aullrem', '_ftol', '_chkstk', '_SEH', '_Xcpt',
             '_CrtDbg', '_msize', '_expand', '_query_new', '_new', '_delete')


def is_library(sym):
    """True for a symbol whose name pattern marks stock-library code.

    A link-map VA for these names points at whatever library body the linker
    placed there, not at a game reconstruction, so comparing the reference span
    at that VA to a game object's bytes is meaningless (round 923).
    """
    return sym.startswith(LIBPREFIX)


def mapped():
    """symbol -> VA from the link map."""
    out = {}
    pat = re.compile(r'^ [0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8}) f ')
    for line in open(MAP, errors='replace'):
        m = pat.match(line)
        if m:
            out[m.group(1)] = int(m.group(2), 16)
    return out


def body(ins):
    """Instructions up to and including the last `ret`.

    Trailing jump-table and padding bytes decode as real-looking instructions;
    cutting at the last `ret` keeps them out of the counts.
    """
    idx = [n for n, i in enumerate(ins) if i.mnemonic == 'ret']
    return ins[:idx[-1]+1] if idx else ins


def main():
    va, ref = reftext()
    objs = objfuncs()
    mp = mapped()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    ca = collections.Counter()
    cb = collections.Counter()
    per = []
    used = 0
    skipped = 0
    for sym, rva in mp.items():
        if sym not in objs or is_library(sym):
            continue
        body_bytes, size = objs[sym]
        if size <= 0 or rva < va or rva - va + size > len(ref):
            continue
        ra = body(list(md.disasm(ref[rva-va:rva-va+size], rva)))
        rb = body(list(md.disasm(body_bytes[:size], rva)))
        if not ra or not rb:
            continue
        # A COFF .text section usually ends in jump-table or padding bytes that
        # decode as plausible instructions (`or dword ptr [ecx],ecx` for 0x09
        # fill, `adc ch,dh` for table bytes).  Cut at the last `ret`: those
        # trails inflated an earlier version of this census to -51 `or` and
        # -43 `adc` image-wide (round 923), and all of it was filler.
        if ra[0].mnemonic != 'push' or rb[0].mnemonic != 'push':
            skipped += 1
            continue
        used += 1
        for i in ra:
            ca[i.mnemonic] += 1
        for i in rb:
            cb[i.mnemonic] += 1
        per.append((sym, rva, size, len(ra), len(rb)))
    print("aligned %d of %d mapped / %d object functions  (%d skipped: no push prologue, or trailing bytes only)"
          % (used, len(mp), len(objs), skipped))
    print("instructions  REF %d   BLD %d   (%+d)"
          % (sum(ca.values()), sum(cb.values()), sum(cb.values())-sum(ca.values())))
    keys = sorted(set(ca) | set(cb), key=lambda k: -abs(cb.get(k, 0)-ca.get(k, 0)))
    tot = 0
    print("%-14s %6s %6s %7s" % ("mnemonic", "REF", "BLD", "delta"))
    for k in keys:
        d = cb.get(k, 0) - ca.get(k, 0)
        tot += abs(d)
        if d or k in sys.argv[1:]:
            print("%-14s %6d %6d %+7d" % (k, ca.get(k, 0), cb.get(k, 0), d))
    print("total |delta| =", tot)
    bad = [p for p in per if abs(p[4]-p[3]) > 0]
    bad.sort(key=lambda p: -abs(p[4]-p[3]))
    print("\nfunctions with an instruction-count delta: %d" % len(bad))
    for sym, rva, size, ra, rb in bad[:20]:
        print("  %+5d  %08x  %-42s REF %4d BLD %4d  %d bytes"
              % (rb-ra, rva, sym, ra, rb, size))


if __name__ == '__main__':
    main()

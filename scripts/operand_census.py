"""Operand-kind census: how each side addresses operands at aligned VAs.

Round 923 counted mnemonics; round 924 found a real bug by reading *operands*.
This counts operand kind (REG / MEM / ABS / IMM) at addresses where both sides
emit the same mnemonic.

Read the output with care: once a function has drifted, addresses coincide but
instructions do not correspond, so mismatches after the first divergence are
mostly noise.  The signal is in the first few VAs of each function -- which is
exactly where round 924's bad push sat.

Usage: python3 scripts/operand_census.py [function ...]
"""
import re, sys, capstone

BASE = 0x10000000
REF = "original/Server/server.dll"
BLD = "build/server.dll"
OBJDIR = "build/CMakeFiles/server_dll.dir/src/shared"
MAP = "build/split_poc.map"

# the largest residue carriers, from the gate's own attribution
DEFAULT = ['_gm_AllocSpieler', '_CrashDumpUnhandledExceptionFilter@4',
           '_cm_ExSellObjekt', '_ls_LoadBuildingEntityState', '_cm_ExCopyEntityData',
           '_gv_ExAllocGraveyardWorker', '_ServerMainThread@4', '_gm_AllocGebaeude',
           '_vfs_OpenStream', '_gm_FindNextFilteredEntity', '_ahm_ExAllocAlchemist',
           '_gm_CheckInventoryCapacity', '_m_AllocTracked', '_srv_LoadBuf']


def textof(path):
    d = open(path, 'rb').read()
    e = int.from_bytes(d[0x3c:0x40], 'little')
    n = int.from_bytes(d[e+6:e+8], 'little')
    off = e + 24 + int.from_bytes(d[e+20:e+22], 'little')
    for i in range(n):
        s = d[off+i*40:off+(i+1)*40]
        if s[:8].rstrip(b'\0') == b'.text':
            raw = int.from_bytes(s[20:24], 'little')
            rs = int.from_bytes(s[16:20], 'little')
            return int.from_bytes(s[12:16], 'little') + BASE, d[raw:raw+rs]
    raise SystemExit("no .text")


def mapva():
    out = {}
    pat = re.compile(r'^ [0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8}) f ')
    for line in open(MAP, errors='replace'):
        m = pat.match(line)
        if m:
            out[m.group(1)] = int(m.group(2), 16)
    return out


def kind(ins):
    for op in ins.operands:
        if op.type == capstone.x86.X86_OP_IMM:
            return 'IMM'
        if op.type == capstone.x86.X86_OP_MEM:
            return 'ABS' if (op.mem.base == 0 and op.mem.index == 0) else 'MEM'
        if op.type == capstone.x86.X86_OP_REG:
            return 'REG'
    return '?'


def main():
    va, ref = textof(REF)
    _, bld = textof(BLD)
    mp = mapva()
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    md.detail = True
    for sym in (sys.argv[1:] or DEFAULT):
        if sym not in mp:
            print("%-34s not in %s" % (sym, MAP))
            continue
        rva = mp[sym]
        nxt = min([v for v in mp.values() if v > rva], default=rva + 4096)
        size = nxt - rva
        da = {i.address: i for i in md.disasm(ref[rva-va:rva-va+size], rva)}
        db = {i.address: i for i in md.disasm(bld[rva-va:rva-va+size], rva)}
        mism = []
        for a, i in sorted(da.items()):
            j = db.get(a)
            if not j or i.mnemonic != j.mnemonic:
                continue
            if kind(i) != kind(j):
                mism.append((a, i.mnemonic, i.op_str, j.op_str, kind(i), kind(j)))
        print("%-34s %d operand-kind mismatch(es) at aligned VAs" % (sym, len(mism)))
        for m in mism[:6]:
            print("      %08x %-7s REF %-26s BLD %-26s (%s vs %s)" % m)


if __name__ == '__main__':
    main()

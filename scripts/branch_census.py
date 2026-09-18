"""Compare branch TARGETS between the reference and our build, per function.

Why (rounds 970-971): a stream comparison compares `jle` to `jle` and sees a match,
so a divergence consisting only of WHERE the branches go is invisible to it and to
`rebrew diff`. Measured on gv_ExAllocGraveyardWorker: indices 99-118 match
instruction-for-instruction, yet three branches target different addresses for the
byte-identical epilogue -- codegen-walls section 2's epilogue-merge mechanism, visible
only by comparing the jump operands.

A carrier with many target-differing branches is a block-placement story; one with
zero is an instruction-form story. That partition is worth having before choosing a
target.

Usage: python3 scripts/branch_census.py [function ...]
"""
import re, sys, capstone

BASE = 0x10000000
REF = "original/Server/server.dll"
BLD = "build/server.dll"
MAP = "build/split_poc.map"

DEFAULT = ['_gm_AllocSpieler', '_ServerMainThread@4', '_cm_ExSellObjekt',
           '_CrashDumpUnhandledExceptionFilter@4', '_cm_ExCopyEntityData',
           '_gm_AllocGebaeude', '_gv_ExAllocGraveyardWorker',
           '_gm_FindNextFilteredEntity', '_cm_ProcessCommandQueue',
           '_ls_LoadBuildingEntityState', '_gm_CheckInventoryCapacity',
           '_vfs_OpenStream', '_ahm_ExAllocAlchemist', '_m_AllocTracked',
           '_srv_LoadBuf', '_gm_ObjectsAvailble', '_vfs_ReadCompressed',
           '_cm_ExProdObjekt', '_gm_CalculateProductionValue']


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


def main():
    va, ref = textof(REF)
    _, bld = textof(BLD)
    mp = {}
    pat = re.compile(r'^ [0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8}) f ')
    for line in open(MAP, errors='replace'):
        m = pat.match(line)
        if m:
            mp[m.group(1)] = int(m.group(2), 16)
    md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
    print("%-38s %8s %8s  %s" % ("carrier", "branches", "targetdiff", "first"))
    for sym in (sys.argv[1:] or DEFAULT):
        if sym not in mp:
            continue
        V = mp[sym]
        nxt = min([x for x in mp.values() if x > V], default=V + 4096)
        S = nxt - V
        a = list(md.disasm(ref[V-va:V-va+S], V))
        b = list(md.disasm(bld[V-va:V-va+S], V))
        nd = 0
        first = None
        for x, y in zip(a, b):
            if x.mnemonic.startswith('j') and x.mnemonic == y.mnemonic and x.op_str != y.op_str:
                nd += 1
                if first is None:
                    first = '%08x %s %s | %s' % (x.address, x.mnemonic, x.op_str, y.op_str)
        nb = sum(1 for i in a if i.mnemonic.startswith('j'))
        print("%-38s %8d %8d  %s" % (sym, nb, nd, first or '-'))


if __name__ == '__main__':
    main()

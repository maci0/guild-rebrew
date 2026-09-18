"""Find each residue carrier's FAULT address, not its symptom.

Why (round 979): the lowest differing BYTE is usually a branch disposal or a
displaced operand -- a symptom.  Its address frequently has no doc entry while
the real fault (the first instruction whose mnemonic/operand/size actually
disagrees between the two streams) is documented in detail.  Looking up the
symptom makes a closed carrier read as open work; ServerMainThread cost a round
that way (symptom 0x10009767 had 4 TODO hits, fault 0x100097f4 has shapes 126).

Method: walk both instruction streams from the function entry, aligning on
address; report the first index where (mnemonic, op_str, size) differs, and its
address on the REFERENCE side.

Usage: python3 scripts/fault_address.py [symbol ...]
"""
import capstone, re, sys
BASE = 0x10000000


def textof(p):
    d = open(p, 'rb').read()
    e = int.from_bytes(d[0x3c:0x40], 'little')
    n = int.from_bytes(d[e+6:e+8], 'little')
    off = e + 24 + int.from_bytes(d[e+20:e+22], 'little')
    for i in range(n):
        s = d[off+i*40:off+(i+1)*40]
        if s[:8].rstrip(b'\0') == b'.text':
            return (int.from_bytes(s[12:16], 'little') + BASE,
                    d[int.from_bytes(s[20:24], 'little'):][:int.from_bytes(s[16:20], 'little')])


va, ref = textof('original/Server/server.dll')
_, bld = textof('build/server.dll')
mp = {}
pat = re.compile(r'^ [0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8}) f ')
for line in open('build/split_poc.map', errors='replace'):
    m = pat.match(line)
    if m:
        mp[m.group(1)] = int(m.group(2), 16)

md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
CAR = ['_gm_AllocSpieler', '_CrashDumpUnhandledExceptionFilter@4', '_cm_ExSellObjekt',
       '_ls_LoadBuildingEntityState', '_cm_ExCopyEntityData', '_gv_ExAllocGraveyardWorker',
       '_ServerMainThread@4', '_gm_AllocGebaeude', '_vfs_OpenStream', '_gm_FindNextFilteredEntity',
       '_ahm_ExAllocAlchemist', '_gm_CheckInventoryCapacity', '_m_AllocTracked', '_srv_LoadBuf',
       '_gm_ObjectsAvailble', '_vfs_ReadCompressed', '_cm_ExProdObjekt', '_cm_ProcessCommandQueue',
       '_gm_CalculateProductionValue']


def firstbyte(V, S):
    for k in range(S):
        if ref[V-va+k] != bld[V-va+k]:
            return k
    return None


print("%-38s %-12s %-12s %s" % ("carrier", "symptom", "FAULT", "fault instruction"))
for s in (sys.argv[1:] or CAR):
    if s not in mp:
        print('%-38s not in map' % s)
        continue
    V = mp[s]
    nxt = min([x for x in mp.values() if x > V], default=V+4096)
    S = nxt - V
    a = list(md.disasm(ref[V-va:V-va+S], V))
    b = list(md.disasm(bld[V-va:V-va+S], V))
    fb = firstbyte(V, S)
    sym = "0x%x" % (V+fb) if fb is not None else "-"
    # fault: first structurally different instruction, walking both streams by address
    fault = None
    ai, bi = 0, 0
    while ai < len(a) and bi < len(b):
        x, y = a[ai], b[bi]
        if (x.mnemonic, x.op_str, x.size) != (y.mnemonic, y.op_str, y.size):
            fault = x
            break
        ai += 1
        bi += 1
    if fault is None:
        print("%-38s %-12s %-12s %s" % (s, sym, "-", "(streams agree to end)"))
    else:
        print("%-38s %-12s 0x%-10x %s %s" % (s, sym, fault.address, fault.mnemonic, fault.op_str))

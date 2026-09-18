"""Read each carrier's ACTUAL first divergence, by lowest differing byte.

Why (round 975): a positional stream comparison desynchronises at the first
divergence, so every index after it pairs unrelated instructions (measure-traps
section 13).  And the branch-target census (scripts/branch_census.py) classifies by
the first BRANCH whose target differs, which is a proxy for the first divergence --
it filed m_AllocTracked under register-role rotation when the real difference is two
prologue instructions swapped.

This takes the lowest byte offset where the two images differ, then finds the
instruction covering that byte on EACH side independently.  No alignment assumption.

Usage: python3 scripts/first_divergence.py [function ...]
"""
import capstone, re, sys
BASE=0x10000000
def textof(p):
    d=open(p,'rb').read()
    e=int.from_bytes(d[0x3c:0x40],'little'); n=int.from_bytes(d[e+6:e+8],'little')
    off=e+24+int.from_bytes(d[e+20:e+22],'little')
    for i in range(n):
        s=d[off+i*40:off+(i+1)*40]
        if s[:8].rstrip(b'\0')==b'.text':
            return int.from_bytes(s[12:16],'little')+BASE, d[int.from_bytes(s[20:24],'little'):][:int.from_bytes(s[16:20],'little')]
va,ref=textof('original/Server/server.dll'); _,bld=textof('build/server.dll')
mp={}
pat=re.compile(r'^ [0-9a-f]{4}:[0-9a-f]{8}\s+(\S+)\s+([0-9a-f]{8}) f ')
for line in open('build/split_poc.map',errors='replace'):
    m=pat.match(line)
    if m: mp[m.group(1)]=int(m.group(2),16)
md=capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_32)
CAR=['_gm_AllocSpieler','_CrashDumpUnhandledExceptionFilter@4','_cm_ExSellObjekt',
 '_ls_LoadBuildingEntityState','_cm_ExCopyEntityData','_gv_ExAllocGraveyardWorker',
 '_ServerMainThread@4','_gm_AllocGebaeude','_vfs_OpenStream','_gm_FindNextFilteredEntity',
 '_ahm_ExAllocAlchemist','_gm_CheckInventoryCapacity','_m_AllocTracked','_srv_LoadBuf',
 '_gm_ObjectsAvailble','_vfs_ReadCompressed','_cm_ExProdObjekt','_cm_ProcessCommandQueue',
 '_gm_CalculateProductionValue']
# raw-byte first difference is the unambiguous signal
def firstbyte(v,S):
    for k in range(S):
        if ref[v-va+k]!=bld[v-va+k]: return k
    return None
print("%-38s %7s %7s  %s"%("carrier","REFn","BLDn","kind at first differing BYTE"))
for s in (sys.argv[1:] or CAR):
    if s not in mp:
        print('%-38s not in map' % s); continue
    V=mp[s]; nxt=min([x for x in mp.values() if x>V], default=V+4096); S=nxt-V
    a=list(md.disasm(ref[V-va:V-va+S],V)); b=list(md.disasm(bld[V-va:V-va+S],V))
    fb=firstbyte(V,S)
    # which REF instruction covers byte fb, and which BLD instruction covers it
    ri=next((i for i in a if i.address<=V+fb<i.address+i.size), None)
    bi=next((i for i in b if i.address<=V+fb<i.address+i.size), None)
    kind='?'
    if ri and bi:
        if ri.mnemonic==bi.mnemonic and ri.op_str==bi.op_str: kind='same insn (encoding differs)'
        elif ri.mnemonic==bi.mnemonic: kind='same mnemonic, operand differs'
        elif ri.address==bi.address: kind='different mnemonic at same addr'
        else: kind='streams already desynced'
    print("%-38s %7d %7d  +0x%-5x %s | %s  [%s]"%(s,len(a),len(b),fb,
        (ri.mnemonic+' '+ri.op_str) if ri else '?', (bi.mnemonic+' '+bi.op_str) if bi else '?', kind))

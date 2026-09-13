#!/usr/bin/env python3
"""Reference real body vs ours, windowed correctly.

A function's out-of-line jump table / case map live after its code but inside its
object, so if our real COMDAT body is shorter than the reference's, the table sits
early and every 4-byte relocated entry in it moves (round 184: vfs_OpenStream's 8
bytes were worth 36).  The reference window must run to the NEXT function's VA --
the metadata `size` covers only the code and stops before the table, which made the
first version of this report a bogus +34 for an already-fixed function.
"""
import re, subprocess, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1] / "scripts"))
import instr_diff as ID
from split_coff import Coff
H = {
 0x10002770:("CrashDump","src/server.dll/Units/Error/Error_c/CrashDumpUnhandledExceptionFilter.c","_CrashDumpUnhandledExceptionFilter@4"),
 0x10006580:("m_AllocTracked","src/server.dll/Units/m_alloc/m_alloc_c/m_AllocTracked.c","_m_AllocTracked"),
 0x10008a90:("vfs_ReadCompressed","src/server.dll/Units/vfs/vfs_ReadCompressed.c","_vfs_ReadCompressed"),
 0x10009020:("vfs_OpenStream","src/server.dll/Units/vfs/vfs_c/vfs_OpenStream.c","_vfs_OpenStream"),
 0x100093a0:("ServerMainThread","src/server.dll/DieGildeAddOnServer/server_c/ServerMainThread.c","_ServerMainThread@4"),
 0x1000a570:("srv_LoadBuf","src/server.dll/DieGildeAddOnServer/server_c/srv_LoadBuf.c","_srv_LoadBuf"),
 0x1000aac0:("cm_ProcessCommandQueue","src/server.dll/DieGildeAddOnServer/server_c/cm_ProcessCommandQueue.c","_cm_ProcessCommandQueue"),
 0x1000bdf0:("ahm_ExAllocAlchemist","src/server.dll/DieGildeAddOn/game/alchemistry_logic_c/ahm_ExAllocAlchemist.c","_ahm_ExAllocAlchemist"),
 0x1000d930:("cm_ExSellObjekt","src/server.dll/DieGildeAddOn/command/command_c/cm_ExSellObjekt.c","_cm_ExSellObjekt"),
 0x1000e140:("cm_ExProdObjekt","src/server.dll/DieGildeAddOn/command/command_c/cm_ExProdObjekt.c","_cm_ExProdObjekt"),
 0x1000ec00:("cm_ExCopyEntityData","src/server.dll/DieGildeAddOn/command/command_c/cm_ExCopyEntityData.c","_cm_ExCopyEntityData"),
 0x10011bf0:("gv_ExAllocGraveyardWorker","src/server.dll/DieGildeAddOn/game/friedhof_logic_c/gv_ExAllocGraveyardWorker.c","_gv_ExAllocGraveyardWorker"),
 0x100128f0:("ls_LoadBuildingEntityState","src/server.dll/DieGildeAddOn/loadsave/loadsave_c/ls_LoadBuildingEntityState.c","_ls_LoadBuildingEntityState"),
 0x10015f70:("gm_ObjectsAvailble","src/server.dll/DieGildeAddOn/game/spiel_c/gm_ObjectsAvailble.c","_gm_ObjectsAvailble"),
 0x10016f80:("gm_FindNextFilteredEntity","src/server.dll/DieGildeAddOn/game/spiel_dumpD.c","_gm_FindNextFilteredEntity"),
 0x100174d0:("gm_AllocGebaeude","src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocGebaeude.c","_gm_AllocGebaeude"),
 0x10018850:("gm_AllocSpieler","src/server.dll/DieGildeAddOn/game/spiel_c/gm_AllocSpieler.c","_gm_AllocSpieler"),
 0x10019ed0:("gm_CheckInventoryCapacity","src/server.dll/DieGildeAddOn/game/spiel622.c","_gm_CheckInventoryCapacity"),
}
rows=[]
for ln in open("db/server.dll_functions.csv"):
    p=ln.strip().split("|")
    if len(p)>=5:
        try: rows.append((int(p[0],16),int(p[4]),p[1]))
        except ValueError: pass
rows.sort()
def nextva(va):
    for a,sz,_n in rows:
        if a>va: return a
    return va+sz
secs=ID.sections(ID.REFERENCE); tb=ID.REFERENCE.read_bytes()
print(f"{'function':30s} {'ref-real':>8s} {'our-real':>8s} {'delta':>6s}")
for va,(name,src,sym) in sorted(H.items()):
    end=nextva(va)
    off=secs[".text"][2]+(va-secs[".text"][0]-ID.IMAGE_BASE)
    rb=tb[off:off+(end-va)]
    e=len(rb)
    while e>0 and rb[e-1]==0x90: e-=1
    refreal=e
    out=subprocess.run([".venv/bin/python","-u","scripts/probe_function.py","--va",hex(va),
        "--file",src],capture_output=True,text=True).stdout
    m=re.search(r"object: (\S+)",out)
    if not m: print(f"{name:30s}  probe failed"); continue
    c=Coff(Path(m.group(1)).read_bytes()); our=0
    for si,s in enumerate(c.sections):
        if not s["name"].startswith(b".text"): continue
        if next((x["name"] for x in c.symbols if x and x["section"]==si+1 and x["storage_class"]==2),None)!=sym: continue
        b=bytes(c.section_body(si)); e=len(b)
        while e>0 and b[e-1]==0x90: e-=1
        our=e
    flag="   <-- length case" if our!=refreal else ""
    print(f"{name:30s} {refreal:8d} {our:8d} {our-refreal:+6d}{flag}")

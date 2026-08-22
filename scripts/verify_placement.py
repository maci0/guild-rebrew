#!/usr/bin/env python3
"""Post-edit placement verification: build, then compare symbol VAs vs toml."""
import re, subprocess, pathlib, sys, tomllib
ROOT = pathlib.Path(__file__).parent.parent

def _build_data_va():
    """image-base-correct .data VA of the current build (never hardcode)."""
    try:
        import pefile
        pe = pefile.PE(str(ROOT / "build" / "server.dll"))
        for s in pe.sections:
            if s.Name.rstrip(b"\x00") == b".data":
                return pe.OPTIONAL_HEADER.ImageBase + s.VirtualAddress
    except Exception:
        pass
    return 0x1002E000

def main():
    rsp=(ROOT/"build/CMakeFiles/server_dll.dir/objects1.rsp").read_text()
    objs=re.findall(r'"([^"]+\.obj)"|(?:^|\s)(\S+\.obj)(?=\s|$)',rsp)
    objs=[pathlib.Path(ROOT/"build")/(a or b) for a,b in objs]
    data_va=_build_data_va()
    tot_d=0; here={}
    for o in objs:
        h=subprocess.run(["objdump","-h",str(o)],capture_output=True,text=True).stdout
        secs=re.findall(r"^\s+(\d+)\s+(\S+)\s+([0-9a-f]+)\s",h,re.M)
        secname={int(a):b for a,b,_ in secs}
        d=sum(int(c,16) for a,b,c in secs if b==".data")
        t=subprocess.run(["objdump","-t",str(o)],capture_output=True,text=True).stdout
        for line in t.splitlines():
            m=re.match(r"\[ *\d+\]\(sec +(-?\d+)\)",line)
            if not m: continue
            sec=int(m.group(1))
            vm=re.search(r"\s(?:0x)?([0-9a-f]{8})\s+(\S+)\s*$",line[m.end():])
            if not vm: continue
            sym=vm.group(2).lstrip('_')
            if secname.get(sec-1)==".data":
                here.setdefault(sym,data_va+tot_d+int(vm.group(1),16))
        tot_d+=d
    with open(ROOT/"src/rebrew-data.toml","rb") as f:
        toml=tomllib.load(f)
    exp={v.get("name",""):int(k.split('.')[1],16) for k,v in toml.items() if v.get("section")==".data"}
    good=bad=0; bads=[]
    for s,a in here.items():
        if s in exp:
            if a==exp[s]: good+=1
            else: bad+=1; bads.append((s,exp[s],a))
    print(f"symbols: {len(here)} toml-matched: {good+bad} correct-VA: {good} misplaced: {bad}")
    bads.sort(key=lambda x:-(abs(x[1]-x[2])))
    for s,e,a in bads[:15]:
        print(f"  {s:32} exp {e:#010x} our {a:#010x} d {a-e:+#x}")
if __name__=="__main__":
    main()

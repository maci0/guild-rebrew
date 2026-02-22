; pretty disassembly for Init
; VA: 0x10009320..0x10009350 (48 bytes)
10009320  8B4C2404          mov ecx,[esp+0x4]
10009324  8D442404          lea eax,[esp+0x4]
10009328  50                push eax
10009329  6A00              push dword 0x0
1000932B  51                push ecx
1000932C  68A0930010        push dword 0x100093a0
10009331  6A00              push dword 0x0
10009333  6A00              push dword 0x0
10009335  FF1550400210      call dword near [0x10024050]
1000933B  33D2              xor edx,edx
1000933D  A394407611        mov [0x11764094],eax
10009342  85C0              test eax,eax
10009344  0F95C2            setnz dl
10009347  8BC2              mov eax,edx
10009349  C3                ret
1000934A  90                nop
1000934B  90                nop
1000934C  90                nop
1000934D  90                nop
1000934E  90                nop
1000934F  90                nop

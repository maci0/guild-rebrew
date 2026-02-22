; pretty disassembly for Exit
; VA: 0x10009350..0x10009394 (68 bytes)
10009350  A194407611        mov eax,[0x11764094]
10009355  85C0              test eax,eax
10009357  743A              jz 0x10009393
10009359  56                push esi
1000935A  8B3558400210      mov esi,[0x10024058]
10009360  C705804603100100  mov dword [0x10034680],0x1
         -0000
1000936A  6A0A              push dword 0xa
1000936C  FF                db 0xff
1000936D  D6                salc
1000936E  A180460310        mov eax,[0x10034680]
10009373  85C0              test eax,eax
10009375  75F3              jnz 0x1000936a
10009377  A194407611        mov eax,[0x11764094]
1000937C  6A00              push dword 0x0
1000937E  50                push eax
1000937F  FF1554400210      call dword near [0x10024054]
10009385  8B0D94407611      mov ecx,[0x11764094]
1000938B  51                push ecx
1000938C  FF1510400210      call dword near [0x10024010]
10009392  5E                pop esi
10009393  C3                ret

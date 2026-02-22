; pretty disassembly for fcn_10006f40
; VA: 0x10006f40..0x10006fa6 (102 bytes)
10006F40  8B542404          mov edx,[esp+0x4]
10006F44  56                push esi
10006F45  B91E010000        mov ecx,0x11e
10006F4A  33F6              xor esi,esi
10006F4C  8D828C000000      lea eax,[edx+0x8c]
10006F52  668930            mov [eax],si
10006F55  83C004            add eax,0x4
10006F58  49                dec ecx
10006F59  75F7              jnz 0x10006f52
10006F5B  8D8280090000      lea eax,[edx+0x980]
10006F61  B91E000000        mov ecx,0x1e
10006F66  668930            mov [eax],si
10006F69  83C004            add eax,0x4
10006F6C  49                dec ecx
10006F6D  75F7              jnz 0x10006f66
10006F6F  8D82740A0000      lea eax,[edx+0xa74]
10006F75  B913000000        mov ecx,0x13
10006F7A  668930            mov [eax],si
10006F7D  83C004            add eax,0x4
10006F80  49                dec ecx
10006F81  75F7              jnz 0x10006f7a
10006F83  89B2A4160000      mov [edx+0x16a4],esi
10006F89  89B2A0160000      mov [edx+0x16a0],esi
10006F8F  89B2A8160000      mov [edx+0x16a8],esi
10006F95  89B298160000      mov [edx+0x1698],esi
10006F9B  66C7828C04000001  mov word [edx+0x48c],0x1
         -00
10006FA4  5E                pop esi
10006FA5  C3                ret

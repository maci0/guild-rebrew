; pretty disassembly for fcn_10002640
; VA: 0x10002640..0x10002762 (290 bytes)
10002640  81EC08010000      sub esp,0x108
10002646  53                push ebx
10002647  8A9C2414010000    mov bl,[esp+0x114]
1000264E  55                push ebp
1000264F  8BAC2414010000    mov ebp,[esp+0x114]
10002656  F6C301            test bl,0x1
10002659  56                push esi
1000265A  0F84A1000000      jz 0x10002701
10002660  8B942420010000    mov edx,[esp+0x120]
10002667  33C0              xor eax,eax
10002669  B978700210        mov ecx,0x10027078
1000266E  3B11              cmp edx,[ecx]
10002670  740E              jz 0x10002680
10002672  83C104            add ecx,0x4
10002675  40                inc eax
10002676  81F984700210      cmp ecx,0x10027084
1000267C  7CF0              jl 0x1000266e
1000267E  EB35              jmp 0x100026b5
10002680  C1E005            shl eax,byte 0x5
10002683  0584700210        add eax,0x10027084
10002688  50                push eax
10002689  6800617611        push dword 0x11766100
1000268E  8D442418          lea eax,[esp+0x18]
10002692  68FC700210        push dword 0x100270fc
10002697  50                push eax
10002698  E8FC7B0100        call 0x1001a299
1000269D  8D4C2420          lea ecx,[esp+0x20]
100026A1  68F8700210        push dword 0x100270f8
100026A6  51                push ecx
100026A7  E8DA7B0100        call 0x1001a286
100026AC  8BF0              mov esi,eax
100026AE  83C418            add esp,0x18
100026B1  85F6              test esi,esi
100026B3  7531              jnz 0x100026e6
100026B5  68E8700210        push dword 0x100270e8
100026BA  6800617611        push dword 0x11766100
100026BF  8D542418          lea edx,[esp+0x18]
100026C3  68FC700210        push dword 0x100270fc
100026C8  52                push edx
100026C9  E8CB7B0100        call 0x1001a299
100026CE  8D442420          lea eax,[esp+0x20]
100026D2  68F8700210        push dword 0x100270f8
100026D7  50                push eax
100026D8  E8A97B0100        call 0x1001a286
100026DD  8BF0              mov esi,eax
100026DF  83C418            add esp,0x18
100026E2  85F6              test esi,esi
100026E4  741B              jz 0x10002701
100026E6  56                push esi
100026E7  55                push ebp
100026E8  E81A7B0100        call 0x1001a207
100026ED  56                push esi
100026EE  68E4700210        push dword 0x100270e4
100026F3  E80F7B0100        call 0x1001a207
100026F8  56                push esi
100026F9  E88C7A0100        call 0x1001a18a
100026FE  83C414            add esp,0x14
10002701  F6C304            test bl,0x4
10002704  7410              jz 0x10002716
10002706  8B3504400210      mov esi,[0x10024004]
1000270C  55                push ebp
1000270D  FF                db 0xff
1000270E  D6                salc
1000270F  68E4700210        push dword 0x100270e4
10002714  FF                db 0xff
10002715  D6                salc
10002716  F6C308            test bl,0x8
10002719  743D              jz 0x10002758
1000271B  57                push edi
1000271C  8D4C2410          lea ecx,[esp+0x10]
10002720  6A00              push dword 0x0
10002722  51                push ecx
10002723  8BFD              mov edi,ebp
10002725  83C9FF            or ecx,0xffffffffffffffff
10002728  33C0              xor eax,eax
1000272A  8B1504627611      mov edx,[0x11766204]
10002730  F2AE              repne scasb
10002732  8B35C0400210      mov esi,[0x100240c0]
10002738  F7D1              not ecx
1000273A  49                dec ecx
1000273B  51                push ecx
1000273C  55                push ebp
1000273D  52                push edx
1000273E  FF                db 0xff
1000273F  D6                salc
10002740  8B0D04627611      mov ecx,[0x11766204]
10002746  8D442410          lea eax,[esp+0x10]
1000274A  6A00              push dword 0x0
1000274C  50                push eax
1000274D  6A01              push dword 0x1
1000274F  68E4700210        push dword 0x100270e4
10002754  51                push ecx
10002755  FF                db 0xff
10002756  D6                salc
10002757  5F                pop edi
10002758  5E                pop esi
10002759  5D                pop ebp
1000275A  5B                pop ebx
1000275B  81C408010000      add esp,0x108
10002761  C3                ret

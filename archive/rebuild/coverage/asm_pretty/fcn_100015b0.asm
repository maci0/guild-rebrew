; pretty disassembly for fcn_100015b0
; VA: 0x100015b0..0x1000185f (685 bytes)
100015B0  53                push ebx
100015B1  8B5C2408          mov ebx,[esp+0x8]
100015B5  55                push ebp
100015B6  56                push esi
100015B7  85DB              test ebx,ebx
100015B9  57                push edi
100015BA  0F8493020000      jz 0x10001853
100015C0  8B731C            mov esi,[ebx+0x1c]
100015C3  85F6              test esi,esi
100015C5  0F8488020000      jz 0x10001853
100015CB  8B6C2418          mov ebp,[esp+0x18]
100015CF  83FD04            cmp ebp,0x4
100015D2  0F8F7B020000      jg 0x10001853
100015D8  85ED              test ebp,ebp
100015DA  0F8C73020000      jl 0x10001853
100015E0  8B430C            mov eax,[ebx+0xc]
100015E3  85C0              test eax,eax
100015E5  0F845F020000      jz 0x1000184a
100015EB  833B00            cmp dword [ebx],0x0
100015EE  750B              jnz 0x100015fb
100015F0  8B4304            mov eax,[ebx+0x4]
100015F3  85C0              test eax,eax
100015F5  0F854F020000      jnz 0x1000184a
100015FB  8B4604            mov eax,[esi+0x4]
100015FE  3D9A020000        cmp eax,0x29a
10001603  7509              jnz 0x1000160e
10001605  83FD04            cmp ebp,0x4
10001608  0F853C020000      jnz 0x1000184a
1000160E  8B4B10            mov ecx,[ebx+0x10]
10001611  85C9              test ecx,ecx
10001613  7512              jnz 0x10001627
10001615  A1F0940210        mov eax,[0x100294f0]
1000161A  5F                pop edi
1000161B  5E                pop esi
1000161C  894318            mov [ebx+0x18],eax
1000161F  5D                pop ebp
10001620  B8FBFFFFFF        mov eax,0xfffffffb
10001625  5B                pop ebx
10001626  C3                ret
10001627  8B4E20            mov ecx,[esi+0x20]
1000162A  83F82A            cmp eax,0x2a
1000162D  891E              mov [esi],ebx
1000162F  894C2414          mov [esp+0x14],ecx
10001633  896E20            mov [esi+0x20],ebp
10001636  7578              jnz 0x100016b0
10001638  8B4E28            mov ecx,[esi+0x28]
1000163B  8B467C            mov eax,[esi+0x7c]
1000163E  C1E10C            shl ecx,byte 0xc
10001641  81E900780000      sub ecx,0x7800
10001647  48                dec eax
10001648  D1F8              sar eax,0x0
1000164A  83F803            cmp eax,0x3
1000164D  7605              jna 0x10001654
1000164F  B803000000        mov eax,0x3
10001654  C1E006            shl eax,byte 0x6
10001657  0BC8              or ecx,eax
10001659  8B4664            mov eax,[esi+0x64]
1000165C  85C0              test eax,eax
1000165E  7403              jz 0x10001663
10001660  83C920            or ecx,0x20
10001663  8BC1              mov eax,ecx
10001665  33D2              xor edx,edx
10001667  BF1F000000        mov edi,0x1f
1000166C  C7460471000000    mov dword [esi+0x4],0x71
10001673  F7F7              div edi
10001675  2BCA              sub ecx,edx
10001677  03CF              add ecx,edi
10001679  51                push ecx
1000167A  56                push esi
1000167B  E8E0010000        call 0x10001860
10001680  8B4664            mov eax,[esi+0x64]
10001683  83C408            add esp,0x8
10001686  85C0              test eax,eax
10001688  741F              jz 0x100016a9
1000168A  8B5330            mov edx,[ebx+0x30]
1000168D  C1EA10            shr edx,byte 0x10
10001690  52                push edx
10001691  56                push esi
10001692  E8C9010000        call 0x10001860
10001697  8B4330            mov eax,[ebx+0x30]
1000169A  25FFFF0000        and eax,0xffff
1000169F  50                push eax
100016A0  56                push esi
100016A1  E8BA010000        call 0x10001860
100016A6  83C410            add esp,0x10
100016A9  C7433001000000    mov dword [ebx+0x30],0x1
100016B0  8B4614            mov eax,[esi+0x14]
100016B3  85C0              test eax,eax
100016B5  741E              jz 0x100016d5
100016B7  53                push ebx
100016B8  E8D3010000        call 0x10001890
100016BD  8B4310            mov eax,[ebx+0x10]
100016C0  83C404            add esp,0x4
100016C3  85C0              test eax,eax
100016C5  7533              jnz 0x100016fa
100016C7  C74620FFFFFFFF    mov dword [esi+0x20],0xffffffff
100016CE  5F                pop edi
100016CF  5E                pop esi
100016D0  5D                pop ebp
100016D1  33C0              xor eax,eax
100016D3  5B                pop ebx
100016D4  C3                ret
100016D5  8B4304            mov eax,[ebx+0x4]
100016D8  85C0              test eax,eax
100016DA  751E              jnz 0x100016fa
100016DC  3B6C2414          cmp ebp,[esp+0x14]
100016E0  7F18              jg 0x100016fa
100016E2  83FD04            cmp ebp,0x4
100016E5  7413              jz 0x100016fa
100016E7  8B0DF0940210      mov ecx,[0x100294f0]
100016ED  5F                pop edi
100016EE  5E                pop esi
100016EF  894B18            mov [ebx+0x18],ecx
100016F2  5D                pop ebp
100016F3  B8FBFFFFFF        mov eax,0xfffffffb
100016F8  5B                pop ebx
100016F9  C3                ret
100016FA  8B4604            mov eax,[esi+0x4]
100016FD  8B4B04            mov ecx,[ebx+0x4]
10001700  3D9A020000        cmp eax,0x29a
10001705  7517              jnz 0x1000171e
10001707  85C9              test ecx,ecx
10001709  7417              jz 0x10001722
1000170B  8B15F0940210      mov edx,[0x100294f0]
10001711  5F                pop edi
10001712  5E                pop esi
10001713  895318            mov [ebx+0x18],edx
10001716  5D                pop ebp
10001717  B8FBFFFFFF        mov eax,0xfffffffb
1000171C  5B                pop ebx
1000171D  C3                ret
1000171E  85C9              test ecx,ecx
10001720  751A              jnz 0x1000173c
10001722  8B4E6C            mov ecx,[esi+0x6c]
10001725  85C9              test ecx,ecx
10001727  7513              jnz 0x1000173c
10001729  85ED              test ebp,ebp
1000172B  0F84AB000000      jz 0x100017dc
10001731  3D9A020000        cmp eax,0x29a
10001736  0F84A0000000      jz 0x100017dc
1000173C  8B467C            mov eax,[esi+0x7c]
1000173F  55                push ebp
10001740  56                push esi
10001741  8D0440            lea eax,[eax+eax*2]
10001744  FF1485E0450210    call dword near [eax*4+0x100245e0]
1000174B  83C408            add esp,0x8
1000174E  83F802            cmp eax,0x2
10001751  7405              jz 0x10001758
10001753  83F803            cmp eax,0x3
10001756  7507              jnz 0x1000175f
10001758  C746049A020000    mov dword [esi+0x4],0x29a
1000175F  85C0              test eax,eax
10001761  0F84CE000000      jz 0x10001835
10001767  83F802            cmp eax,0x2
1000176A  0F84C5000000      jz 0x10001835
10001770  83F801            cmp eax,0x1
10001773  7567              jnz 0x100017dc
10001775  3BE8              cmp ebp,eax
10001777  750B              jnz 0x10001784
10001779  56                push esi
1000177A  E8D1580000        call 0x10007050
1000177F  83C404            add esp,0x4
10001782  EB3A              jmp 0x100017be
10001784  6A00              push dword 0x0
10001786  6A00              push dword 0x0
10001788  6A00              push dword 0x0
1000178A  56                push esi
1000178B  E820580000        call 0x10006fb0
10001790  83C410            add esp,0x10
10001793  83FD03            cmp ebp,0x3
10001796  7526              jnz 0x100017be
10001798  8B4E44            mov ecx,[esi+0x44]
1000179B  8B563C            mov edx,[esi+0x3c]
1000179E  66C7444AFE0000    mov word [edx+ecx*2-0x2],0x0
100017A5  8B4644            mov eax,[esi+0x44]
100017A8  8B7E3C            mov edi,[esi+0x3c]
100017AB  8D4C00FE          lea ecx,[eax+eax-0x2]
100017AF  33C0              xor eax,eax
100017B1  8BD1              mov edx,ecx
100017B3  C1E902            shr ecx,byte 0x2
100017B6  F3AB              rep stosd
100017B8  8BCA              mov ecx,edx
100017BA  23CD              and ecx,ebp
100017BC  F3AA              rep stosb
100017BE  53                push ebx
100017BF  E8CC000000        call 0x10001890
100017C4  8B4310            mov eax,[ebx+0x10]
100017C7  83C404            add esp,0x4
100017CA  85C0              test eax,eax
100017CC  750E              jnz 0x100017dc
100017CE  C74620FFFFFFFF    mov dword [esi+0x20],0xffffffff
100017D5  5F                pop edi
100017D6  5E                pop esi
100017D7  5D                pop ebp
100017D8  33C0              xor eax,eax
100017DA  5B                pop ebx
100017DB  C3                ret
100017DC  83FD04            cmp ebp,0x4
100017DF  7407              jz 0x100017e8
100017E1  5F                pop edi
100017E2  5E                pop esi
100017E3  5D                pop ebp
100017E4  33C0              xor eax,eax
100017E6  5B                pop ebx
100017E7  C3                ret
100017E8  8B4618            mov eax,[esi+0x18]
100017EB  85C0              test eax,eax
100017ED  740A              jz 0x100017f9
100017EF  5F                pop edi
100017F0  5E                pop esi
100017F1  5D                pop ebp
100017F2  B801000000        mov eax,0x1
100017F7  5B                pop ebx
100017F8  C3                ret
100017F9  8B4330            mov eax,[ebx+0x30]
100017FC  C1E810            shr eax,byte 0x10
100017FF  50                push eax
10001800  56                push esi
10001801  E85A000000        call 0x10001860
10001806  8B4B30            mov ecx,[ebx+0x30]
10001809  81E1FFFF0000      and ecx,0xffff
1000180F  51                push ecx
10001810  56                push esi
10001811  E84A000000        call 0x10001860
10001816  53                push ebx
10001817  E874000000        call 0x10001890
1000181C  8B4E14            mov ecx,[esi+0x14]
1000181F  83C414            add esp,0x14
10001822  C74618FFFFFFFF    mov dword [esi+0x18],0xffffffff
10001829  33C0              xor eax,eax
1000182B  5F                pop edi
1000182C  5E                pop esi
1000182D  85C9              test ecx,ecx
1000182F  5D                pop ebp
10001830  5B                pop ebx
10001831  0F94C0            setz al
10001834  C3                ret
10001835  8B4310            mov eax,[ebx+0x10]
10001838  85C0              test eax,eax
1000183A  7507              jnz 0x10001843
1000183C  C74620FFFFFFFF    mov dword [esi+0x20],0xffffffff
10001843  5F                pop edi
10001844  5E                pop esi
10001845  5D                pop ebp
10001846  33C0              xor eax,eax
10001848  5B                pop ebx
10001849  C3                ret
1000184A  8B15E4940210      mov edx,[0x100294e4]
10001850  895318            mov [ebx+0x18],edx
10001853  5F                pop edi
10001854  5E                pop esi
10001855  5D                pop ebp
10001856  B8FEFFFFFF        mov eax,0xfffffffe
1000185B  5B                pop ebx
1000185C  C3                ret

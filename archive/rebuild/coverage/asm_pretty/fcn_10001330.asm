; pretty disassembly for fcn_10001330
; VA: 0x10001330..0x10001529 (505 bytes)
10001330  8B44241C          mov eax,[esp+0x1c]
10001334  53                push ebx
10001335  55                push ebp
10001336  33D2              xor edx,edx
10001338  33ED              xor ebp,ebp
1000133A  56                push esi
1000133B  3BC2              cmp eax,edx
1000133D  57                push edi
1000133E  0F84DB010000      jz 0x1000151f
10001344  8B0D74700210      mov ecx,[0x10027074]
1000134A  8A00              mov al,[eax]
1000134C  3A01              cmp al,[ecx]
1000134E  0F85CB010000      jnz 0x1000151f
10001354  837C243038        cmp dword [esp+0x30],0x38
10001359  0F85C0010000      jnz 0x1000151f
1000135F  8B7C2414          mov edi,[esp+0x14]
10001363  3BFA              cmp edi,edx
10001365  750A              jnz 0x10001371
10001367  5F                pop edi
10001368  5E                pop esi
10001369  5D                pop ebp
1000136A  B8FEFFFFFF        mov eax,0xfffffffe
1000136F  5B                pop ebx
10001370  C3                ret
10001371  8B4720            mov eax,[edi+0x20]
10001374  895718            mov [edi+0x18],edx
10001377  3BC2              cmp eax,edx
10001379  750A              jnz 0x10001385
1000137B  C74720E0920010    mov dword [edi+0x20],0x100092e0
10001382  895728            mov [edi+0x28],edx
10001385  395724            cmp [edi+0x24],edx
10001388  7507              jnz 0x10001391
1000138A  C7472400930010    mov dword [edi+0x24],0x10009300
10001391  8B4C2418          mov ecx,[esp+0x18]
10001395  83F9FF            cmp ecx,0xffffffffffffffff
10001398  750C              jnz 0x100013a6
1000139A  C744241806000000  mov dword [esp+0x18],0x6
100013A2  8B4C2418          mov ecx,[esp+0x18]
100013A6  8B5C2420          mov ebx,[esp+0x20]
100013AA  3BDA              cmp ebx,edx
100013AC  7D07              jnl 0x100013b5
100013AE  BD01000000        mov ebp,0x1
100013B3  F7DB              neg ebx
100013B5  8B442424          mov eax,[esp+0x24]
100013B9  83F801            cmp eax,0x1
100013BC  7CA9              jl 0x10001367
100013BE  83F809            cmp eax,0x9
100013C1  7FA4              jg 0x10001367
100013C3  837C241C08        cmp dword [esp+0x1c],0x8
100013C8  759D              jnz 0x10001367
100013CA  83FB08            cmp ebx,0x8
100013CD  7C98              jl 0x10001367
100013CF  83FB0F            cmp ebx,0xf
100013D2  7F93              jg 0x10001367
100013D4  3BCA              cmp ecx,edx
100013D6  7C8F              jl 0x10001367
100013D8  83F909            cmp ecx,0x9
100013DB  7F8A              jg 0x10001367
100013DD  8B442428          mov eax,[esp+0x28]
100013E1  3BC2              cmp eax,edx
100013E3  7C82              jl 0x10001367
100013E5  83F802            cmp eax,0x2
100013E8  0F8F79FFFFFF      jg 0x10001367
100013EE  8B5728            mov edx,[edi+0x28]
100013F1  68B8160000        push dword 0x16b8
100013F6  6A01              push dword 0x1
100013F8  52                push edx
100013F9  FF5720            call dword near [edi+0x20]
100013FC  8BF0              mov esi,eax
100013FE  83C40C            add esp,0xc
10001401  85F6              test esi,esi
10001403  750A              jnz 0x1000140f
10001405  5F                pop edi
10001406  5E                pop esi
10001407  5D                pop ebp
10001408  B8FCFFFFFF        mov eax,0xfffffffc
1000140D  5B                pop ebx
1000140E  C3                ret
1000140F  89771C            mov [edi+0x1c],esi
10001412  896E18            mov [esi+0x18],ebp
10001415  BD01000000        mov ebp,0x1
1000141A  8BCB              mov ecx,ebx
1000141C  D3E5              shl ebp,cl
1000141E  895E28            mov [esi+0x28],ebx
10001421  8B5C2424          mov ebx,[esp+0x24]
10001425  893E              mov [esi],edi
10001427  6A02              push dword 0x2
10001429  8D4B07            lea ecx,[ebx+0x7]
1000142C  894E48            mov [esi+0x48],ecx
1000142F  896E24            mov [esi+0x24],ebp
10001432  8D45FF            lea eax,[ebp-0x1]
10001435  55                push ebp
10001436  89462C            mov [esi+0x2c],eax
10001439  B801000000        mov eax,0x1
1000143E  D3E0              shl eax,cl
10001440  83C102            add ecx,0x2
10001443  894644            mov [esi+0x44],eax
10001446  48                dec eax
10001447  89464C            mov [esi+0x4c],eax
1000144A  B8ABAAAAAA        mov eax,0xaaaaaaab
1000144F  F7E1              mul ecx
10001451  D1EA              shr edx,0x0
10001453  895650            mov [esi+0x50],edx
10001456  8B4F28            mov ecx,[edi+0x28]
10001459  51                push ecx
1000145A  FF5720            call dword near [edi+0x20]
1000145D  8B5624            mov edx,[esi+0x24]
10001460  894630            mov [esi+0x30],eax
10001463  8B4728            mov eax,[edi+0x28]
10001466  6A02              push dword 0x2
10001468  52                push edx
10001469  50                push eax
1000146A  FF5720            call dword near [edi+0x20]
1000146D  8B4E44            mov ecx,[esi+0x44]
10001470  894638            mov [esi+0x38],eax
10001473  8B5728            mov edx,[edi+0x28]
10001476  6A02              push dword 0x2
10001478  51                push ecx
10001479  52                push edx
1000147A  FF5720            call dword near [edi+0x20]
1000147D  89463C            mov [esi+0x3c],eax
10001480  8D4B06            lea ecx,[ebx+0x6]
10001483  B801000000        mov eax,0x1
10001488  6A04              push dword 0x4
1000148A  D3E0              shl eax,cl
1000148C  898694160000      mov [esi+0x1694],eax
10001492  50                push eax
10001493  8B4728            mov eax,[edi+0x28]
10001496  50                push eax
10001497  FF5720            call dword near [edi+0x20]
1000149A  8B8E94160000      mov ecx,[esi+0x1694]
100014A0  83C430            add esp,0x30
100014A3  894608            mov [esi+0x8],eax
100014A6  8D148D00000000    lea edx,[ecx*4+0x0]
100014AD  89560C            mov [esi+0xc],edx
100014B0  8B5630            mov edx,[esi+0x30]
100014B3  85D2              test edx,edx
100014B5  744D              jz 0x10001504
100014B7  8B5638            mov edx,[esi+0x38]
100014BA  85D2              test edx,edx
100014BC  7446              jz 0x10001504
100014BE  8B563C            mov edx,[esi+0x3c]
100014C1  85D2              test edx,edx
100014C3  743F              jz 0x10001504
100014C5  85C0              test eax,eax
100014C7  743B              jz 0x10001504
100014C9  8BD1              mov edx,ecx
100014CB  57                push edi
100014CC  D1EA              shr edx,0x0
100014CE  C6461D08          mov byte [esi+0x1d],0x8
100014D2  8D1450            lea edx,[eax+edx*2]
100014D5  8D0448            lea eax,[eax+ecx*2]
100014D8  03C8              add ecx,eax
100014DA  89969C160000      mov [esi+0x169c],edx
100014E0  8B54242C          mov edx,[esp+0x2c]
100014E4  898E90160000      mov [esi+0x1690],ecx
100014EA  8B4C241C          mov ecx,[esp+0x1c]
100014EE  899680000000      mov [esi+0x80],edx
100014F4  894E7C            mov [esi+0x7c],ecx
100014F7  E834000000        call 0x10001530
100014FC  83C404            add esp,0x4
100014FF  5F                pop edi
10001500  5E                pop esi
10001501  5D                pop ebp
10001502  5B                pop ebx
10001503  C3                ret
10001504  A1EC940210        mov eax,[0x100294ec]
10001509  57                push edi
1000150A  894718            mov [edi+0x18],eax
1000150D  E8FE030000        call 0x10001910
10001512  83C404            add esp,0x4
10001515  B8FCFFFFFF        mov eax,0xfffffffc
1000151A  5F                pop edi
1000151B  5E                pop esi
1000151C  5D                pop ebp
1000151D  5B                pop ebx
1000151E  C3                ret
1000151F  5F                pop edi
10001520  5E                pop esi
10001521  5D                pop ebp
10001522  B8FAFFFFFF        mov eax,0xfffffffa
10001527  5B                pop ebx
10001528  C3                ret

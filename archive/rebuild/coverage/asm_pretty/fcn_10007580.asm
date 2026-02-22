; pretty disassembly for fcn_10007580
; VA: 0x10007580..0x100078e0 (864 bytes)
10007580  8B542420          mov edx,[esp+0x20]
10007584  896A04            mov [edx+0x4],ebp
10007587  8B8648140000      mov eax,[esi+0x1448]
1000758D  99                cdq
1000758E  2BC2              sub eax,edx
10007590  8BD8              mov ebx,eax
10007592  D1FB              sar ebx,0x0
10007594  83FB01            cmp ebx,0x1
10007597  7C11              jl 0x100075aa
10007599  53                push ebx
1000759A  57                push edi
1000759B  56                push esi
1000759C  E83F010000        call 0x100076e0
100075A1  83C40C            add esp,0xc
100075A4  4B                dec ebx
100075A5  83FB01            cmp ebx,0x1
100075A8  7DEF              jnl 0x10007599
100075AA  8B442414          mov eax,[esp+0x14]
100075AE  89442414          mov [esp+0x14],eax
100075B2  8D0487            lea eax,[edi+eax*4]
100075B5  8944241C          mov [esp+0x1c],eax
100075B9  8B8648140000      mov eax,[esi+0x1448]
100075BF  8B9E580B0000      mov ebx,[esi+0xb58]
100075C5  6A01              push dword 0x1
100075C7  57                push edi
100075C8  8B8C86540B0000    mov ecx,[esi+eax*4+0xb54]
100075CF  48                dec eax
100075D0  56                push esi
100075D1  898E580B0000      mov [esi+0xb58],ecx
100075D7  898648140000      mov [esi+0x1448],eax
100075DD  E8FE000000        call 0x100076e0
100075E2  8B964C140000      mov edx,[esi+0x144c]
100075E8  8BAE580B0000      mov ebp,[esi+0xb58]
100075EE  83C40C            add esp,0xc
100075F1  4A                dec edx
100075F2  8BC2              mov eax,edx
100075F4  89964C140000      mov [esi+0x144c],edx
100075FA  899C86540B0000    mov [esi+eax*4+0xb54],ebx
10007601  8B8E4C140000      mov ecx,[esi+0x144c]
10007607  49                dec ecx
10007608  8BC1              mov eax,ecx
1000760A  898E4C140000      mov [esi+0x144c],ecx
10007610  89AC86540B0000    mov [esi+eax*4+0xb54],ebp
10007617  668B14AF          mov dx,[edi+ebp*4]
1000761B  6603149F          add dx,[edi+ebx*4]
1000761F  8B44241C          mov eax,[esp+0x1c]
10007623  668910            mov [eax],dx
10007626  8A841E50140000    mov al,[esi+ebx+0x1450]
1000762D  8A8C2E50140000    mov cl,[esi+ebp+0x1450]
10007634  3AC1              cmp al,cl
10007636  7207              jc 0x1000763f
10007638  25FF000000        and eax,0xff
1000763D  EB08              jmp 0x10007647
1000763F  81E1FF000000      and ecx,0xff
10007645  8BC1              mov eax,ecx
10007647  8B4C2414          mov ecx,[esp+0x14]
1000764B  FEC0              inc al
1000764D  6A01              push dword 0x1
1000764F  57                push edi
10007650  88840E50140000    mov [esi+ecx+0x1450],al
10007657  8B442424          mov eax,[esp+0x24]
1000765B  66894CAF02        mov [edi+ebp*4+0x2],cx
10007660  66894C9F02        mov [edi+ebx*4+0x2],cx
10007665  898E580B0000      mov [esi+0xb58],ecx
1000766B  41                inc ecx
1000766C  83C004            add eax,0x4
1000766F  56                push esi
10007670  894C2420          mov [esp+0x20],ecx
10007674  89442428          mov [esp+0x28],eax
10007678  E863000000        call 0x100076e0
1000767D  8B8648140000      mov eax,[esi+0x1448]
10007683  83C40C            add esp,0xc
10007686  83F802            cmp eax,0x2
10007689  0F8D2AFFFFFF      jnl 0x100075b9
1000768F  8B964C140000      mov edx,[esi+0x144c]
10007695  8B8E580B0000      mov ecx,[esi+0xb58]
1000769B  4A                dec edx
1000769C  89964C140000      mov [esi+0x144c],edx
100076A2  8BC2              mov eax,edx
100076A4  8B542420          mov edx,[esp+0x20]
100076A8  52                push edx
100076A9  56                push esi
100076AA  898C86540B0000    mov [esi+eax*4+0xb54],ecx
100076B1  E80A010000        call 0x100077c0
100076B6  8B442418          mov eax,[esp+0x18]
100076BA  81C6340B0000      add esi,0xb34
100076C0  56                push esi
100076C1  50                push eax
100076C2  57                push edi
100076C3  E828030000        call 0x100079f0
100076C8  83C414            add esp,0x14
100076CB  5F                pop edi
100076CC  5E                pop esi
100076CD  5D                pop ebp
100076CE  5B                pop ebx
100076CF  83C408            add esp,0x8
100076D2  C3                ret
100076D3  90                nop
100076D4  90                nop
100076D5  90                nop
100076D6  90                nop
100076D7  90                nop
100076D8  90                nop
100076D9  90                nop
100076DA  90                nop
100076DB  90                nop
100076DC  90                nop
100076DD  90                nop
100076DE  90                nop
100076DF  90                nop
100076E0  8B442404          mov eax,[esp+0x4]
100076E4  53                push ebx
100076E5  55                push ebp
100076E6  56                push esi
100076E7  8B742418          mov esi,[esp+0x18]
100076EB  8B9048140000      mov edx,[eax+0x1448]
100076F1  57                push edi
100076F2  8BACB0540B0000    mov ebp,[eax+esi*4+0xb54]
100076F9  8D0C36            lea ecx,[esi+esi]
100076FC  3BCA              cmp ecx,edx
100076FE  896C2414          mov [esp+0x14],ebp
10007702  0F8F9D000000      jg 0x100077a5
10007708  8B7C2418          mov edi,[esp+0x18]
1000770C  7D34              jnl 0x10007742
1000770E  8BB488580B0000    mov esi,[eax+ecx*4+0xb58]
10007715  8BAC88540B0000    mov ebp,[eax+ecx*4+0xb54]
1000771C  668B14B7          mov dx,[edi+esi*4]
10007720  668B1CAF          mov bx,[edi+ebp*4]
10007724  663BD3            cmp dx,bx
10007727  7214              jc 0x1000773d
10007729  7513              jnz 0x1000773e
1000772B  8A940650140000    mov dl,[esi+eax+0x1450]
10007732  8A9C2850140000    mov bl,[eax+ebp+0x1450]
10007739  3AD3              cmp dl,bl
1000773B  7701              ja 0x1000773e
1000773D  41                inc ecx
1000773E  8B6C2414          mov ebp,[esp+0x14]
10007742  8BB488540B0000    mov esi,[eax+ecx*4+0xb54]
10007749  668B14AF          mov dx,[edi+ebp*4]
1000774D  668B1CB7          mov bx,[edi+esi*4]
10007751  663BD3            cmp dx,bx
10007754  722F              jc 0x10007785
10007756  7512              jnz 0x1000776a
10007758  8A942850140000    mov dl,[eax+ebp+0x1450]
1000775F  8A9C0650140000    mov bl,[esi+eax+0x1450]
10007766  3AD3              cmp dl,bl
10007768  762B              jna 0x10007795
1000776A  8B54241C          mov edx,[esp+0x1c]
1000776E  894C241C          mov [esp+0x1c],ecx
10007772  D1E1              shl ecx,0x0
10007774  89B490540B0000    mov [eax+edx*4+0xb54],esi
1000777B  8B9048140000      mov edx,[eax+0x1448]
10007781  3BCA              cmp ecx,edx
10007783  7E87              jng 0x1000770c
10007785  8B4C241C          mov ecx,[esp+0x1c]
10007789  5F                pop edi
1000778A  5E                pop esi
1000778B  89AC88540B0000    mov [eax+ecx*4+0xb54],ebp
10007792  5D                pop ebp
10007793  5B                pop ebx
10007794  C3                ret
10007795  8B54241C          mov edx,[esp+0x1c]
10007799  5F                pop edi
1000779A  5E                pop esi
1000779B  89AC90540B0000    mov [eax+edx*4+0xb54],ebp
100077A2  5D                pop ebp
100077A3  5B                pop ebx
100077A4  C3                ret
100077A5  89ACB0540B0000    mov [eax+esi*4+0xb54],ebp
100077AC  5F                pop edi
100077AD  5E                pop esi
100077AE  5D                pop ebp
100077AF  5B                pop ebx
100077B0  C3                ret
100077B1  90                nop
100077B2  90                nop
100077B3  90                nop
100077B4  90                nop
100077B5  90                nop
100077B6  90                nop
100077B7  90                nop
100077B8  90                nop
100077B9  90                nop
100077BA  90                nop
100077BB  90                nop
100077BC  90                nop
100077BD  90                nop
100077BE  90                nop
100077BF  90                nop
100077C0  83EC1C            sub esp,0x1c
100077C3  8B442424          mov eax,[esp+0x24]
100077C7  53                push ebx
100077C8  55                push ebp
100077C9  56                push esi
100077CA  8B18              mov ebx,[eax]
100077CC  8B4804            mov ecx,[eax+0x4]
100077CF  8B4008            mov eax,[eax+0x8]
100077D2  894C2418          mov [esp+0x18],ecx
100077D6  57                push edi
100077D7  33F6              xor esi,esi
100077D9  8B10              mov edx,[eax]
100077DB  8B4804            mov ecx,[eax+0x4]
100077DE  8B6810            mov ebp,[eax+0x10]
100077E1  89542414          mov [esp+0x14],edx
100077E5  8B5008            mov edx,[eax+0x8]
100077E8  894C2424          mov [esp+0x24],ecx
100077EC  89542420          mov [esp+0x20],edx
100077F0  8B542430          mov edx,[esp+0x30]
100077F4  B908000000        mov ecx,0x8
100077F9  33C0              xor eax,eax
100077FB  8DBA340B0000      lea edi,[edx+0xb34]
10007801  89742410          mov [esp+0x10],esi
10007805  F3AB              rep stosd
10007807  8B824C140000      mov eax,[edx+0x144c]
1000780D  896C2428          mov [esp+0x28],ebp
10007811  8B8C82540B0000    mov ecx,[edx+eax*4+0xb54]
10007818  6689748B02        mov [ebx+ecx*4+0x2],si
1000781D  8BB24C140000      mov esi,[edx+0x144c]
10007823  46                inc esi
10007824  81FE3D020000      cmp esi,0x23d
1000782A  0F8DA9010000      jnl 0x100079d9
10007830  8D84B2540B0000    lea eax,[edx+esi*4+0xb54]
10007837  89442430          mov [esp+0x30],eax
1000783B  B83D020000        mov eax,0x23d
10007840  2BC6              sub eax,esi
10007842  03F0              add esi,eax
10007844  89442418          mov [esp+0x18],eax
10007848  89742434          mov [esp+0x34],esi
1000784C  8B4C2430          mov ecx,[esp+0x30]
10007850  33C0              xor eax,eax
10007852  33FF              xor edi,edi
10007854  8B09              mov ecx,[ecx]
10007856  668B448B02        mov ax,[ebx+ecx*4+0x2]
1000785B  668B7C8302        mov di,[ebx+eax*4+0x2]
10007860  8BC7              mov eax,edi
10007862  40                inc eax
10007863  3BC5              cmp eax,ebp
10007865  7E0B              jng 0x10007872
10007867  8B7C2410          mov edi,[esp+0x10]
1000786B  8BC5              mov eax,ebp
1000786D  47                inc edi
1000786E  897C2410          mov [esp+0x10],edi
10007872  8B7C241C          mov edi,[esp+0x1c]
10007876  6689448B02        mov [ebx+ecx*4+0x2],ax
1000787B  3BCF              cmp ecx,edi
1000787D  7F60              jg 0x100078df
1000787F  8B742420          mov esi,[esp+0x20]
10007883  66FF8442340B0000  inc word [edx+eax*2+0xb34]
1000788B  33FF              xor edi,edi
1000788D  3BCE              cmp ecx,esi
1000788F  7C0B              jl 0x1000789c
10007891  8BF9              mov edi,ecx
10007893  2BFE              sub edi,esi
10007895  8B742424          mov esi,[esp+0x24]
10007899  8B3CBE            mov edi,[esi+edi*4]
1000789C  668B348B          mov si,[ebx+ecx*4]
100078A0  03C7              add eax,edi
100078A2  81E6FFFF0000      and esi,0xffff
100078A8  0FAFC6            imul eax,esi
100078AB  0182A0160000      add [edx+0x16a0],eax
100078B1  8B442414          mov eax,[esp+0x14]
100078B5  85C0              test eax,eax
100078B7  7422              jz 0x100078db
100078B9  8B6C2414          mov ebp,[esp+0x14]
100078BD  33C0              xor eax,eax
100078BF  668B448D02        mov ax,[ebp+ecx*4+0x2]
100078C4  8B8AA4160000      mov ecx,[edx+0x16a4]
100078CA  03C7              add eax,edi
100078CC  8B6C2428          mov ebp,[esp+0x28]
100078D0  0FAFC6            imul eax,esi
100078D3  03C8              add ecx,eax
100078D5  898AA4160000      mov [edx+0x16a4],ecx
100078DB  8B742434          mov esi,[esp+0x34]
100078DF  8B                db 0x8b

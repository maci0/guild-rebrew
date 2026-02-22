; pretty disassembly for fcn_10002fc0
; VA: 0x10002fc0..0x10003138 (376 bytes)
10002FC0  83EC1C            sub esp,0x1c
10002FC3  53                push ebx
10002FC4  55                push ebp
10002FC5  56                push esi
10002FC6  8B74242C          mov esi,[esp+0x2c]
10002FCA  57                push edi
10002FCB  8B16              mov edx,[esi]
10002FCD  8B420C            mov eax,[edx+0xc]
10002FD0  8B4A08            mov ecx,[edx+0x8]
10002FD3  8D7C1010          lea edi,[eax+edx+0x10]
10002FD7  33C0              xor eax,eax
10002FD9  85C9              test ecx,ecx
10002FDB  7618              jna 0x10002ff5
10002FDD  8B5E08            mov ebx,[esi+0x8]
10002FE0  3B5F04            cmp ebx,[edi+0x4]
10002FE3  7205              jc 0x10002fea
10002FE5  3B5F08            cmp ebx,[edi+0x8]
10002FE8  7615              jna 0x10002fff
10002FEA  8B2F              mov ebp,[edi]
10002FEC  40                inc eax
10002FED  3BC1              cmp eax,ecx
10002FEF  8D7C2F10          lea edi,[edi+ebp+0x10]
10002FF3  72EB              jc 0x10002fe0
10002FF5  5F                pop edi
10002FF6  5E                pop esi
10002FF7  5D                pop ebp
10002FF8  32C0              xor al,al
10002FFA  5B                pop ebx
10002FFB  83C41C            add esp,0x1c
10002FFE  C3                ret
10002FFF  A038730210        mov al,[0x10027338]
10003004  8B0D34730210      mov ecx,[0x10027334]
1000300A  88442420          mov [esp+0x20],al
1000300E  A030730210        mov al,[0x10027330]
10003013  894C241C          mov [esp+0x1c],ecx
10003017  8B0D2C730210      mov ecx,[0x1002732c]
1000301D  88442428          mov [esp+0x28],al
10003021  8B4610            mov eax,[esi+0x10]
10003024  894C2424          mov [esp+0x24],ecx
10003028  8A0D1C460310      mov cl,[0x1003461c]
1000302E  85C0              test eax,eax
10003030  C744241400000000  mov dword [esp+0x14],0x0
10003038  7508              jnz 0x10003042
1000303A  8B4F04            mov ecx,[edi+0x4]
1000303D  894E10            mov [esi+0x10],ecx
10003040  EB45              jmp 0x10003087
10003042  3B460C            cmp eax,[esi+0xc]
10003045  750F              jnz 0x10003056
10003047  8B4704            mov eax,[edi+0x4]
1000304A  894610            mov [esi+0x10],eax
1000304D  8B4618            mov eax,[esi+0x18]
10003050  40                inc eax
10003051  894618            mov [esi+0x18],eax
10003054  EB31              jmp 0x10003087
10003056  8D44241C          lea eax,[esp+0x1c]
1000305A  89442414          mov [esp+0x14],eax
1000305E  8B4614            mov eax,[esi+0x14]
10003061  85C0              test eax,eax
10003063  761A              jna 0x1000307f
10003065  837E1801          cmp dword [esi+0x18],0x1
10003069  7714              ja 0x1000307f
1000306B  8D4C2424          lea ecx,[esp+0x24]
1000306F  48                dec eax
10003070  894C2414          mov [esp+0x14],ecx
10003074  8B4F04            mov ecx,[edi+0x4]
10003077  894E10            mov [esi+0x10],ecx
1000307A  894614            mov [esi+0x14],eax
1000307D  EB08              jmp 0x10003087
1000307F  84C9              test cl,cl
10003081  0F846EFFFFFF      jz 0x10002ff5
10003087  8B470C            mov eax,[edi+0xc]
1000308A  50                push eax
1000308B  52                push edx
1000308C  E8AF000000        call 0x10003140
10003091  668B0D14730210    mov cx,[0x10027314]
10003098  8A1516730210      mov dl,[0x10027316]
1000309E  8B1D24400210      mov ebx,[0x10024024]
100030A4  8BE8              mov ebp,eax
100030A6  66A128730210      mov ax,[0x10027328]
100030AC  83C408            add esp,0x8
100030AF  6689442430        mov [esp+0x30],ax
100030B4  8B442414          mov eax,[esp+0x14]
100030B8  85C0              test eax,eax
100030BA  66894C2410        mov [esp+0x10],cx
100030BF  88542412          mov [esp+0x12],dl
100030C3  7412              jz 0x100030d7
100030C5  8D4C2418          lea ecx,[esp+0x18]
100030C9  6A00              push dword 0x0
100030CB  51                push ecx
100030CC  8BD0              mov edx,eax
100030CE  8B4604            mov eax,[esi+0x4]
100030D1  6A04              push dword 0x4
100030D3  52                push edx
100030D4  50                push eax
100030D5  FF                db 0xff
100030D6  D38B178B4604      ror dword [ebx+0x4468b17],cl
100030DC  8D4C2418          lea ecx,[esp+0x18]
100030E0  6A00              push dword 0x0
100030E2  4A                dec edx
100030E3  51                push ecx
100030E4  83C710            add edi,0x10
100030E7  52                push edx
100030E8  57                push edi
100030E9  50                push eax
100030EA  FF                db 0xff
100030EB  D385ED742A8B      rol dword [ebp-0x74d58b13],cl
100030F1  46                inc esi
100030F2  048D              add al,0x8d
100030F4  4C                dec esp
100030F5  2418              and al,0x18
100030F7  6A00              push dword 0x0
100030F9  51                push ecx
100030FA  8D542438          lea edx,[esp+0x38]
100030FE  6A01              push dword 0x1
10003100  52                push edx
10003101  50                push eax
10003102  FF                db 0xff
10003103  D38B55008B46      ror dword [ebx+0x468b0055],cl
10003109  048D              add al,0x8d
1000310B  4C                dec esp
1000310C  2418              and al,0x18
1000310E  6A00              push dword 0x0
10003110  4A                dec edx
10003111  51                push ecx
10003112  83C504            add ebp,0x4
10003115  52                push edx
10003116  55                push ebp
10003117  50                push eax
10003118  FF                db 0xff
10003119  D38B46048D4C      ror dword [ebx+0x4c8d0446],cl
1000311F  2418              and al,0x18
10003121  6A00              push dword 0x0
10003123  51                push ecx
10003124  8D542418          lea edx,[esp+0x18]
10003128  6A02              push dword 0x2
1000312A  52                push edx
1000312B  50                push eax
1000312C  FF                db 0xff
1000312D  D35F5E            rcr dword [edi+0x5e],cl
10003130  5D                pop ebp
10003131  B001              mov al,0x1
10003133  5B                pop ebx
10003134  83C41C            add esp,0x1c
10003137  C3                ret

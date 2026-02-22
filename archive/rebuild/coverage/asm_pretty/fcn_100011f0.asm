; pretty disassembly for fcn_100011f0
; VA: 0x100011f0..0x10001325 (309 bytes)
100011F0  8B4C2408          mov ecx,[esp+0x8]
100011F4  85C9              test ecx,ecx
100011F6  7503              jnz 0x100011fb
100011F8  33C0              xor eax,eax
100011FA  C3                ret
100011FB  8B442404          mov eax,[esp+0x4]
100011FF  53                push ebx
10001200  56                push esi
10001201  8B742414          mov esi,[esp+0x14]
10001205  83FE08            cmp esi,0x8
10001208  F7D0              not eax
1000120A  0F82EE000000      jc 0x100012fe
10001210  57                push edi
10001211  8BFE              mov edi,esi
10001213  C1EF03            shr edi,byte 0x3
10001216  8BD0              mov edx,eax
10001218  33DB              xor ebx,ebx
1000121A  8A19              mov bl,[ecx]
1000121C  81E2FF000000      and edx,0xff
10001222  33D3              xor edx,ebx
10001224  8BD8              mov ebx,eax
10001226  C1EB08            shr ebx,byte 0x8
10001229  8B0495A0410210    mov eax,[edx*4+0x100241a0]
10001230  83EE08            sub esi,0x8
10001233  33C3              xor eax,ebx
10001235  41                inc ecx
10001236  8BD0              mov edx,eax
10001238  33DB              xor ebx,ebx
1000123A  8A19              mov bl,[ecx]
1000123C  81E2FF000000      and edx,0xff
10001242  33D3              xor edx,ebx
10001244  33DB              xor ebx,ebx
10001246  8A5901            mov bl,[ecx+0x1]
10001249  8B1495A0410210    mov edx,[edx*4+0x100241a0]
10001250  C1E808            shr eax,byte 0x8
10001253  33D0              xor edx,eax
10001255  41                inc ecx
10001256  8BC2              mov eax,edx
10001258  25FF000000        and eax,0xff
1000125D  33C3              xor eax,ebx
1000125F  33DB              xor ebx,ebx
10001261  8A5901            mov bl,[ecx+0x1]
10001264  8B0485A0410210    mov eax,[eax*4+0x100241a0]
1000126B  C1EA08            shr edx,byte 0x8
1000126E  33C2              xor eax,edx
10001270  41                inc ecx
10001271  8BD0              mov edx,eax
10001273  81E2FF000000      and edx,0xff
10001279  33D3              xor edx,ebx
1000127B  33DB              xor ebx,ebx
1000127D  8A5901            mov bl,[ecx+0x1]
10001280  8B1495A0410210    mov edx,[edx*4+0x100241a0]
10001287  C1E808            shr eax,byte 0x8
1000128A  33D0              xor edx,eax
1000128C  41                inc ecx
1000128D  8BC2              mov eax,edx
1000128F  25FF000000        and eax,0xff
10001294  33C3              xor eax,ebx
10001296  33DB              xor ebx,ebx
10001298  8A5901            mov bl,[ecx+0x1]
1000129B  8B0485A0410210    mov eax,[eax*4+0x100241a0]
100012A2  C1EA08            shr edx,byte 0x8
100012A5  33C2              xor eax,edx
100012A7  41                inc ecx
100012A8  8BD0              mov edx,eax
100012AA  81E2FF000000      and edx,0xff
100012B0  33D3              xor edx,ebx
100012B2  33DB              xor ebx,ebx
100012B4  8A5901            mov bl,[ecx+0x1]
100012B7  8B1495A0410210    mov edx,[edx*4+0x100241a0]
100012BE  C1E808            shr eax,byte 0x8
100012C1  33D0              xor edx,eax
100012C3  41                inc ecx
100012C4  8BC2              mov eax,edx
100012C6  25FF000000        and eax,0xff
100012CB  33C3              xor eax,ebx
100012CD  33DB              xor ebx,ebx
100012CF  8A5901            mov bl,[ecx+0x1]
100012D2  8B0485A0410210    mov eax,[eax*4+0x100241a0]
100012D9  C1EA08            shr edx,byte 0x8
100012DC  33C2              xor eax,edx
100012DE  41                inc ecx
100012DF  8BD0              mov edx,eax
100012E1  81E2FF000000      and edx,0xff
100012E7  33D3              xor edx,ebx
100012E9  C1E808            shr eax,byte 0x8
100012EC  8B1495A0410210    mov edx,[edx*4+0x100241a0]
100012F3  33C2              xor eax,edx
100012F5  41                inc ecx
100012F6  4F                dec edi
100012F7  0F8519FFFFFF      jnz 0x10001216
100012FD  5F                pop edi
100012FE  85F6              test esi,esi
10001300  741E              jz 0x10001320
10001302  8BD0              mov edx,eax
10001304  33DB              xor ebx,ebx
10001306  8A19              mov bl,[ecx]
10001308  81E2FF000000      and edx,0xff
1000130E  33D3              xor edx,ebx
10001310  C1E808            shr eax,byte 0x8
10001313  8B1495A0410210    mov edx,[edx*4+0x100241a0]
1000131A  33C2              xor eax,edx
1000131C  41                inc ecx
1000131D  4E                dec esi
1000131E  75E2              jnz 0x10001302
10001320  5E                pop esi
10001321  5B                pop ebx
10001322  F7D0              not eax
10001324  C3                ret

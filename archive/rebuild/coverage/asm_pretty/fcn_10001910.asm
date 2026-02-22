; pretty disassembly for fcn_10001910
; VA: 0x10001910..0x100019ba (170 bytes)
10001910  56                push esi
10001911  8B742408          mov esi,[esp+0x8]
10001915  85F6              test esi,esi
10001917  57                push edi
10001918  0F8494000000      jz 0x100019b2
1000191E  8B461C            mov eax,[esi+0x1c]
10001921  85C0              test eax,eax
10001923  0F8489000000      jz 0x100019b2
10001929  8B7804            mov edi,[eax+0x4]
1000192C  83FF2A            cmp edi,0x2a
1000192F  740D              jz 0x1000193e
10001931  83FF71            cmp edi,0x71
10001934  7408              jz 0x1000193e
10001936  81FF9A020000      cmp edi,0x29a
1000193C  7574              jnz 0x100019b2
1000193E  8B4008            mov eax,[eax+0x8]
10001941  85C0              test eax,eax
10001943  740B              jz 0x10001950
10001945  50                push eax
10001946  8B4628            mov eax,[esi+0x28]
10001949  50                push eax
1000194A  FF5624            call dword near [esi+0x24]
1000194D  83C408            add esp,0x8
10001950  8B4E1C            mov ecx,[esi+0x1c]
10001953  8B413C            mov eax,[ecx+0x3c]
10001956  85C0              test eax,eax
10001958  740B              jz 0x10001965
1000195A  8B5628            mov edx,[esi+0x28]
1000195D  50                push eax
1000195E  52                push edx
1000195F  FF5624            call dword near [esi+0x24]
10001962  83C408            add esp,0x8
10001965  8B461C            mov eax,[esi+0x1c]
10001968  8B4038            mov eax,[eax+0x38]
1000196B  85C0              test eax,eax
1000196D  740B              jz 0x1000197a
1000196F  8B4E28            mov ecx,[esi+0x28]
10001972  50                push eax
10001973  51                push ecx
10001974  FF5624            call dword near [esi+0x24]
10001977  83C408            add esp,0x8
1000197A  8B561C            mov edx,[esi+0x1c]
1000197D  8B4230            mov eax,[edx+0x30]
10001980  85C0              test eax,eax
10001982  740B              jz 0x1000198f
10001984  50                push eax
10001985  8B4628            mov eax,[esi+0x28]
10001988  50                push eax
10001989  FF5624            call dword near [esi+0x24]
1000198C  83C408            add esp,0x8
1000198F  8B4E1C            mov ecx,[esi+0x1c]
10001992  8B5628            mov edx,[esi+0x28]
10001995  51                push ecx
10001996  52                push edx
10001997  FF5624            call dword near [esi+0x24]
1000199A  83C408            add esp,0x8
1000199D  33C0              xor eax,eax
1000199F  83FF71            cmp edi,0x71
100019A2  C7461C00000000    mov dword [esi+0x1c],0x0
100019A9  0F95C0            setnz al
100019AC  48                dec eax
100019AD  5F                pop edi
100019AE  24FD              and al,0xfd
100019B0  5E                pop esi
100019B1  C3                ret
100019B2  5F                pop edi
100019B3  B8FEFFFFFF        mov eax,0xfffffffe
100019B8  5E                pop esi
100019B9  C3                ret

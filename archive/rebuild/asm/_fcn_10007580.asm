; fcn_10007580
; Address: 0x10007580
; Size: 864 bytes

BITS 32
org 0x10007580

fcn_10007580:
    mov edx, [esp+0x20]
    mov [edx+0x4], ebp
    mov eax, [esi+0x1448]
    cdq
    ; NOTE: MSVC6 uses 2B C2 for `sub eax, edx`
    db 0x2B, 0xC2
    ; NOTE: MSVC6 uses 8B D8 for `mov ebx, eax`
    db 0x8B, 0xD8
    sar ebx, 1
    cmp ebx, 1
    jl short 0x100075aa
    push ebx
    push edi
    push esi
    call 0x100076e0
    add esp, 0xc
    dec ebx
    cmp ebx, 1
    jge short 0x10007599
    mov eax, [esp+0x14]
    mov [esp+0x14], eax
    lea eax, [edi+eax*4]
    mov [esp+0x1c], eax
    mov eax, [esi+0x1448]
    mov ebx, [esi+0xb58]
    push dword 0x1
    push edi
    mov ecx, [esi+eax*4+0xb54]
    dec eax
    push esi
    mov [esi+0xb58], ecx
    mov [esi+0x1448], eax
    call 0x100076e0
    mov edx, [esi+0x144c]
    mov ebp, [esi+0xb58]
    add esp, 0xc
    dec edx
    ; NOTE: MSVC6 uses 8B C2 for `mov eax, edx`
    db 0x8B, 0xC2
    mov [esi+0x144c], edx
    mov [esi+eax*4+0xb54], ebx
    mov ecx, [esi+0x144c]
    dec ecx
    ; NOTE: MSVC6 uses 8B C1 for `mov eax, ecx`
    db 0x8B, 0xC1
    mov [esi+0x144c], ecx
    mov [esi+eax*4+0xb54], ebp
    mov dx, [edi+ebp*4]
    add dx, [edi+ebx*4]
    mov eax, [esp+0x1c]
    mov [eax], dx
    mov al, [esi+ebx+0x1450]
    mov cl, [esi+ebp+0x1450]
    ; NOTE: MSVC6 uses 3A C1 for `cmp al, cl`
    db 0x3A, 0xC1
    jc short 0x1000763f
    and eax, 0xff
    jmp short 0x10007647

    and ecx, 0xff
    ; NOTE: MSVC6 uses 8B C1 for `mov eax, ecx`
    db 0x8B, 0xC1
    mov ecx, [esp+0x14]
    inc al
    push dword 0x1
    push edi
    mov [esi+ecx+0x1450], al
    mov eax, [esp+0x24]
    mov [edi+ebp*4+0x2], cx
    mov [edi+ebx*4+0x2], cx
    mov [esi+0xb58], ecx
    inc ecx
    add eax, 0x4
    push esi
    mov [esp+0x20], ecx
    mov [esp+0x28], eax
    call 0x100076e0
    mov eax, [esi+0x1448]
    add esp, 0xc
    cmp eax, 0x2
    jge 0x100075b9
    mov edx, [esi+0x144c]
    mov ecx, [esi+0xb58]
    dec edx
    mov [esi+0x144c], edx
    ; NOTE: MSVC6 uses 8B C2 for `mov eax, edx`
    db 0x8B, 0xC2
    mov edx, [esp+0x20]
    push edx
    push esi
    mov [esi+eax*4+0xb54], ecx
    call 0x100077c0
    mov eax, [esp+0x18]
    add esi, 0xb34
    push esi
    push eax
    push edi
    call 0x100079f0
    add esp, 0x14
    pop edi
    pop esi
    pop ebp
    pop ebx
    add esp, 0x8
    ret

    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

    mov eax, [esp+0x4]
    push ebx
    push ebp
    push esi
    mov esi, [esp+0x18]
    mov edx, [eax+0x1448]
    push edi
    mov ebp, [eax+esi*4+0xb54]
    lea ecx, [esi+esi]
    ; NOTE: MSVC6 uses 3B CA for `cmp ecx, edx`
    db 0x3B, 0xCA
    mov [esp+0x14], ebp
    jg 0x100077a5
    mov edi, [esp+0x18]
    jge short 0x10007742
    mov esi, [eax+ecx*4+0xb58]
    mov ebp, [eax+ecx*4+0xb54]
    mov dx, [edi+esi*4]
    mov bx, [edi+ebp*4]
    ; NOTE: MSVC6 uses 66 3B D3 for `cmp dx, bx`
    db 0x66, 0x3B, 0xD3
    jc short 0x1000773d
    jnz short 0x1000773e
    mov dl, [esi+eax+0x1450]
    mov bl, [eax+ebp+0x1450]
    ; NOTE: MSVC6 uses 3A D3 for `cmp dl, bl`
    db 0x3A, 0xD3
    ja short 0x1000773e
    inc ecx
    mov ebp, [esp+0x14]
    mov esi, [eax+ecx*4+0xb54]
    mov dx, [edi+ebp*4]
    mov bx, [edi+esi*4]
    ; NOTE: MSVC6 uses 66 3B D3 for `cmp dx, bx`
    db 0x66, 0x3B, 0xD3
    jc short 0x10007785
    jnz short 0x1000776a
    mov dl, [eax+ebp+0x1450]
    mov bl, [esi+eax+0x1450]
    ; NOTE: MSVC6 uses 3A D3 for `cmp dl, bl`
    db 0x3A, 0xD3
    jbe short 0x10007795
    mov edx, [esp+0x1c]
    mov [esp+0x1c], ecx
    shl ecx, 1
    mov [eax+edx*4+0xb54], esi
    mov edx, [eax+0x1448]
    ; NOTE: MSVC6 uses 3B CA for `cmp ecx, edx`
    db 0x3B, 0xCA
    jle short 0x1000770c
    mov ecx, [esp+0x1c]
    pop edi
    pop esi
    mov [eax+ecx*4+0xb54], ebp
    pop ebp
    pop ebx
    ret

    mov edx, [esp+0x1c]
    pop edi
    pop esi
    mov [eax+edx*4+0xb54], ebp
    pop ebp
    pop ebx
    ret

    mov [eax+esi*4+0xb54], ebp
    pop edi
    pop esi
    pop ebp
    pop ebx
    ret

    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop
    nop

    sub esp, 0x1c
    mov eax, [esp+0x24]
    push ebx
    push ebp
    push esi
    mov ebx, [eax]
    mov ecx, [eax+0x4]
    mov eax, [eax+0x8]
    mov [esp+0x18], ecx
    push edi
    ; NOTE: MSVC6 uses 33 F6 for `xor esi, esi`
    db 0x33, 0xF6
    mov edx, [eax]
    mov ecx, [eax+0x4]
    mov ebp, [eax+0x10]
    mov [esp+0x14], edx
    mov edx, [eax+0x8]
    mov [esp+0x24], ecx
    mov [esp+0x20], edx
    mov edx, [esp+0x30]
    mov ecx, 0x8
    ; NOTE: MSVC6 uses 33 C0 for `xor eax, eax`
    db 0x33, 0xC0
    lea edi, [edx+0xb34]
    mov [esp+0x10], esi
    rep stosd
    mov eax, [edx+0x144c]
    mov [esp+0x28], ebp
    mov ecx, [edx+eax*4+0xb54]
    mov [ebx+ecx*4+0x2], si
    mov esi, [edx+0x144c]
    inc esi
    cmp esi, 0x23d
    jge 0x100079d9
    lea eax, [edx+esi*4+0xb54]
    mov [esp+0x30], eax
    mov eax, 0x23d
    ; NOTE: MSVC6 uses 2B C6 for `sub eax, esi`
    db 0x2B, 0xC6
    ; NOTE: MSVC6 uses 03 F0 for `add esi, eax`
    db 0x03, 0xF0
    mov [esp+0x18], eax
    mov [esp+0x34], esi
    mov ecx, [esp+0x30]
    ; NOTE: MSVC6 uses 33 C0 for `xor eax, eax`
    db 0x33, 0xC0
    ; NOTE: MSVC6 uses 33 FF for `xor edi, edi`
    db 0x33, 0xFF
    mov ecx, [ecx]
    mov ax, [ebx+ecx*4+0x2]
    mov di, [ebx+eax*4+0x2]
    ; NOTE: MSVC6 uses 8B C7 for `mov eax, edi`
    db 0x8B, 0xC7
    inc eax
    ; NOTE: MSVC6 uses 3B C5 for `cmp eax, ebp`
    db 0x3B, 0xC5
    jle short 0x10007872
    mov edi, [esp+0x10]
    ; NOTE: MSVC6 uses 8B C5 for `mov eax, ebp`
    db 0x8B, 0xC5
    inc edi
    mov [esp+0x10], edi
    mov edi, [esp+0x1c]
    mov [ebx+ecx*4+0x2], ax
    ; NOTE: MSVC6 uses 3B CF for `cmp ecx, edi`
    db 0x3B, 0xCF
    jg short 0x100078df
    mov esi, [esp+0x20]
    inc word [edx+eax*2+0xb34]
    ; NOTE: MSVC6 uses 33 FF for `xor edi, edi`
    db 0x33, 0xFF
    ; NOTE: MSVC6 uses 3B CE for `cmp ecx, esi`
    db 0x3B, 0xCE
    jl short 0x1000789c
    ; NOTE: MSVC6 uses 8B F9 for `mov edi, ecx`
    db 0x8B, 0xF9
    ; NOTE: MSVC6 uses 2B FE for `sub edi, esi`
    db 0x2B, 0xFE
    mov esi, [esp+0x24]
    mov edi, [esi+edi*4]
    mov si, [ebx+ecx*4]
    ; NOTE: MSVC6 uses 03 C7 for `add eax, edi`
    db 0x03, 0xC7
    and esi, 0xffff
    imul eax, esi
    add [edx+0x16a0], eax
    mov eax, [esp+0x14]
    test eax, eax
    jz short 0x100078db
    mov ebp, [esp+0x14]
    ; NOTE: MSVC6 uses 33 C0 for `xor eax, eax`
    db 0x33, 0xC0
    mov ax, [ebp+ecx*4+0x2]
    mov ecx, [edx+0x16a4]
    ; NOTE: MSVC6 uses 03 C7 for `add eax, edi`
    db 0x03, 0xC7
    mov ebp, [esp+0x28]
    imul eax, esi
    ; NOTE: MSVC6 uses 03 C8 for `add ecx, eax`
    db 0x03, 0xC8
    mov [edx+0x16a4], ecx
    mov esi, [esp+0x34]
    db 0x8b

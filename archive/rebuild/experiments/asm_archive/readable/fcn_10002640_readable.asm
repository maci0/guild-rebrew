; fcn_10002640 - dispatch/logging routine
; Address: 0x10002640
; Size: 290 bytes
; Readable NASM with actual instructions

BITS 32

org 0x10002640

fcn_10002640:
    sub     esp, 0x108
    push    ebx
    mov     bl, [esp+0x114]
    push    ebp
    mov     ebp, [esp+0x114]
    test    bl, 0x1
    push    esi
    je      .flag1_done

    mov     edx, [esp+0x120]
    xor     eax, eax
    mov     ecx, 0x10027078

.scan_loop:
    cmp     edx, [ecx]
    je      .found_entry
    add     ecx, 0x4
    inc     eax
    cmp     ecx, 0x10027084
    jl      .scan_loop
    jmp     .fallback_format

.found_entry:
    shl     eax, 0x5
    add     eax, 0x10027084
    push    eax
    push    0x11766100
    lea     eax, [esp+0x18]
    push    0x100270fc
    push    eax
    call    0x1001a299
    lea     ecx, [esp+0x20]
    push    0x100270f8
    push    ecx
    call    0x1001a286
    mov     esi, eax
    add     esp, 0x18
    test    esi, esi
    jne     .emit_message

.fallback_format:
    push    0x100270e8
    push    0x11766100
    lea     edx, [esp+0x18]
    push    0x100270fc
    push    edx
    call    0x1001a299
    lea     eax, [esp+0x20]
    push    0x100270f8
    push    eax
    call    0x1001a286
    mov     esi, eax
    add     esp, 0x18
    test    esi, esi
    je      .flag1_done

.emit_message:
    push    esi
    push    ebp
    call    0x1001a207
    push    esi
    push    0x100270e4
    call    0x1001a207
    push    esi
    call    0x1001a18a
    add     esp, 0x14

.flag1_done:
    test    bl, 0x4
    je      .flag4_done
    mov     esi, [0x10024004]
    push    ebp
    call    esi
    push    0x100270e4
    call    esi

.flag4_done:
    test    bl, 0x8
    je      .done
    push    edi
    lea     ecx, [esp+0x10]
    push    0x0
    push    ecx
    mov     edi, ebp
    or      ecx, 0xffffffff
    xor     eax, eax
    mov     edx, [0x11766204]
    repnz   scasb
    mov     esi, [0x100240c0]
    not     ecx
    dec     ecx
    push    ecx
    push    ebp
    push    edx
    call    esi

    mov     ecx, [0x11766204]
    lea     eax, [esp+0x10]
    push    0x0
    push    eax
    push    0x1
    push    0x100270e4
    push    ecx
    call    esi
    pop     edi

.done:
    pop     esi
    pop     ebp
    pop     ebx
    add     esp, 0x108
    ret

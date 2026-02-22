; Function: entry0 (DllMain)
; VA: 0x1001B9D4
; Size: 157 bytes
;
; Buildable NASM source that assembles to the exact same byte stream.
; Use: nasm -f bin -o entry0.bin _entry0_nasm.asm
;
; Two kinds of db workarounds:
;   1) MSVC direction-bit encoding: mov ebp,esp (8B EC vs 89 E5),
;      xor eax,eax (33 C0 vs 31 C0)
;   2) External call targets: relative calls to functions outside this
;      snippet — encoded as raw bytes since there's no linker in bin mode.

bits 32
org 0x1001B9D4

_entry0:
    push    ebp
    db 0x8b, 0xec               ; mov ebp, esp  (MSVC: 8B EC; NASM would emit 89 E5)
    push    ebx
    mov     ebx, dword [ebp + 8]
    push    esi
    mov     esi, dword [ebp + 0xc]
    push    edi
    mov     edi, dword [ebp + 0x10]

    ; switch on fdwReason (esi)
    test    esi, esi
    jne     .reason_nonzero
    cmp     dword [0x100354fc], 0
    jmp     .check_fail

.reason_nonzero:
    cmp     esi, 1
    je      .reason_1_or_2
    cmp     esi, 2
    jne     .do_main_call

.reason_1_or_2:
    mov     eax, dword [0x11767588]
    test    eax, eax
    je      .skip_indirect_1
    push    edi
    push    esi
    push    ebx
    call    eax
    test    eax, eax
    je      .return_zero

.skip_indirect_1:
    push    edi
    push    esi
    push    ebx
    db 0xe8, 0xe7, 0xfe, 0xff, 0xff  ; call 0x1001B8FB (external)
    test    eax, eax

.check_fail:
    jne     .do_main_call

.return_zero:
    db 0x33, 0xc0               ; xor eax, eax  (MSVC: 33 C0; NASM would emit 31 C0)
    jmp     .epilog

.do_main_call:
    push    edi
    push    esi
    push    ebx
    db 0xe8, 0xec, 0xd8, 0xfe, 0xff  ; call 0x10009310 (external)
    cmp     esi, 1
    mov     dword [ebp + 0xc], eax
    jne     .check_detach
    test    eax, eax
    jne     .maybe_notify
    push    edi
    push    eax
    push    ebx
    db 0xe8, 0xc3, 0xfe, 0xff, 0xff  ; call 0x1001B8FB (external)

.check_detach:
    test    esi, esi
    je      .do_detach
    cmp     esi, 3
    jne     .maybe_notify

.do_detach:
    push    edi
    push    esi
    push    ebx
    db 0xe8, 0xb2, 0xfe, 0xff, 0xff  ; call 0x1001B8FB (external)
    test    eax, eax
    jne     .check_result
    and     dword [ebp + 0xc], eax

.check_result:
    cmp     dword [ebp + 0xc], 0
    je      .maybe_notify
    mov     eax, dword [0x11767588]
    test    eax, eax
    je      .maybe_notify
    push    edi
    push    esi
    push    ebx
    call    eax
    mov     dword [ebp + 0xc], eax

.maybe_notify:
    mov     eax, dword [ebp + 0xc]

.epilog:
    pop     edi
    pop     esi
    pop     ebx
    pop     ebp
    ret     0xc

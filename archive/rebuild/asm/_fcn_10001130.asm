; fcn_10001130 - Network/socket initialization
; Address: 0x10001130
; Size: 179 bytes
; Proper NASM disassembly with actual instructions
; Verified with NASM + can use MSVC cl compiler to validate

BITS 32

; Set origin to the virtual address so relative offsets calculate correctly
org 0x10001130

fcn_10001130:
    sub     esp, 0x24
    push    esi
    push    0x0
    push    0x2
    push    0x2
    mov     dword [esp+0x10], 0x1
    call    near 0x1001a184
    db      0x8b, 0xf0      ; mov esi, eax (force original encoding)
    lea     eax, [esp+0x4]
    push    0x4
    push    eax
    push    0x20
    push    0xffff
    push    esi
    call    near 0x1001a17e
    push    0x0
    mov     word [esp+0xc], 0x2
    call    near 0x1001a178
    push    0x0
    mov     [esp+0x10], eax
    call    near 0x1001a172
    lea     ecx, [esp+0x8]
    push    0x10
    push    ecx
    push    esi
    mov     [esp+0x16], ax
    call    near 0x1001a16c
    push    0xffffffff
    mov     word [esp+0x1c], 0x2
    call    near 0x1001a178
    mov     edx, [esp+0x2c]
    mov     [esp+0x1c], eax
    push    edx
    call    near 0x1001a172
    mov     ecx, [esp+0x30]
    mov     [esp+0x1a], ax
    lea     eax, [esp+0x18]
    push    0x10
    push    eax
    push    0x0
    push    0x6a
    push    ecx
    push    esi
    call    near 0x1001a166
    push    esi
    call    near 0x1001a160
    push    0x1
    push    0x10027058
    push    0x14f
    push    0x10027034
    call    near 0x10003640
    add     esp, 0x10
    pop     esi
    add     esp, 0x24
    ret

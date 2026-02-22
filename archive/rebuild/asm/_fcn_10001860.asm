; fcn_10001860 - Output byte write helper (zlib)
; Address: 0x10001860
; Size: 47 bytes
; Proper NASM disassembly with actual instructions

BITS 32

org 0x10001860

fcn_10001860:
    mov     eax, [esp+0x4]      ; deflate_state pointer
    mov     ecx, [esp+0x8]      ; value to write
    push    esi
    push    edi
    mov     esi, [eax+0x8]       ; pending_buf
    mov     edi, [eax+0x14]      ; pending count
    mov     edx, ecx
    shr     edx, 0x8
    mov     [esi+edi], dl        ; write high byte
    mov     edx, [eax+0x14]
    mov     esi, [eax+0x8]
    inc     edx
    mov     [eax+0x14], edx
    pop     edi
    mov     [esi+edx], cl        ; write low byte
    mov     ecx, [eax+0x14]
    inc     ecx
    pop     esi
    mov     [eax+0x14], ecx
    ret

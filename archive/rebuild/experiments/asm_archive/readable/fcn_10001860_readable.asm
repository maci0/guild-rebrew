; fcn_10001860 - Output Byte Write Helper (zlib)
; Address: 0x10001860
; Size: 47 bytes
; Writes 2 bytes to pending output buffer

BITS 32

org 0x10001860

fcn_10001860:
    mov     eax, [esp+0x4]      ; deflate_state pointer
    mov     ecx, [esp+0x8]      ; 16-bit value to write
    push    esi
    push    edi
    mov     esi, [eax+0x8]       ; pending_buf pointer
    mov     edi, [eax+0x14]      ; pending count (current position)
    mov     edx, ecx             ; Copy value to edx
    shr     edx, 0x8             ; Get high byte
    mov     [esi+edi], dl        ; Write high byte to buffer
    mov     edx, [eax+0x14]      ; Reload pending count
    mov     esi, [eax+0x8]       ; Reload buffer pointer
    inc     edx                  ; Increment position
    mov     [eax+0x14], edx      ; Store new position
    pop     edi
    mov     [esi+edx], cl        ; Write low byte to buffer
    mov     ecx, [eax+0x14]      ; Reload position
    inc     ecx                  ; Increment again
    pop     esi
    mov     [eax+0x14], ecx      ; Store final position
    ret

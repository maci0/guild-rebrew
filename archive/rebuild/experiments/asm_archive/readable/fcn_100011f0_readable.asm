; fcn_100011f0 - CRC32 Update Function (zlib)
; Address: 0x100011f0
; Size: 309 bytes
; Readable NASM with actual instructions
; Implements CRC32 calculation with lookup table

BITS 32

org 0x100011f0

fcn_100011f0:
    ; Get parameters: ecx = buf, [esp+4] = crc, [esp+8] = len
    mov     ecx, [esp+0x8]          ; buf pointer
    test    ecx, ecx
    jne     .have_buffer
    xor     eax, eax
    ret
    
.have_buffer:
    mov     eax, [esp+0x4]          ; initial crc
    push    ebx
    push    esi
    mov     esi, [esp+0x14]         ; len
    
    ; Check if we have at least 8 bytes for block processing
    cmp     esi, 0x8
    jb      .byte_loop
    not     eax                     ; Invert CRC
    
    ; Process 8 bytes at a time (unrolled loop)
.block_loop:
    push    edi
    mov     edi, esi
    shr     edi, 0x3                ; edi = len / 8
    mov     edx, eax
    xor     ebx, ebx
    
.8byte_loop:
    mov     bl, [ecx]               ; Get next byte
    and     edx, 0xff
    xor     edx, ebx
    mov     ebx, eax
    shr     ebx, 0x8
    mov     eax, [edx*4+0x100241a0] ; Lookup in crc_table
    sub     esi, 0x8
    xor     eax, ebx
    inc     ecx
    
    ; Process 7 more bytes (unrolled)
    mov     edx, eax
    xor     ebx, ebx
    mov     bl, [ecx]
    and     edx, 0xff
    xor     edx, ebx
    xor     ebx, ebx
    mov     bl, [ecx+0x1]
    mov     edx, [edx*4+0x100241a0]
    shr     eax, 0x8
    xor     edx, eax
    inc     ecx
    
    mov     eax, edx
    and     eax, 0xff
    xor     eax, ebx
    xor     ebx, ebx
    mov     bl, [ecx+0x1]
    mov     eax, [eax*4+0x100241a0]
    shr     edx, 0x8
    xor     eax, edx
    inc     ecx
    
    mov     edx, eax
    and     edx, 0xff
    xor     edx, ebx
    xor     ebx, ebx
    mov     bl, [ecx+0x1]
    mov     edx, [edx*4+0x100241a0]
    shr     eax, 0x8
    xor     edx, eax
    inc     ecx
    
    mov     eax, edx
    and     eax, 0xff
    xor     eax, ebx
    xor     ebx, ebx
    mov     bl, [ecx+0x1]
    mov     eax, [eax*4+0x100241a0]
    shr     edx, 0x8
    xor     eax, edx
    inc     ecx
    
    mov     edx, eax
    and     edx, 0xff
    xor     edx, ebx
    xor     ebx, ebx
    mov     bl, [ecx+0x1]
    mov     edx, [edx*4+0x100241a0]
    shr     eax, 0x8
    xor     edx, eax
    inc     ecx
    
    mov     eax, edx
    and     eax, 0xff
    xor     eax, ebx
    xor     ebx, ebx
    mov     bl, [ecx+0x1]
    mov     eax, [eax*4+0x100241a0]
    shr     edx, 0x8
    xor     eax, edx
    inc     ecx
    
    mov     edx, eax
    and     edx, 0xff
    xor     edx, ebx
    shr     eax, 0x8
    mov     edx, [edx*4+0x100241a0]
    xor     eax, edx
    inc     ecx
    dec     edi
    jne     .8byte_loop
    
    pop     edi
    
    ; Process remaining bytes one at a time
.byte_loop:
    test    esi, esi
    je      .done
    
.byte_loop_iter:
    mov     edx, eax
    xor     ebx, ebx
    mov     bl, [ecx]
    and     edx, 0xff
    xor     edx, ebx
    shr     eax, 0x8
    mov     edx, [edx*4+0x100241a0]
    xor     eax, edx
    inc     ecx
    dec     esi
    jne     .byte_loop_iter
    
.done:
    pop     esi
    pop     ebx
    not     eax
    ret

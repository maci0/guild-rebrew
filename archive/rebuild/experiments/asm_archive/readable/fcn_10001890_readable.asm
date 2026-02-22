; fcn_10001890 - Flush Pending Output (zlib)
; Address: 0x10001890
; Size: 114 bytes
; Copies pending output to output stream

BITS 32

org 0x10001890

fcn_10001890:
    mov     eax, [esp+0x4]          ; z_stream pointer
    push    esi
    mov     esi, [eax+0x1c]          ; deflate_state
    mov     ecx, [eax+0x10]          ; avail_out
    mov     edx, [esi+0x14]          ; pending (amount to flush)
    cmp     edx, ecx
    jbe     .use_pending
    mov     edx, ecx                ; Use minimum of pending and avail_out
    
.use_pending:
    test    edx, edx
    je      .nothing_to_flush
    mov     esi, [esi+0x10]          ; pending_out (source)
    mov     ecx, edx                ; Copy count
    push    ebx
    mov     ebx, ecx                ; Save count
    push    edi
    mov     edi, [eax+0xc]           ; next_out (destination)
    shr     ecx, 0x2                 ; Convert to DWORDs
    rep     movsd                    ; Copy DWORDs
    mov     ecx, ebx
    and     ecx, 0x3                 ; Remaining bytes
    rep     movsb                    ; Copy bytes
    mov     edi, [eax+0xc]           ; next_out
    mov     ecx, [eax+0x1c]          ; deflate_state
    add     edi, edx                ; Advance next_out
    mov     [eax+0xc], edi           ; Store next_out
    mov     esi, [ecx+0x10]          ; pending_out
    add     esi, edx                ; Advance pending_out
    mov     [ecx+0x10], esi          ; Store pending_out
    mov     ebx, [eax+0x14]          ; avail_out
    mov     edi, [eax+0x10]          ; total_out low
    sub     ebx, edx                ; Decrease avail_out
    sub     edi, edx                ; Decrease remaining (?)
    mov     [eax+0x14], ebx          ; Store avail_out
    mov     [eax+0x10], edi          ; Store total_out
    mov     esi, [ecx+0x14]          ; pending
    pop     edi
    sub     esi, edx                ; Decrease pending
    pop     ebx
    mov     [ecx+0x14], esi          ; Store pending
    mov     eax, [eax+0x1c]          ; deflate_state
    mov     ecx, [eax+0x14]          ; pending
    test    ecx, ecx
    jne     .nothing_to_flush
    mov     ecx, [eax+0x8]           ; pending_buf
    mov     [eax+0x10], ecx          ; pending_out = pending_buf
    
.nothing_to_flush:
    pop     esi
    ret

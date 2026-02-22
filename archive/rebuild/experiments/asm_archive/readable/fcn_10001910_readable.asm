; fcn_10001910 - Deflate End/Cleanup (zlib)
; Address: 0x10001910
; Size: 170 bytes
; Frees all memory allocated for deflate

BITS 32

org 0x10001910

fcn_10001910:
    push    esi
    mov     esi, [esp+0x8]          ; z_stream pointer
    test    esi, esi
    push    edi
    je      .error
    mov     eax, [esi+0x1c]          ; deflate_state
    test    eax, eax
    je      .error
    mov     edi, [eax+0x4]           ; status
    cmp     edi, 0x2a               ; INIT_STATE
    je      .valid_state
    cmp     edi, 0x71               ; BUSY_STATE
    je      .valid_state
    cmp     edi, 0x29a              ; FINISHING_STATE
    jne     .error
    
.valid_state:
    ; Free pending_buf
    mov     eax, [eax+0x8]
    test    eax, eax
    je      .free_head
    push    eax
    mov     eax, [esi+0x28]          ; zfree
    push    eax
    call    dword [esi+0x24]         ; call zfree
    add     esp, 0x8
    
.free_head:
    ; Free head array
    mov     ecx, [esi+0x1c]
    mov     eax, [ecx+0x3c]
    test    eax, eax
    je      .free_prev
    mov     edx, [esi+0x28]
    push    eax
    push    edx
    call    dword [esi+0x24]
    add     esp, 0x8
    
.free_prev:
    ; Free prev array
    mov     eax, [esi+0x1c]
    mov     eax, [eax+0x38]
    test    eax, eax
    je      .free_window
    mov     ecx, [esi+0x28]
    push    eax
    push    ecx
    call    dword [esi+0x24]
    add     esp, 0x8
    
.free_window:
    ; Free window buffer
    mov     edx, [esi+0x1c]
    mov     eax, [edx+0x30]
    test    eax, eax
    je      .free_state
    push    eax
    mov     eax, [esi+0x28]
    push    eax
    call    dword [esi+0x24]
    add     esp, 0x8
    
.free_state:
    ; Free deflate_state itself
    mov     ecx, [esi+0x1c]
    mov     edx, [esi+0x28]
    push    ecx
    push    edx
    call    dword [esi+0x24]
    add     esp, 0x8
    
    ; Clear state pointer
    xor     eax, eax
    cmp     edi, 0x71               ; Was it BUSY_STATE?
    mov     dword [esi+0x1c], 0x0   ; Clear state
    setne   al                      ; Return Z_DATA_ERROR if BUSY
    dec     eax
    and     al, 0xfd
    pop     edi
    pop     esi
    ret
    
.error:
    pop     edi
    mov     eax, 0xfffffffe         ; Z_STREAM_ERROR
    pop     esi
    ret

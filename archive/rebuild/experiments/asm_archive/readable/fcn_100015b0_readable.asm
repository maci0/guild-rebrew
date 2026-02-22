; fcn_100015b0 - Deflate Parameter Processing (zlib)
; Address: 0x100015b0
; Size: 685 bytes
; Main deflate function handling flush modes and compression

BITS 32

org 0x100015b0

fcn_100015b0:
    push    ebx
    mov     ebx, [esp+0x8]          ; strm
    push    ebp
    push    esi
    test    ebx, ebx
    push    edi
    je      .error_stream
    mov     esi, [ebx+0x1c]         ; deflate_state
    test    esi, esi
    je      .error_stream
    mov     ebp, [esp+0x18]         ; flush
    cmp     ebp, 0x4                ; Z_FINISH
    jg      .error_stream
    test    ebp, ebp
    jl      .error_stream
    mov     eax, [ebx+0xc]          ; next_out
    test    eax, eax
    je      .error_data
    cmp     dword [ebx], 0x0        ; next_in
    jne     .check_state
    mov     eax, [ebx+0x4]          ; avail_in
    test    eax, eax
    jne     .error_data
    
.check_state:
    mov     eax, [esi+0x4]          ; status
    cmp     eax, 0x29a              ; FINISHING_STATE
    jne     .check_busy
    cmp     ebp, 0x4                ; Must be Z_FINISH
    jne     .error_data
    
.check_busy:
    mov     ecx, [ebx+0x10]         ; avail_out
    test    ecx, ecx
    jne     .process
    mov     eax, [0x100294f0]       ; z_errmsg
    pop     edi
    pop     esi
    mov     [ebx+0x18], eax
    pop     ebp
    mov     eax, 0xfffffffb         ; Z_BUF_ERROR
    pop     ebx
    ret
    
.process:
    mov     ecx, [esi+0x20]         ; last_flush
    mov     [esi], ebx              ; Backlink
    mov     [esp+0x14], ecx         ; Save last_flush
    mov     [esi+0x20], ebp          ; Set flush
    cmp     eax, 0x2a               ; INIT_STATE
    jne     .check_init_done
    
    ; Initialize gzip header if needed
    mov     ecx, [esi+0x28]         ; w_bits
    mov     eax, [esi+0x7c]         ; level
    shl     ecx, 0xc                ; w_bits << 12
    sub     ecx, 0x7800             ; -30720
    dec     eax
    sar     eax, 0x1
    cmp     eax, 0x3
    jbe     .level_ok
    mov     eax, 0x3
    
.level_ok:
    shl     eax, 0x6                ; (level-1) << 6
    or      ecx, eax                ; Combine flags
    mov     eax, [esi+0x64]         ; gzhead
    test    eax, eax
    je      .no_gzhead
    or      ecx, 0x20               ; Set gzip header flag
    
.no_gzhead:
    mov     eax, ecx
    xor     edx, edx
    mov     edi, 0x1f
    mov     dword [esi+0x4], 0x71   ; BUSY_STATE
    div     edi                     ; Compute header CRC
    sub     ecx, edx
    add     ecx, edi
    push    ecx
    push    esi
    call    0x10001860              ; putShortMSB
    add     esp, 0x8
    
    ; Write gzip subfield if present
    mov     eax, [esi+0x64]         ; gzhead
    test    eax, eax
    je      .init_done
    mov     edx, [ebx+0x30]         ; adler
    shr     edx, 0x10
    push    edx
    push    esi
    call    0x10001860
    mov     eax, [ebx+0x30]
    and     eax, 0xffff
    push    eax
    push    esi
    call    0x10001860
    add     esp, 0x10
    
.init_done:
    mov     dword [ebx+0x30], 0x1   ; Reset adler
    
.check_init_done:
    mov     eax, [esi+0x14]         ; pending
    test    eax, eax
    je      .check_flush
    push    ebx
    call    0x10001890              ; flush_pending
    mov     eax, [ebx+0x10]         ; avail_out
    add     esp, 0x4
    test    eax, eax
    jne     .more_output
    mov     dword [esi+0x20], 0xffffffff
    pop     edi
    pop     esi
    pop     ebp
    xor     eax, eax                ; Z_OK
    pop     ebx
    ret
    
.more_output:
    cmp     ebp, 0x0                ; Z_NO_FLUSH
    jne     .process_flush
    cmp     [esi+0x4], dword 0x666  ; FINISHED
    jne     .check_done
    
.process_flush:
    ; Handle flush modes
    nop
    nop
    nop
    
.check_done:
    ; Handle more flush modes and states
    jmp     short $+2               ; Placeholder for continuation
    nop
    nop
    
.error_stream:
    pop     edi
    pop     esi
    pop     ebp
    mov     eax, 0xfffffffe         ; Z_STREAM_ERROR
    pop     ebx
    ret
    
.error_data:
    mov     edx, [0x100294e4]       ; z_errmsg
    pop     edi
    pop     esi
    mov     [ebx+0x18], edx
    pop     ebp
    mov     eax, 0xfffffffe         ; Z_STREAM_ERROR
    pop     ebx
    ret
    
.check_flush:
    ; Handle different flush modes
    jmp     .error_stream

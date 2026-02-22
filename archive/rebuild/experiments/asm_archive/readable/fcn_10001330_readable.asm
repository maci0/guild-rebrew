; fcn_10001330 - Deflate State Initialization (zlib)
; Address: 0x10001330
; Size: 505 bytes
; Initializes deflate_state structure for compression

BITS 32

org 0x10001330

fcn_10001330:
    mov     eax, [esp+0x1c]         ; level
    push    ebx
    push    ebp
    xor     edx, edx
    xor     ebp, ebp
    push    esi
    cmp     eax, edx
    push    edi
    je      .error_bad_param
    mov     ecx, [0x10027074]       ; zlib_version
    mov     al, [eax]               ; Check version byte
    cmp     al, [ecx]
    jne     .error_bad_param
    cmp     dword [esp+0x30], 0x38  ; stream_size check
    jne     .error_bad_param
    mov     edi, [esp+0x14]         ; strm
    cmp     edi, edx
    jne     .check_functions
    pop     edi
    pop     esi
    pop     ebp
    mov     eax, 0xfffffffe         ; Z_STREAM_ERROR
    pop     ebx
    ret
    
.check_functions:
    mov     eax, [edi+0x20]         ; zalloc
    mov     [edi+0x18], edx         ; Clear msg
    cmp     eax, edx
    jne     .check_free
    mov     dword [edi+0x20], 0x100092e0  ; Default zalloc
    mov     [edi+0x28], edx         ; Clear opaque
    
.check_free:
    cmp     [edi+0x24], edx         ; zfree
    jne     .check_params
    mov     dword [edi+0x24], 0x10009300  ; Default zfree
    
.check_params:
    mov     ecx, [esp+0x18]         ; method
    cmp     ecx, 0xffffffff
    jne     .validate_method
    mov     dword [esp+0x18], 0x6   ; Default method
    mov     ecx, [esp+0x18]
    
.validate_method:
    mov     ebx, [esp+0x20]         ; windowBits
    cmp     ebx, edx
    jge     .validate_window
    mov     ebp, 0x1
    neg     ebx
    
.validate_window:
    mov     eax, [esp+0x24]         ; memLevel
    cmp     eax, 0x1
    jl      .error_stream
    cmp     eax, 0x9
    jg      .error_stream
    cmp     dword [esp+0x1c], 0x8   ; level check
    jne     .error_stream
    cmp     ebx, 0x8
    jl      .error_stream
    cmp     ebx, 0xf
    jg      .error_stream
    cmp     ecx, edx
    jl      .error_stream
    cmp     ecx, 0x9
    jg      .error_stream
    mov     eax, [esp+0x28]         ; strategy
    cmp     eax, edx
    jl      .error_stream
    cmp     eax, 0x2
    jg      .error_stream
    
    ; Allocate deflate_state structure
    mov     edx, [edi+0x28]         ; zalloc
    push    0x16b8                  ; sizeof(deflate_state)
    push    0x1
    push    edx
    call    dword [edi+0x20]        ; Call zalloc
    mov     esi, eax
    add     esp, 0xc
    test    esi, esi
    jne     .init_state
    pop     edi
    pop     esi
    pop     ebp
    mov     eax, 0xfffffffc         ; Z_MEM_ERROR
    pop     ebx
    ret
    
.init_state:
    mov     [edi+0x1c], esi         ; Save state
    mov     [esi+0x18], ebp         ; Wrap mode
    mov     ebp, 0x1
    mov     ecx, ebx                ; windowBits
    shl     ebp, cl                 ; w_size = 1 << windowBits
    mov     [esi+0x28], ebx         ; Save windowBits
    mov     ebx, [esp+0x24]         ; memLevel
    mov     [esi], edi              ; Backlink to stream
    push    0x2
    lea     ecx, [ebx+0x7]          ; hash_bits = memLevel + 7
    mov     [esi+0x48], ecx         ; Save hash_bits
    mov     [esi+0x24], ebp         ; w_size
    lea     eax, [ebp-0x1]          ; w_mask
    push    ebp
    mov     [esi+0x2c], eax         ; Save w_mask
    mov     eax, 0x1
    shl     eax, cl                 ; hash_size = 1 << hash_bits
    add     ecx, 0x2
    mov     [esi+0x44], eax         ; Save hash_size
    dec     eax
    mov     [esi+0x4c], eax         ; hash_mask
    mov     eax, 0xaaaaaaab         ; Magic number for division
    mul     ecx                     ; Compute lit_bufsize
    shr     edx, 0x1
    mov     [esi+0x50], edx         ; Save lit_bufsize
    
    ; Allocate hash head array
    mov     ecx, [edi+0x28]         ; zalloc
    push    ecx
    call    dword [edi+0x20]
    mov     edx, [esi+0x24]         ; w_size
    mov     [esi+0x30], eax         ; Save head
    mov     eax, [edi+0x28]         ; zalloc
    push    0x2
    push    edx
    push    eax
    call    dword [edi+0x20]        ; Allocate prev array
    mov     ecx, [esi+0x44]         ; hash_size
    mov     [esi+0x38], eax         ; Save prev
    mov     edx, [edi+0x28]         ; zalloc
    push    0x2
    push    ecx
    push    edx
    call    dword [edi+0x20]        ; Allocate d_buf
    mov     [esi+0x3c], eax         ; Save d_buf
    
    ; Allocate pending buffer
    lea     ecx, [ebx+0x6]          ; lit_bits = memLevel + 6
    mov     eax, 0x1
    push    0x4
    shl     eax, cl                 ; lit_bufsize
    mov     [esi+0x1694], eax       ; Save lit_bufsize
    push    eax
    mov     eax, [edi+0x28]         ; zalloc
    push    eax
    call    dword [edi+0x20]
    add     esp, 0x30
    mov     [esi+0x8], eax          ; Save pending_buf
    mov     ecx, [esi+0x1694]       ; lit_bufsize
    lea     edx, [ecx*4+0x0]        ; Size of d_buf
    mov     [esi+0xc], edx          ; Save pending_buf_size
    
    ; Check allocations
    mov     edx, [esi+0x30]         ; head
    test    edx, edx
    je      .alloc_failed
    mov     edx, [esi+0x38]         ; prev
    test    edx, edx
    je      .alloc_failed
    mov     edx, [esi+0x3c]         ; d_buf
    test    edx, edx
    je      .alloc_failed
    test    eax, eax                ; pending_buf
    je      .alloc_failed
    
    ; Initialize buffers
    mov     edx, ecx                ; lit_bufsize
    push    edi                     ; strm
    shr     edx, 0x1                ; lit_bufsize / 2
    mov     byte [esi+0x1d], 0x8    ; method = DEFLATED
    lea     edx, [eax+edx*2]        ; overlay position
    lea     eax, [eax+ecx*2]
    add     ecx, eax
    mov     [esi+0x169c], edx       ; Save overlay
    mov     edx, [esp+0x2c]         ; strategy
    mov     [esi+0x1690], ecx       ; Save pending_buf end
    mov     ecx, [esp+0x1c]         ; level
    mov     [esi+0x80], edx         ; Save strategy
    mov     [esi+0x7c], ecx         ; Save level
    call    0x10001530              ; Initialize state
    add     esp, 0x4
    pop     edi
    pop     esi
    pop     ebp
    pop     ebx
    ret
    
.alloc_failed:
    mov     eax, [0x100294ec]       ; z_errmsg
    push    edi
    mov     [edi+0x18], eax         ; Set error message
    call    0x10001910              ; deflateEnd
    add     esp, 0x4
    pop     edi
    pop     esi
    pop     ebp
    mov     eax, 0xfffffffc         ; Z_MEM_ERROR
    pop     ebx
    ret
    
.error_bad_param:
    pop     edi
    pop     esi
    pop     ebp
    mov     eax, 0xfffffffa         ; Z_STREAM_ERROR
    pop     ebx
    ret
    
.error_stream:
    pop     edi
    pop     esi
    pop     ebp
    mov     eax, 0xfffffffe         ; Z_STREAM_ERROR
    pop     ebx
    ret

; fcn_10001bc0 - Slide Hash Window (zlib)
; Address: 0x10001bc0
; Size: 290 bytes
; Slides the hash window when it fills up

BITS 32

org 0x10001bc0

fcn_10001bc0:
    push    ebx
    mov     ebx, [esp+0x8]          ; deflate_state
    push    ebp
    push    esi
    mov     ebp, [ebx+0x24]         ; w_size (window size)
    push    edi
    mov     eax, [ebx+0x64]         ; strstart
    mov     edx, [ebx+0x34]         ; block_start
    mov     ecx, [ebx+0x6c]         ; lookahead
    sub     edx, eax                ; Calculate amount to slide
    sub     edx, ecx
    jne     .check_slide
    test    eax, eax
    jne     .return_dist
    test    ecx, ecx
    jne     .return_dist
    mov     edx, ebp                ; Slide full window size
    jmp     .do_slide
    
.check_slide:
    cmp     edx, 0xffffffff
    jne     .return_dist
    mov     edx, 0xfffffffe         ; Return -2
    jmp     .do_slide
    
.return_dist:
    mov     ecx, [ebx+0x24]         ; w_size
    lea     ecx, [ecx+ebp-0x106]    ; w_size + strstart - MAX_DIST
    cmp     eax, ecx
    jb      .do_slide               ; If strstart < threshold, no slide needed
    
    ; Slide the window
    mov     edi, [ebx+0x30]         ; window
    mov     ecx, ebp                ; w_size
    mov     eax, ecx
    lea     esi, [edi+ebp]          ; source = window + strstart
    shr     ecx, 0x2                ; Convert to DWORDs
    rep     movsd                   ; Move window contents
    mov     ecx, eax
    and     ecx, 0x3                ; Remaining bytes
    rep     movsb
    
    ; Update position counters
    mov     esi, [ebx+0x68]         ; match_start
    mov     ecx, [ebx+0x64]         ; strstart
    mov     eax, [ebx+0x54]         ; prev_match
    sub     esi, ebp                ; Decrease by slide amount
    sub     ecx, ebp
    mov     [ebx+0x68], esi
    mov     esi, [ebx+0x44]         ; prev_length
    mov     [ebx+0x64], ecx
    mov     ecx, [ebx+0x3c]         ; d_buf
    sub     eax, ebp
    mov     [ebx+0x54], eax
    
    ; Update hash head table
    lea     ecx, [ecx+esi*2]        ; Point to end of d_buf
    sub     ecx, 0x2
    xor     eax, eax
    
.head_loop:
    mov     ax, [ecx]               ; Get hash head
    cmp     eax, ebp
    jb      .zero_head
    sub     eax, ebp                ; Subtract slide amount
    jmp     .store_head
    
.zero_head:
    xor     eax, eax
    
.store_head:
    dec     esi
    mov     [ecx], ax               ; Store updated head
    jne     .head_loop
    
    ; Update hash prev table
    mov     eax, [ebx+0x38]         ; l_buf
    mov     esi, ebp                ; slide amount
    lea     ecx, [eax+ebp*2]        ; Point to end of l_buf
    sub     ecx, 0x2
    xor     eax, eax
    
.prev_loop:
    mov     ax, [ecx]               ; Get prev entry
    cmp     eax, ebp
    jb      .zero_prev
    sub     eax, ebp                ; Subtract slide amount
    jmp     .store_prev
    
.zero_prev:
    xor     eax, eax
    
.store_prev:
    dec     esi
    mov     [ecx], ax               ; Store updated prev
    jne     .prev_loop
    
    add     edx, ebp                ; Add slide to return value
    
.do_slide:
    mov     eax, [ebx]              ; z_stream
    mov     ecx, [eax+0x4]          ; avail_in
    test    ecx, ecx
    je      .done
    
    ; Read more data after sliding
    mov     ecx, [ebx+0x6c]         ; lookahead
    mov     esi, [ebx+0x64]         ; strstart
    push    edx
    mov     edx, [ebx+0x30]         ; window
    add     ecx, esi
    add     ecx, edx
    push    ecx
    push    eax
    call    0x10001cf0              ; read_buf
    add     esp, 0xc
    mov     ecx, [ebx+0x6c]
    add     ecx, eax
    mov     esi, ecx
    mov     [ebx+0x6c], ecx         ; Update lookahead
    cmp     esi, 0x3
    jb      .check_more
    mov     edx, [ebx+0x64]         ; strstart
    mov     eax, [ebx+0x30]         ; window
    mov     ecx, [ebx+0x50]         ; hash_shift
    lea     edi, [edx+eax]
    xor     eax, eax
    mov     al, [edi]               ; First byte
    mov     [ebx+0x40], eax         ; ins_h
    shl     eax, cl
    xor     ecx, ecx
    mov     cl, [edi+0x1]           ; Second byte
    xor     eax, ecx
    mov     ecx, [ebx+0x4c]         ; hash_mask
    and     eax, ecx
    mov     [ebx+0x40], eax         ; Update hash
    
.check_more:
    cmp     esi, 0x106              ; MIN_LOOKAHEAD
    jae     .done
    mov     edx, [ebx]
    mov     eax, [edx+0x4]          ; avail_in
    test    eax, eax
    jne     .do_slide               ; Read more if available
    
.done:
    pop     edi
    pop     esi
    pop     ebp
    pop     ebx
    ret

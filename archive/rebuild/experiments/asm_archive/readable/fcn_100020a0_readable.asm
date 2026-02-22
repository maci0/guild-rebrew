; fcn_100020a0 - Longest Match Search (zlib)
; Address: 0x100020a0
; Size: 367 bytes
; Finds longest match in hash chain for LZ77 compression

BITS 32

org 0x100020a0

fcn_100020a0:
    sub     esp, 0x14
    push    ebx
    push    ebp
    push    esi
    push    edi
    mov     edi, [esp+0x28]         ; deflate_state
    mov     esi, [edi+0x24]         ; w_size
    mov     eax, [edi+0x74]         ; max_chain_length
    mov     edx, [edi+0x64]         ; strstart
    mov     ecx, [edi+0x30]         ; window
    mov     ebp, [edi+0x70]         ; match_start
    mov     [esp+0x14], eax
    mov     eax, [edi+0x88]         ; lookahead
    lea     ebx, [esi-0x106]        ; w_size - MAX_DIST
    add     ecx, edx                ; window + strstart
    cmp     edx, ebx
    mov     [esp+0x18], eax
    jbe     .setup_match
    sub     edx, esi
    add     edx, 0x106              ; Calculate limit
    mov     [esp+0x1c], edx
    jmp     .get_prev
    
.setup_match:
    mov     dword [esp+0x1c], 0x0
    
.get_prev:
    mov     dl, [ecx+ebp-0x1]       ; Get previous byte
    lea     ebx, [ecx+0x102]        ; Match limit
    mov     [esp+0x28], dl
    mov     dl, [ecx+ebp]           ; Current byte
    mov     [esp+0x13], dl
    mov     edx, [edi+0x84]         ; nice_match
    cmp     ebp, edx
    jb      .check_match
    shr     dword [esp+0x14], 0x2   ; Reduce chain length
    
.check_match:
    mov     edx, [edi+0x6c]         ; prev_length
    cmp     eax, edx                ; Compare with max length
    mov     [esp+0x20], edx
    jbe     .match_limit
    mov     [esp+0x18], edx
    
.match_limit:
    mov     esi, [esp+0x2c]         ; cur_match
    mov     edx, [edi+0x30]         ; window
    mov     al, [esp+0x13]          ; Current byte
    add     edx, esi                ; match position
    cmp     [edx+ebp], al           ; Quick check
    jne     .no_match
    mov     al, [esp+0x28]          ; Previous byte
    cmp     [edx+ebp-0x1], al
    jne     .no_match
    mov     al, [edx]               ; Check first byte
    cmp     al, [ecx]
    jne     .no_match
    mov     al, [edx+0x1]           ; Check second byte
    inc     edx
    cmp     al, [ecx+0x1]
    jne     .no_match
    
    ; Found potential match - compare more bytes
    add     ecx, 0x2
    inc     edx
    
.compare_loop:
    mov     al, [ecx+0x1]
    inc     ecx
    inc     edx
    cmp     al, [edx]
    jne     .match_done
    mov     al, [ecx+0x1]
    inc     ecx
    inc     edx
    cmp     al, [edx]
    jne     .match_done
    mov     al, [ecx+0x1]
    inc     ecx
    inc     edx
    cmp     al, [edx]
    jne     .match_done
    mov     al, [ecx+0x1]
    inc     ecx
    inc     edx
    cmp     al, [edx]
    jne     .match_done
    mov     al, [ecx+0x1]
    inc     ecx
    inc     edx
    cmp     al, [edx]
    jne     .match_done
    mov     al, [ecx+0x1]
    inc     ecx
    inc     edx
    cmp     al, [edx]
    jne     .match_done
    mov     al, [ecx+0x1]
    inc     ecx
    inc     edx
    cmp     al, [edx]
    jne     .match_done
    mov     al, [ecx+0x1]
    inc     ecx
    inc     edx
    cmp     al, [edx]
    jne     .match_done
    cmp     ecx, ebx                ; Check match limit
    jb      .compare_loop
    
.match_done:
    mov     edx, ecx
    lea     ecx, [ebx-0x102]        ; Match start position
    sub     edx, ebx
    add     edx, 0x102              ; Match length
    cmp     edx, ebp
    jle     .no_match
    mov     eax, [esp+0x18]         ; max match
    mov     [edi+0x68], esi         ; match_start
    cmp     edx, eax
    mov     ebp, edx
    jge     .done
    mov     al, [edx+ecx-0x1]       ; Save previous bytes
    mov     dl, [edx+ecx]
    mov     [esp+0x28], al
    mov     [esp+0x13], dl
    
.no_match:
    mov     edx, [edi+0x2c]         ; w_mask
    mov     eax, [edi+0x38]         ; prev
    and     edx, esi                ; Hash chain index
    xor     esi, esi
    mov     si, [eax+edx*2]         ; Next in chain
    mov     eax, [esp+0x1c]         ; limit
    cmp     esi, eax
    jbe     .done
    mov     eax, [esp+0x14]         ; chain_length
    dec     eax
    mov     [esp+0x14], eax
    jne     .check_match
    
.done:
    mov     eax, [esp+0x20]         ; prev_length
    cmp     ebp, eax
    ja      .return_len
    mov     eax, ebp
    
.return_len:
    pop     edi
    pop     esi
    pop     ebp
    pop     ebx
    add     esp, 0x14
    ret

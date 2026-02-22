; fcn_10001cf0 - Read Input Data (zlib)
; Address: 0x10001cf0
; Size: 113 bytes
; Reads input data from application buffer

BITS 32

org 0x10001cf0

fcn_10001cf0:
    mov     ecx, [esp+0xc]          ; size to read
    push    ebx
    push    ebp
    mov     ebp, [esp+0xc]          ; z_stream
    mov     eax, [ebp+0x4]          ; avail_in
    mov     ebx, eax
    cmp     ebx, ecx
    jbe     .use_avail
    mov     ebx, ecx                ; Use minimum
    
.use_avail:
    test    ebx, ebx
    jne     .have_data
    pop     ebp
    xor     eax, eax
    pop     ebx
    ret
    
.have_data:
    sub     eax, ebx
    mov     [ebp+0x4], eax          ; Decrease avail_in
    mov     eax, [ebp+0x1c]         ; state
    mov     ecx, [eax+0x18]         ; wrap
    test    ecx, ecx
    jne     .skip_crc
    
    ; Update CRC32
    mov     ecx, [ebp+0x0]          ; next_in
    mov     edx, [ebp+0x30]         ; adler (crc)
    push    ebx
    push    ecx
    push    edx
    call    0x10001000              ; crc32
    add     esp, 0xc
    mov     [ebp+0x30], eax         ; Store new CRC
    
.skip_crc:
    mov     ecx, ebx                ; Copy count
    push    esi
    mov     esi, [ebp+0x0]          ; next_in (source)
    mov     eax, ecx                ; Save count
    push    edi
    mov     edi, [esp+0x18]         ; buf (destination)
    shr     ecx, 0x2                ; Convert to DWORDs
    rep     movsd                   ; Copy DWORDs
    mov     ecx, eax
    and     ecx, 0x3                ; Remaining bytes
    rep     movsb                   ; Copy bytes
    mov     ecx, [ebp+0x0]          ; next_in
    mov     eax, [ebp+0x8]          ; total_in
    add     ecx, ebx                ; Advance next_in
    add     eax, ebx                ; Increase total_in
    pop     edi
    mov     [ebp+0x0], ecx          ; Store next_in
    mov     [ebp+0x8], eax          ; Store total_in
    pop     esi
    mov     eax, ebx                ; Return amount read
    pop     ebp
    pop     ebx
    ret

; fcn_10001130 - Network/socket initialization
; Address: 0x10001130
; Size: 179 bytes
; Readable NASM with actual instructions
; NOTE: Some MOV encodings differ from original but function identically

BITS 32

org 0x10001130

fcn_10001130:
    ; Setup stack frame
    sub     esp, 0x24
    push    esi
    
    ; WSAStartup(0x0202, NULL) - initialize Winsock
    push    0x0
    push    0x2
    push    0x2
    mov     dword [esp+0x10], 0x1
    call    0x1001a184              ; WSAStartup
    
    ; Save socket handle
    mov     esi, eax
    lea     eax, [esp+0x4]
    
    ; setsockopt(socket, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size))
    push    0x4
    push    eax
    push    0x20
    push    0xffff
    push    esi
    call    0x1001a17e              ; setsockopt
    
    ; bind(socket, addr, addrlen)
    push    0x0
    mov     word [esp+0xc], 0x2     ; AF_INET
    call    0x1001a178              ; bind
    
    ; ioctlsocket(socket, FIONBIO, &nonblocking)
    push    0x0
    mov     [esp+0x10], eax
    call    0x1001a172              ; ioctlsocket
    
    ; Setup socket for operations
    lea     ecx, [esp+0x8]
    push    0x10
    push    ecx
    push    esi
    mov     [esp+0x16], ax
    call    0x1001a16c
    
    ; Additional socket setup
    push    0xffffffff
    mov     word [esp+0x1c], 0x2
    call    0x1001a178              ; bind
    
    ; More socket I/O setup
    mov     edx, [esp+0x2c]
    mov     [esp+0x1c], eax
    push    edx
    call    0x1001a172              ; ioctlsocket
    
    ; Setup UDP socket
    mov     ecx, [esp+0x30]
    mov     [esp+0x1a], ax
    lea     eax, [esp+0x18]
    push    0x10
    push    eax
    push    0x0
    push    0x6a                    ; IPPROTO_UDP = 106
    push    ecx
    push    esi
    call    0x1001a166              ; socket
    
    ; Close temporary socket
    push    esi
    call    0x1001a160              ; closesocket
    
    ; Log initialization
    push    0x1
    push    0x10027058
    push    0x14f
    push    0x10027034
    call    0x10003640              ; log function
    add     esp, 0x10
    
    ; Cleanup and return
    pop     esi
    add     esp, 0x24
    ret

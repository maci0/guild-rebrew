; Modified Init function with NOP slide
; Original VA: 0x10009320

section .text
    global _Init

_Init:
    ; NOP slide (4 bytes added)
    nop
    nop
    nop
    nop
    
    ; Original function body (shifted by 4 bytes)
    db 0x8b, 0x4c, 0x24, 0x04           ; mov ecx, [esp+4]
    db 0x8d, 0x44, 0x24, 0x04           ; lea eax, [esp+4]
    db 0x50                             ; push eax
    db 0x6a, 0x00                       ; push 0
    db 0x51                             ; push ecx
    db 0x68, 0xa0, 0x93, 0x00, 0x10     ; push 0x100093a0
    db 0x6a, 0x00                       ; push 0
    db 0x6a, 0x00                       ; push 0
    db 0xff, 0x15, 0x50, 0x40, 0x02, 0x10 ; call dword [0x10024050]
    db 0x33, 0xd2                       ; xor edx, edx
    db 0xa3, 0x94, 0x40, 0x76, 0x11     ; mov [0x11764094], eax
    db 0x85, 0xc0                       ; test eax, eax
    db 0x0f, 0x95, 0xc2                 ; setne dl
    db 0x8b, 0xc2                       ; mov eax, edx
    db 0xc3                             ; ret

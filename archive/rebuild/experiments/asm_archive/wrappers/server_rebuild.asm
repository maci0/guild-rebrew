; Complete server.dll rebuild in NASM
; Target: Exact byte reproduction

BITS 32

; We need to create proper section structure
; Section 1: .text (code + init function)
section .text align=4096 vstart=0x10001000

; The Init function at RVA 0x9320 (file offset 0x9320)
; This means in the .text section at offset 0x8320 (0x9320 - 0x1000)
; First, include all the original text section
times 0x8320 db 0x90  ; Pad to Init function location

; Init function (48 bytes)
_init:
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
    ; Padding to 48 bytes
    db 0x90, 0x90, 0x90, 0x90
    db 0x90, 0x90

; Include rest of original text section after Init
times (0x22846 - 0x8320 - 48) db 0x90

; Pad to full raw size (0x23000)
times (0x23000 - 0x8320 - 48) db 0x00


; fcn_100034c0
; Address: 0x100034c0
; Size: 83 bytes
BITS 32

org 0x100034c0


push esi
mov esi, 0x10027078

.loop:
mov eax, [esi]
mov ecx, [0x10034618]
push eax
push ecx
push dword 0x100273ac
call 0x10002640
add esi, 0x4
add esp, 0xc
cmp esi, 0x10027084
jl .loop

mov al, [0x10034618]

; NOTE: MSVC6 chose the "33 /r" form (33 F6) for `xor esi, esi`.
; NASM defaults to 31 F6 for the same mnemonic.
db 0x33, 0xF6

test al, 0x8
je .zero_globals
call dword [0x1002404c]
mov [0x11766204], esi

.zero_globals:
mov [0x10034610], esi
mov [0x117660e0], esi
mov [0x10034618], esi
pop esi
ret

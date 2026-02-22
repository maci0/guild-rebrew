; fcn_10003170
; Address: 0x10003170
; Size: 95 bytes
BITS 32


sub esp, 0x1c
; Encoding note: original uses 8D 44 24 00 (disp8=0) not 8D 04 24.
db 0x8D, 0x44, 0x24, 0x00

push byte 0x1c
push eax
push dword 0x10003170
call dword [0x10024018]

mov ecx, [esp+0x20]
and ecx, 0xff
lea eax, [ecx-0x2]
cmp eax, 0x7e
ja .ret_false_al

; NOTE: MSVC6 chose the "33 /r" form (33 D2) for `xor edx, edx`.
; NASM defaults to 31 D2 for the same mnemonic.
db 0x33, 0xD2

mov dl, byte [eax+0x100031dc]
jmp dword [edx*4 + 0x100031d0]

.case_a6:
mov eax, [esp+0x14]
cmp eax, 0x2
je .ret_true_eax
cmp eax, 0x4
je .ret_true_eax

; NOTE: MSVC6 chose the "33 /r" form (33 C0) for `xor eax, eax`.
; NASM defaults to 31 C0 for the same mnemonic.
db 0x33, 0xC0
add esp, 0x1c
ret

.ret_true_eax:
mov eax, 0x1
add esp, 0x1c
ret

.ret_true_al:
mov al, 0x1
add esp, 0x1c
ret

.ret_false_al:
; NOTE: MSVC6 chose the "32 /r" form (32 C0) for `xor al, al`.
; NASM defaults to 30 C0 for the same mnemonic.
db 0x32, 0xC0
add esp, 0x1c
ret

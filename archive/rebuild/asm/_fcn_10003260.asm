; fcn_10003260
; Address: 0x10003260
; Size: 183 bytes
BITS 32


; arg0 = [esp+0x04] : pointer to the *end* of an instruction sequence
; arg1 = [esp+0x08] : available bytes before arg0
; arg2 = [esp+0x0c] : VA corresponding to arg0 (used for E8 rel32 target)
; arg3 = [esp+0x10] : out pointer (DWORD) for resolved target; always zeroed on entry

mov ecx, [esp+0x10]
mov edx, [esp+0x08]
mov eax, [esp+0x04]
cmp edx, 0x5
push ebx
mov dword [ecx], 0x0

; Case: E8 rel32
jl .check_ff14
cmp byte [eax-0x5], 0xE8
jne .check_ff14
mov eax, [eax-0x4]
mov edx, [esp+0x10]
; NOTE: MSVC6 chose the "03 /r" form (03 C2) for `add eax, edx`.
; NASM defaults to 01 D0 for the same mnemonic.
db 0x03, 0xC2
pop ebx
mov [ecx], eax
mov al, 0x1
ret

.check_ff14:
or bl, 0xFF

; Case: FF ?? 14
cmp edx, 0x3
jl .check_ff15
cmp byte [eax-0x3], bl
jne .check_ff15
cmp byte [eax-0x2], 0x14
jne .check_ff15
mov al, 0x2
pop ebx
ret

.check_ff15:
; Case: FF 15 imm32
cmp edx, 0x6
jl .check_ff_group
cmp byte [eax-0x6], bl
jne .check_ff_group
cmp byte [eax-0x5], 0x15
jne .check_ff_group
mov al, 0x2
pop ebx
ret

.check_ff_group:
; Cases starting with 0xFF at [eax-2]
cmp edx, 0x2
jl .check_ff50
mov cl, byte [eax-0x2]
; NOTE: MSVC6 chose the "3A /r" form (3A CB) for `cmp cl, bl`.
; NASM defaults to 38 D9 for the same mnemonic.
db 0x3A, 0xCB
jne .check_ff50
cmp byte [eax-0x1], 0x40
jae .check_ffd0
mov al, 0x2
pop ebx
ret

.check_ffd0:
; NOTE: MSVC6 chose the "3A /r" form (3A CB) for `cmp cl, bl`.
; NASM defaults to 38 D9 for the same mnemonic.
db 0x3A, 0xCB
jne .check_ff50
mov cl, byte [eax-0x1]
and cl, 0xF8
cmp cl, 0xD0
jne .check_ff50
mov al, 0x2
pop ebx
ret

.check_ff50:
; Case: FF 50 disp8 (call [reg+disp8])
cmp edx, 0x3
jl .check_ff90
cmp byte [eax-0x3], bl
jne .check_ff90
mov cl, byte [eax-0x2]
and cl, 0xF8
cmp cl, 0x50
jne .check_ff90
mov al, 0x2
pop ebx
ret

.check_ff90:
; Case: FF 90 disp32 (call [reg+disp32])
cmp edx, 0x7
jl .ret_false
cmp byte [eax-0x7], bl
jne .ret_false
mov dl, byte [eax-0x6]
and dl, 0xF8
cmp dl, 0x90
jne .ret_false
mov al, 0x2
pop ebx
ret

.ret_false:
; NOTE: MSVC6 chose the "32 /r" form (32 C0) for `xor al, al`.
; NASM defaults to 30 C0 for the same mnemonic.
db 0x32, 0xC0
pop ebx
ret

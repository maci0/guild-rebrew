; fcn_10003820
; Address: 0x10003820
; Size: 114 bytes
; FUNCTION: SERVER 0x10003820
BITS 32

org 0x10003820

push esi
mov esi, [esp+0x8]

mov eax, [esi+0x3c]
test eax, eax
je .check_have_byte

or eax, 0xffffffff
pop esi
ret

.check_have_byte:
mov eax, [esi+0x4]
test eax, eax
jnz .consume

call 0x1001A7E5
mov dword [eax], 0x0

mov eax, [esi+0x40]
mov ecx, [esi+0x44]
push eax
push dword 0x4000
push byte 0x1
push ecx
call 0x1001AA6A
add esp, 0x10
mov [esi+0x4], eax
test eax, eax
jnz .set_ptr

mov edx, [esi+0x40]
mov dword [esi+0x3c], 0x1
or eax, 0xffffffff
test byte [edx+0xc], 0x20
jz .epilogue

mov [esi+0x38], eax
pop esi
ret

.set_ptr:
mov eax, [esi+0x44]
mov [esi], eax

.consume:
mov eax, [esi+0x4]
; NOTE: MSVC6 used 33 C9 for `xor ecx, ecx` (NASM prefers 31 C9).
db 0x33, 0xC9
dec eax
mov [esi+0x4], eax
mov eax, [esi]
mov cl, [eax]
inc eax
mov [esi], eax

; NOTE: MSVC6 used 8B C1 for `mov eax, ecx` (NASM may choose 89 C8).
db 0x8B, 0xC1

.epilogue:
pop esi
ret

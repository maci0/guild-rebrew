; fcn_100038a0
; Address: 0x100038a0
; Size: 177 bytes
; FUNCTION: SERVER 0x100038a0
BITS 32

org 0x100038a0

push esi
mov esi, [esp+0x8]
push edi

; NOTE: MSVC6 used 33 FF for `xor edi, edi` (NASM prefers 31 FF).
db 0x33, 0xFF

test esi, esi
jnz .have_ctx

pop edi
mov eax, 0xFFFFFFFE
pop esi
ret

.have_ctx:
mov eax, [esi+0x50]
test eax, eax
je .check_inner
push eax
call 0x1001AB81
add esp, 0x4

.check_inner:
mov eax, [esi+0x1c]
test eax, eax
je .check_buf

mov al, [esi+0x5c]
cmp al, 0x77
jne .check_r
push esi
call 0x10001910
jmp .after_sub

.check_r:
cmp al, 0x72
jne .check_buf
push esi
call 0x10005770

.after_sub:
add esp, 0x4
; NOTE: MSVC6 used 8B F8 for `mov edi, eax` (NASM prefers 89 C7).
db 0x8B, 0xF8

.check_buf:
mov eax, [esi+0x40]
test eax, eax
je .check_status

push eax
call 0x1001A18A
add esp, 0x4
test eax, eax
je .check_status

call 0x1001A7E5
cmp dword [eax], 0x1d
je .check_status
or edi, 0xFFFFFFFF

.check_status:
mov eax, [esi+0x38]
test eax, eax
jge .free_fields

; NOTE: MSVC6 used 8B F8 for `mov edi, eax` (NASM prefers 89 C7).
db 0x8B, 0xF8

.free_fields:
mov eax, [esi+0x44]
test eax, eax
je .free_48
push eax
call 0x1001AB81
add esp, 0x4

.free_48:
mov eax, [esi+0x48]
test eax, eax
je .free_54
push eax
call 0x1001AB81
add esp, 0x4

.free_54:
mov eax, [esi+0x54]
test eax, eax
je .free_self
push eax
call 0x1001AB81
add esp, 0x4

.free_self:
push esi
call 0x1001AB81
add esp, 0x4

; NOTE: MSVC6 used 8B C7 for `mov eax, edi` (NASM prefers 89 F8).
db 0x8B, 0xC7

pop edi
pop esi
ret

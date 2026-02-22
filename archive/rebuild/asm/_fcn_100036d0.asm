; fcn_100036d0
; Address: 0x100036d0
; Size: 332 bytes
BITS 32

org 0x100036d0


push ebx
push esi
mov esi, [esp+0xc]
push edi

; NOTE: MSVC6 used 33 DB for `xor ebx, ebx` (NASM prefers 31 DB).
db 0x33, 0xDB

mov edi, 0x10027488

.chk_loop:
push esi
call 0x10003820
mov ecx, [edi]
add esp, 0x4

; NOTE: MSVC6 used 3B C1 for `cmp eax, ecx` (NASM may choose 39 C8).
db 0x3B, 0xC1
jne near .mismatch

add edi, 0x4
inc ebx
cmp edi, 0x10027490
jb short .chk_loop

push esi
call 0x10003820

push esi
; NOTE: MSVC6 used 8B F8 for `mov edi, eax` (NASM prefers 89 C7).
db 0x8B, 0xF8
call 0x10003820
add esp, 0x8

cmp edi, 0x8
; NOTE: MSVC6 used 8B D8 for `mov ebx, eax` (NASM prefers 89 C3).
db 0x8B, 0xD8
jne near .bad

test bl, 0xe0
jne near .bad

mov edi, 0x6
.skip6:
push esi
call 0x10003820
add esp, 0x4
dec edi
jne .skip6

test bl, 0x4
je .after_len

push esi
call 0x10003820

push esi
; mov edi, eax (8B F8)
db 0x8B, 0xF8
call 0x10003820

shl eax, 0x8
; NOTE: MSVC6 used 03 F8 for `add edi, eax` (NASM may choose 01 C7).
db 0x03, 0xF8
add esp, 0x8

; NOTE: MSVC6 used 8B CF for `mov ecx, edi` (NASM may choose 89 F9).
db 0x8B, 0xCF
dec edi
test ecx, ecx
je .after_len

.skip_len_loop:
push esi
call 0x10003820
add esp, 0x4
cmp eax, byte -1
je .after_len
; NOTE: MSVC6 used 8B D7 for `mov edx, edi` (NASM may choose 89 FA).
db 0x8B, 0xD7
dec edi
test edx, edx
jne .skip_len_loop

.after_len:
test bl, 0x8
je .after8

push esi
call 0x10003820
add esp, 0x4
test eax, eax
je .after8

.loop8_cmp:
cmp eax, byte -1
je .after8
push esi
call 0x10003820
add esp, 0x4
test eax, eax
jne .loop8_cmp

.after8:
test bl, 0x10
je .after10

push esi
call 0x10003820
add esp, 0x4
test eax, eax
je .after10

.loop10_cmp:
cmp eax, byte -1
je .after10
push esi
call 0x10003820
add esp, 0x4
test eax, eax
jne .loop10_cmp

.after10:
test bl, 0x2
je .final_status

mov edi, 0x2
.skip2:
push esi
call 0x10003820
add esp, 0x4
dec edi
jne .skip2

.final_status:
mov eax, [esi+0x3c]
pop edi
neg eax
; NOTE: MSVC6 used 1B C0 for `sbb eax, eax` (NASM may choose 19 C0).
db 0x1B, 0xC0
and al, 0xfd
mov [esi+0x38], eax
pop esi
pop ebx
ret

.mismatch:
test ebx, ebx
je .mismatch2
mov edx, [esi+0x4]
mov ecx, [esi]
inc edx
dec ecx
mov [esi+0x4], edx
mov [esi], ecx

.mismatch2:
cmp eax, byte -1
je .set_done

mov ecx, [esi+0x4]
mov eax, [esi]
inc ecx
dec eax
mov [esi+0x4], ecx
mov [esi], eax
mov dword [esi+0x58], 0x1

.set_done:
mov ecx, [esi+0x4]
; NOTE: MSVC6 used 33 C0 for `xor eax, eax` (NASM prefers 31 C0).
db 0x33, 0xC0
test ecx, ecx
sete al
mov [esi+0x38], eax
pop edi
pop esi
pop ebx
ret

.bad:
mov dword [esi+0x38], 0xfffffffd
pop edi
pop esi
pop ebx
ret

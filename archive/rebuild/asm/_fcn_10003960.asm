; fcn_10003960
; Address: 0x10003960
; Size: 559 bytes
; FUNCTION: SERVER 0x10003960
BITS 32

org 0x10003960

push ecx
mov ecx, [esp+0xc]
push ebx
push ebp
mov ebp, [esp+0x10]
push esi
push edi
test ebp, ebp
; NOTE: MSVC6 used 8B F1 for `mov esi, ecx` (NASM prefers 89 CE).
db 0x8B, 0xF1
jz near .ret_badarg

cmp byte [ebp+0x5c], 0x72
jnz near .ret_badarg

mov eax, [ebp+0x38]
cmp eax, 0xfffffffd
jz near .ret_minus1
cmp eax, 0xffffffff
jz near .ret_minus1
cmp eax, 0x1
jnz .not_done

pop edi
pop esi
pop ebp
; NOTE: MSVC6 used 33 C0 for `xor eax, eax` (NASM prefers 31 C0).
db 0x33, 0xC0
pop ebx
pop ecx
ret

.not_done:
mov ebx, [esp+0x20]
mov [esp+0x10], ecx
test ebx, ebx
mov [ebp+0xc], ecx
mov [ebp+0x10], ebx
jz near .final_crc

.loop_top:
mov eax, [ebp+0x58]
test eax, eax
mov eax, [ebp+0x4]
jnz near .copy_from_buf

test eax, eax
jnz .call_step

mov eax, [ebp+0x3c]
test eax, eax
jnz .call_step

call 0x1001A7E5
mov dword [eax], 0x0
mov eax, [ebp+0x40]
mov ecx, [ebp+0x44]
push eax
push dword 0x4000
push byte 0x1
push ecx
call 0x1001AA6A
add esp, 0x10
mov [ebp+0x4], eax
test eax, eax
jnz .set_ptr

mov edx, [ebp+0x40]
mov dword [ebp+0x3c], 0x1
test byte [edx+0xc], 0x20
jnz near .set_status_minus1

.set_ptr:
mov eax, [ebp+0x44]
mov [ebp+0x0], eax

.call_step:
push byte 0x0
push ebp
call 0x100058D0
add esp, 0x8
cmp eax, 0x1
mov [ebp+0x38], eax
jnz .after_step

mov ecx, [ebp+0xc]
mov edx, [ebp+0x4c]
; NOTE: MSVC6 used 2B CE for `sub ecx, esi` (NASM prefers 29 F1).
db 0x2B, 0xCE
push ecx
push esi
push edx
call 0x100011F0
mov [ebp+0x4c], eax
mov eax, [ebp+0xc]
push ebp
mov [esp+0x28], eax
call 0x10003C50
mov ecx, [ebp+0x4c]
add esp, 0x10
; NOTE: MSVC6 used 3B C1 for `cmp eax, ecx` (NASM prefers 39 C8).
db 0x3B, 0xC1
jz .crc_ok

mov dword [ebp+0x38], 0xfffffffd
jmp .after_crc

.crc_ok:
push ebp
call 0x10003C50
push ebp
call 0x100036D0
mov eax, [ebp+0x38]
add esp, 0x8
test eax, eax
jnz .after_crc

mov esi, [ebp+0x8]
mov edi, [ebp+0x14]
push ebp
call 0x10005720
push byte 0x0
push byte 0x0
push byte 0x0
mov [ebp+0x8], esi
mov [ebp+0x14], edi
call 0x100011F0
add esp, 0x10
mov [ebp+0x4c], eax

.after_crc:
mov esi, [esp+0x18]

.after_step:
mov eax, [ebp+0x38]
test eax, eax
jnz near .final_crc

mov eax, [ebp+0x3c]
test eax, eax
jnz near .final_crc

mov eax, [ebp+0x10]
test eax, eax
jnz near .loop_top

jmp near .final_crc

.copy_from_buf:
mov ecx, [ebp+0x10]
; NOTE: MSVC6 used 3B C1 for `cmp eax, ecx` (NASM prefers 39 C8).
db 0x3B, 0xC1
jbe .le_count
; NOTE: MSVC6 used 8B C1 for `mov eax, ecx` (NASM may choose 89 C8).
db 0x8B, 0xC1

.le_count:
test eax, eax
jbe .after_copy

mov esi, [ebp+0x0]
mov edi, [ebp+0xc]
mov ecx, eax
mov edx, ecx
shr ecx, 0x2
rep movsd
mov ecx, edx
and ecx, 0x3
rep movsb

mov ecx, [esp+0x1c]
mov esi, [ebp+0x0]
mov edx, [ebp+0x10]
add ecx, eax
mov [esp+0x10], ecx
mov [ebp+0xc], ecx
mov ecx, [ebp+0x4]
add esi, eax
sub edx, eax
sub ecx, eax
mov [ebp+0x0], esi
mov [ebp+0x10], edx
mov [ebp+0x4], ecx

.after_copy:
mov eax, [ebp+0x10]
test eax, eax
jbe .adjust_out

mov edx, [ebp+0x40]
push edx
push eax
mov eax, [esp+0x18]
push byte 0x1
push eax
call 0x1001AA6A
mov ecx, [ebp+0x10]
add esp, 0x10
sub ecx, eax
mov [ebp+0x10], ecx

.adjust_out:
mov esi, [ebp+0x10]
mov edx, [ebp+0x8]
mov ecx, [ebp+0x14]
sub ebx, esi
add edx, ebx
add ecx, ebx
test ebx, ebx
mov [ebp+0x8], edx
mov [ebp+0x14], ecx
jnz .ret_len

mov dword [ebp+0x3c], 0x1

.ret_len:
pop edi
pop esi
; NOTE: MSVC6 used 8B C3 for `mov eax, ebx` (NASM may choose 89 D8).
db 0x8B, 0xC3
pop ebp
pop ebx
pop ecx
ret

.set_status_minus1:
mov dword [ebp+0x38], 0xffffffff

.final_crc:
mov ecx, [ebp+0xc]
mov edx, [ebp+0x4c]
sub ecx, esi
push ecx
push esi
push edx
call 0x100011F0
mov ecx, [ebp+0x10]
add esp, 0xc
mov [ebp+0x4c], eax
; NOTE: MSVC6 used 8B C3 for `mov eax, ebx` (NASM may choose 89 D8).
db 0x8B, 0xC3
pop edi
pop esi
pop ebp
; NOTE: MSVC6 used 2B C1 for `sub eax, ecx` (NASM prefers 29 C8).
db 0x2B, 0xC1
pop ebx
pop ecx
ret

.ret_minus1:
pop edi
pop esi
pop ebp
or eax, 0xffffffff
pop ebx
pop ecx
ret

.ret_badarg:
pop edi
pop esi
pop ebp
mov eax, 0xFFFFFFFE
pop ebx
pop ecx
ret

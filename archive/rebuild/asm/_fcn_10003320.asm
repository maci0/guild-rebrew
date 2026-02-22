; fcn_10003320
; Address: 0x10003320
; Size: 404 bytes
BITS 32

org 0x10003320


; Large initialization/dispatch routine.

sub esp, 0x208

mov eax, [esp+0x20c]
mov ecx, [esp+0x210]
mov [0x10034610], eax

mov eax, [esp+0x218]
mov [0x10034618], eax

push esi
mov esi, [esp+0x218]

push dword 0x10002770
shr eax, 0x4
and al, 0x1
mov [0x10034614], ecx
mov [0x117660e0], esi
mov [0x1003461c], al
call dword [0x10024040]

push byte 0x0
call 0x1001a567
add esp, 0x4

lea edx, [esp+0x10c]
mov [esp+0x4], eax
push dword 0x100
push edx
push esi
call dword [0x1002414c]

push dword 0x104
push dword 0x11766100
push byte 0x0
call dword [0x1002403c]

push byte 0x5c
push dword 0x11766100
call 0x1001a540
mov byte [eax], 0x0

lea eax, [esp+0xc]
push eax
call 0x1001a527

lea ecx, [esp+0x118]
push eax
push ecx
push dword 0x1002735c
push dword 0x117640e0
call 0x1001a299

mov al, [0x10034618]
add esp, 0x1c
test al, 0x1
je near .no_table_loop

push edi
mov edi, 0x10027084

.loop_table:
push edi
push dword 0x11766100
lea edx, [esp+0x14]
push dword 0x100270fc
push edx
call 0x1001a299

lea eax, [esp+0x1c]
push dword 0x100270f8
push eax
call 0x1001a286

; NOTE: MSVC6 used 8B F0 for `mov esi, eax` (NASM prefers 89 C6).
db 0x8B, 0xF0
add esp, 0x18
test esi, esi
je .next_table

push byte 0x2
push byte 0x0
push esi
call 0x1001a46e

push esi
call 0x1001a2eb
add esp, 0x10

cmp eax, 0x10000
jle .after_large

push esi
call 0x1001a18a
lea ecx, [esp+0x10]
push dword 0x10027358
push ecx
call 0x1001a286
; NOTE: MSVC6 used 8B F0 for `mov esi, eax` (NASM prefers 89 C6).
db 0x8B, 0xF0
push esi
push dword 0x1002733c
call 0x1001a207
add esp, 0x14

.after_large:
push esi
call 0x1001a18a
add esp, 0x4

.next_table:
add edi, 0x20
cmp edi, 0x100270e4
jl .loop_table
pop edi

.no_table_loop:
test byte [0x10034618], 0x8
je .log_loop

call dword [0x10024048]
push byte -11
call dword [0x10024044]
mov [0x11766204], eax

.log_loop:
mov esi, 0x10027078

.loop_log:
mov edx, [esi]
mov eax, [0x10034618]
push edx
push eax
push dword 0x117640e0
call 0x10002640
add esi, 0x4
add esp, 0xc
cmp esi, 0x10027084
jl .loop_log

pop esi
add esp, 0x208
ret

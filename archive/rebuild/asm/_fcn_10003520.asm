; fcn_10003520
; Address: 0x10003520
; Size: 160 bytes
BITS 32

org 0x10003520


mov eax, [0x10034610]
test eax, eax
jne .have_cb

push byte 0x30
push dword 0x10027424
push dword 0x100273fc
push byte 0x0
call dword [0x10024148]
.ret:
ret

.have_cb:
mov eax, [0x10034618]
test eax, eax
je .ret

test al, 0x0f
je .post_format

mov eax, [esp+0xc]
mov ecx, [esp+0x8]
mov edx, [esp+0x4]
push eax
push ecx
push edx
push dword 0x100273e0
push dword 0x117640e0
call 0x1001a299
add esp, 0x14
mov eax, [0x10034618]

.post_format:
test al, 0x0d
je .maybe_notify

push byte 0x1
push eax
push dword 0x117640e0
call 0x10002640
mov eax, [0x10034618]
add esp, 0xc

.maybe_notify:
test al, 0x2
je .ret

mov eax, [0x117660e0]
push dword 0x124
push dword 0x100273c4
push dword 0x117640e0
push eax
call dword [0x10024148]
cmp eax, 0x6
jne .ret

call dword [0x10034610]
push byte 0x0f
call 0x1001a670

nop
nop
nop
nop
nop

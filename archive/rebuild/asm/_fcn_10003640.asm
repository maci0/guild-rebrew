; fcn_10003640
; Address: 0x10003640
; Size: 132 bytes
BITS 32

org 0x10003640


mov eax, [0x10034610]
test eax, eax
jne .have_cb

push dword 0x10030
push dword 0x10027424
push dword 0x100273fc
push byte 0x0
call dword [0x10024148]
ret

.have_cb:
mov al, [0x10034618]
test al, 0x1
je .ret

mov ecx, [esp+0x8]
mov edx, [esp+0x4]
test al, 0x20
mov eax, [esp+0xc]
push eax
push ecx
push edx
je .fmt_simple

call dword [0x10024154]
push eax
push dword 0x10027464
push dword 0x117640e0
call 0x1001a299
add esp, 0x18
jmp .after_fmt

.fmt_simple:
push dword 0x10027448
push dword 0x117640e0
call 0x1001a299
add esp, 0x14

.after_fmt:
mov eax, [esp+0x10]
mov ecx, [0x10034618]
push eax
push ecx
push dword 0x117640e0
call 0x10002640
add esp, 0xc

.ret:
ret

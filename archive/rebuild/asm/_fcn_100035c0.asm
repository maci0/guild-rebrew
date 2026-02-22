; fcn_100035c0
; Address: 0x100035c0
; Size: 119 bytes
BITS 32

org 0x100035c0


mov eax, [0x10034610]
push esi
test eax, eax
jne .have_cb

push dword 0x10030
push dword 0x10027424
push dword 0x100273fc
push byte 0x0
call dword [0x10024148]
pop esi
ret

.have_cb:
mov eax, [0x10034618]
test eax, eax
je .ret_pop

mov esi, [esp+0x8]
test al, 0x0d
je .maybe_notify

push esi
push dword 0x10027438
push dword 0x117640e0
call 0x1001a299

mov eax, [0x10034618]
push byte 0x1
push eax
push dword 0x117640e0
call 0x10002640
mov eax, [0x10034618]
add esp, 0x18

.maybe_notify:
test al, 0x2
je .ret_pop

push dword 0x1030
push dword 0x1002742c
push esi
push byte 0x0
call dword [0x10024148]

.ret_pop:
pop esi
ret

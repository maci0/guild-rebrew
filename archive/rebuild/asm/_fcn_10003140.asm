; fcn_10003140
; Address: 0x10003140
; Size: 33 bytes
; FUNCTION: SERVER 0x10003140
BITS 32


; Summary:
; - arg0 = [esp+4] (table base)
; - arg1 = [esp+8] (index)
; - returns pointer to the indexed variable-length entry, or NULL if out of range

mov eax, [esp+0x4]
mov ecx, [esp+0x8]

cmp ecx, [eax+0x4]
jae .out_of_range

add eax, 0x10
test ecx, ecx
jbe .ret

.loop:
mov edx, [eax]
dec ecx
lea eax, [eax+edx+0x4]
jne .loop
ret

.out_of_range:
; NOTE: MSVC6 chose the "33 /r" form (33 C0). NASM encodes `xor eax, eax`
; as 31 C0 by default and doesn't provide a syntax knob to select 33 /r here.
db 0x33, 0xC0
.ret:
ret

; fcn_10006f40 - zlib deflate state initialization/clear function
; Address: 0x10006f40
; Size: 102 bytes (0x66)
; Returns: void
; Arguments: [esp+4] = pointer to deflate_state structure
; Description: Clears/initializes deflate state structure arrays and fields

BITS 32

; Function starts at 0x10006f40 (file offset 0x6f40)
db 0x8b, 0x54, 0x24, 0x04    ; 10006f40: mov    edx,DWORD PTR [esp+0x4]
db 0x56                      ; 10006f44: push   esi
db 0xb9, 0x1e, 0x01, 0x00, 0x00  ; 10006f45: mov    ecx,0x11e (286 iterations)
db 0x33, 0xf6                ; 10006f4a: xor    esi,esi  ; esi = 0

; Clear first array at offset 0x8c (286 WORD entries)
; Loop: for (i=0x11e; i>0; i--) state->array1[i] = 0
db 0x8d, 0x82, 0x8c, 0x00, 0x00, 0x00  ; 10006f4c: lea    eax,[edx+0x8c]
; Loop start at 0x10006f52
db 0x66, 0x89, 0x30          ; 10006f52: mov    WORD PTR [eax],si
db 0x83, 0xc0, 0x04          ; 10006f55: add    eax,0x4
db 0x49                      ; 10006f58: dec    ecx
db 0x75, 0xf7                ; 10006f59: jne    0x10006f52 (loop back)

; Clear second array at offset 0x980 (30 WORD entries)
db 0x8d, 0x82, 0x80, 0x09, 0x00, 0x00  ; 10006f5b: lea    eax,[edx+0x980]
db 0xb9, 0x1e, 0x00, 0x00, 0x00  ; 10006f61: mov    ecx,0x1e (30 iterations)
; Loop start at 0x10006f66
db 0x66, 0x89, 0x30          ; 10006f66: mov    WORD PTR [eax],si
db 0x83, 0xc0, 0x04          ; 10006f69: add    eax,0x4
db 0x49                      ; 10006f6c: dec    ecx
db 0x75, 0xf7                ; 10006f6d: jne    0x10006f66 (loop back)

; Clear third array at offset 0xa74 (19 WORD entries)
db 0x8d, 0x82, 0x74, 0x0a, 0x00, 0x00  ; 10006f6f: lea    eax,[edx+0xa74]
db 0xb9, 0x13, 0x00, 0x00, 0x00  ; 10006f75: mov    ecx,0x13 (19 iterations)
; Loop start at 0x10006f7a
db 0x66, 0x89, 0x30          ; 10006f7a: mov    WORD PTR [eax],si
db 0x83, 0xc0, 0x04          ; 10006f7d: add    eax,0x4
db 0x49                      ; 10006f80: dec    ecx
db 0x75, 0xf7                ; 10006f81: jne    0x10006f7a (loop back)

; Clear DWORD fields at various offsets
db 0x89, 0xb2, 0xa4, 0x16, 0x00, 0x00  ; 10006f83: mov    DWORD PTR [edx+0x16a4],esi
db 0x89, 0xb2, 0xa0, 0x16, 0x00, 0x00  ; 10006f89: mov    DWORD PTR [edx+0x16a0],esi
db 0x89, 0xb2, 0xa8, 0x16, 0x00, 0x00  ; 10006f8f: mov    DWORD PTR [edx+0x16a8],esi
db 0x89, 0xb2, 0x98, 0x16, 0x00, 0x00  ; 10006f95: mov    DWORD PTR [edx+0x1698],esi

; Set WORD field to 1 at offset 0x48c
db 0x66, 0xc7, 0x82, 0x8c, 0x04, 0x00, 0x00  ; 10006f9b: mov    WORD PTR [edx+0x48c],...
db 0x01, 0x00                ; ...0x1

; Function epilog
db 0x5e                      ; 10006fa4: pop    esi
db 0xc3                      ; 10006fa5: ret

; Note: 10 NOPs (0x90) follow for alignment (0x10006fa6 - 0x10006faf)

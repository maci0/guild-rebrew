; Complete DLL reconstruction in NASM
; Target: server.dll with exact byte reproduction

; Section: .text (Code)
; Virtual Address: 0x10001000
; File Offset: 0x1000
section .text align=4096 vstart=0x10001000

; Include the raw text section bytes
incbin "rebuild/sections/text_raw.bin"

; Section: .rdata (Read-only data)
; Virtual Address: 0x10024000
; File Offset: 0x24000
section .rdata align=4096 vstart=0x10024000

; Include the raw rdata section bytes
incbin "rebuild/sections/rdata_raw.bin"

; Section: .data (Initialized data)
; Virtual Address: 0x10027000
; File Offset: 0x27000
section .data align=4096 vstart=0x10027000

; Include the raw data section bytes
incbin "rebuild/sections/data_raw.bin"

; Section: .reloc (Base relocations)
; Virtual Address: 0x11768000
; File Offset: 0x35000
section .reloc align=4096 vstart=0x11768000

; Include the raw reloc section bytes
incbin "rebuild/sections/reloc_raw.bin"

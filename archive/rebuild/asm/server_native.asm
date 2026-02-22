; server.dll native reconstruction
; Assemble with: nasm -f bin -o server.dll server_native.asm

BITS 32

; Include the PE header we extracted
incbin "rebuild/sections/header.bin"

; .text section (offset 0x1000)
incbin "rebuild/sections/text_raw.bin"

; .rdata section (offset 0x24000)
incbin "rebuild/sections/rdata_raw.bin"

; .data section (offset 0x27000)
incbin "rebuild/sections/data_raw.bin"

; .reloc section (offset 0x35000)
incbin "rebuild/sections/reloc_raw.bin"

; server.dll reconstruction using patched .text from rebuild/asm/Makefile
; Assemble with: nasm -f bin -o rebuild/Server/server_from_asm.dll rebuild/asm/server_from_asm.asm

BITS 32

incbin "../sections/header.bin"
incbin "../sections/text_from_asm.bin"
incbin "../sections/rdata_raw.bin"
incbin "../sections/data_raw.bin"
incbin "../sections/reloc_raw.bin"

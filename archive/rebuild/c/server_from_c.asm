; server.dll reconstruction using MSVC6-compiled C function bytes
; Built by: rebuild/c/Makefile

BITS 32

incbin "../sections/header.bin"
incbin "../sections/text_from_c.bin"
incbin "../sections/rdata_raw.bin"
incbin "../sections/data_raw.bin"
incbin "../sections/reloc_raw.bin"

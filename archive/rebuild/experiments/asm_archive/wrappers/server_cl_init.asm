; server.dll reconstruction using CL-built Init bytes
; Assemble with: nasm -f bin -o rebuild/Server/server_cl_init.dll rebuild/asm/server_cl_init.asm

BITS 32

incbin "rebuild/sections/header.bin"
incbin "rebuild/sections/text_cl_init.bin"
incbin "rebuild/sections/rdata_raw.bin"
incbin "rebuild/sections/data_raw.bin"
incbin "rebuild/sections/reloc_raw.bin"

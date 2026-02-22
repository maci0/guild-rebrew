; Complete PE DLL Construction in NASM
; Creates server.dll from raw sections with proper PE headers
; Output: Flat binary ready to use (no linker needed)

BITS 32

; PE File Layout:
; 0x0000 - 0x00FF: DOS Header + Stub (256 bytes)
; 0x0100 - 0x01FF: PE Header + COFF Header (256 bytes)
; 0x0200 - 0x03FF: Optional Header + Data Directories (512 bytes)
; 0x0400 - 0x0FFF: Section Table + Padding (3KB)
; 0x1000 - 0x23FFF: .text section (143360 bytes)
; 0x24000 - 0x26FFF: .rdata section (12288 bytes)
; 0x27000 - 0x34FFF: .data section (57344 bytes)
; 0x35000 - 0x45FFF: .reloc section (69632 bytes)

; Total: 286720 bytes (0x46000)

; ============================================================
; DOS HEADER (0x00 - 0x7F, 128 bytes)
; ============================================================
dos_header:
    db 'MZ'                     ; e_magic (DOS signature)
    dw 0x0090                   ; e_cblp (bytes on last page)
    dw 0x0003                   ; e_cp (pages in file)
    dw 0x0000                   ; e_crlc (relocations)
    dw 0x0004                   ; e_cparhdr (size of header in paragraphs)
    dw 0x0000                   ; e_minalloc
    dw 0xFFFF                   ; e_maxalloc
    dw 0x0000                   ; e_ss (initial SS)
    dw 0x00B8                   ; e_sp (initial SP)
    dw 0x0000                   ; e_csum (checksum)
    dw 0x0000                   ; e_ip (initial IP)
    dw 0x0000                   ; e_cs (initial CS)
    dw 0x0040                   ; e_lfarlc (relocation table offset)
    dw 0x0000                   ; e_ovno (overlay number)
    times 4 dw 0x0000           ; e_res (reserved)
    dw 0x0000                   ; e_oemid
    dw 0x0000                   ; e_oeminfo
    times 10 dw 0x0000          ; e_res2 (reserved)
    dd pe_header - $$           ; e_lfanew (PE header offset)

; ============================================================
; DOS STUB (0x80 - 0xE7, 104 bytes)
; ============================================================
dos_stub:
    db 0x0E, 0x1F               ; push cs / pop ds
    db 0xBA, 0x0E, 0x00         ; mov dx, 0x000E
    db 0xB4, 0x09               ; mov ah, 0x09
    db 0xCD, 0x21               ; int 0x21 (DOS print string)
    db 0xB8, 0x01, 0x4C         ; mov ax, 0x4C01
    db 0xCD, 0x21               ; int 0x21 (DOS exit)
    db 'This program cannot be run in DOS mode.', 0x0D, 0x0D, 0x0A, '$'
    times (0xE8 - ($ - $$)) db 0x00

; ============================================================
; PE HEADER (0xE8)
; ============================================================
pe_header:
    db 'PE', 0x00, 0x00         ; PE signature

; ============================================================
; COFF HEADER (0xEC - 0xFF, 20 bytes)
; ============================================================
coff_header:
    dw 0x014C                   ; Machine (i386)
    dw 0x0004                   ; NumberOfSections
    dd 0x3FDD84A0               ; TimeDateStamp (2003-12-15 17:53:36)
    dd 0x00000000               ; PointerToSymbolTable
    dd 0x00000000               ; NumberOfSymbols
    dw 0x00E0                   ; SizeOfOptionalHeader (224 bytes)
    dw 0x210E                   ; Characteristics

; ============================================================
; OPTIONAL HEADER (0x0100 - 0x01DF, 224 bytes)
; ============================================================
optional_header:
    dw 0x010B                   ; Magic (PE32)
    db 0x06                     ; MajorLinkerVersion
    db 0x00                     ; MinorLinkerVersion
    dd 0x00023000               ; SizeOfCode
    dd 0x01755000               ; SizeOfInitializedData
    dd 0x00000000               ; SizeOfUninitializedData
    dd 0x0001B9D4               ; AddressOfEntryPoint
    dd 0x00001000               ; BaseOfCode
    dd 0x00024000               ; BaseOfData
    dd 0x10000000               ; ImageBase
    dd 0x00001000               ; SectionAlignment
    dd 0x00001000               ; FileAlignment
    dw 0x0004                   ; MajorOperatingSystemVersion
    dw 0x0000                   ; MinorOperatingSystemVersion
    dw 0x0000                   ; MajorImageVersion
    dw 0x0000                   ; MinorImageVersion
    dw 0x0004                   ; MajorSubsystemVersion
    dw 0x0000                   ; MinorSubsystemVersion
    dd 0x00000000               ; Win32VersionValue
    dd 0x01779000               ; SizeOfImage
    dd 0x00001000               ; SizeOfHeaders
    dd 0x00000000               ; CheckSum (will be calculated)
    dw 0x0002                   ; Subsystem (WINDOWS_GUI)
    dw 0x0000                   ; DllCharacteristics
    dd 0x00100000               ; SizeOfStackReserve
    dd 0x00001000               ; SizeOfStackCommit
    dd 0x00100000               ; SizeOfHeapReserve
    dd 0x00001000               ; SizeOfHeapCommit
    dd 0x00000000               ; LoaderFlags
    dd 0x00000010               ; NumberOfRvaAndSizes (16)

; ============================================================
; DATA DIRECTORIES (16 entries, 128 bytes)
; ============================================================
data_directories:
    dd 0x00026E30, 0x00000051   ; Export Directory
    dd 0x00026608, 0x00000064   ; Import Directory
    dd 0x00000000, 0x00000000   ; Resource Directory
    dd 0x00000000, 0x00000000   ; Exception Directory
    dd 0x00000000, 0x00000000   ; Security Directory
    dd 0x01768000, 0x00001CEC   ; Base Relocation Directory
    dd 0x00000000, 0x00000000   ; Debug Directory
    dd 0x00000000, 0x00000000   ; Architecture
    dd 0x00000000, 0x00000000   ; Global Ptr
    dd 0x00000000, 0x00000000   ; TLS Directory
    dd 0x00000000, 0x00000000   ; Load Config Directory
    dd 0x00000000, 0x00000000   ; Bound Import Directory
    dd 0x00024000, 0x000001A0   ; Import Address Table
    dd 0x00000000, 0x00000000   ; Delay Import Descriptor
    dd 0x00000000, 0x00000000   ; COM Runtime Header
    dd 0x00000000, 0x00000000   ; Reserved

; ============================================================
; SECTION TABLE (4 sections x 40 bytes = 160 bytes)
; ============================================================
section_table:
    ; .text section
    db '.text', 0, 0, 0         ; Name
    dd 0x00022846               ; VirtualSize
    dd 0x10001000               ; VirtualAddress
    dd 0x00023000               ; SizeOfRawData
    dd 0x00001000               ; PointerToRawData
    dd 0x00000000               ; PointerToRelocations
    dd 0x00000000               ; PointerToLinenumbers
    dw 0x0000                   ; NumberOfRelocations
    dw 0x0000                   ; NumberOfLinenumbers
    dd 0x60000020               ; Characteristics (CODE | EXECUTE | READ)

    ; .rdata section
    db '.rdata', 0, 0           ; Name
    dd 0x00002E81               ; VirtualSize
    dd 0x10024000               ; VirtualAddress
    dd 0x00003000               ; SizeOfRawData
    dd 0x00024000               ; PointerToRawData
    dd 0x00000000               ; PointerToRelocations
    dd 0x00000000               ; PointerToLinenumbers
    dw 0x0000                   ; NumberOfRelocations
    dw 0x0000                   ; NumberOfLinenumbers
    dd 0x40000040               ; Characteristics (INITIALIZED_DATA | READ)

    ; .data section
    db '.data', 0, 0, 0         ; Name
    dd 0x0000E000               ; VirtualSize
    dd 0x10027000               ; VirtualAddress
    dd 0x0000E000               ; SizeOfRawData
    dd 0x00027000               ; PointerToRawData
    dd 0x00000000               ; PointerToRelocations
    dd 0x00000000               ; PointerToLinenumbers
    dw 0x0000                   ; NumberOfRelocations
    dw 0x0000                   ; NumberOfLinenumbers
    dd 0xC0000040               ; Characteristics (INITIALIZED_DATA | READ | WRITE)

    ; .reloc section
    db '.reloc', 0, 0           ; Name
    dd 0x00010374               ; VirtualSize
    dd 0x11768000               ; VirtualAddress
    dd 0x00011000               ; SizeOfRawData
    dd 0x00035000               ; PointerToRawData
    dd 0x00000000               ; PointerToRelocations
    dd 0x00000000               ; PointerToLinenumbers
    dw 0x0000                   ; NumberOfRelocations
    dw 0x0000                   ; NumberOfLinenumbers
    dd 0x42000040               ; Characteristics (INITIALIZED_DATA | READ | DISCARDABLE)

; ============================================================
; PADDING TO 0x1000 (4096 bytes)
; ============================================================
times (0x1000 - ($ - $$)) db 0x00

; ============================================================
; SECTION DATA
; ============================================================

; .text section (143360 bytes)
section .text follows=.header vstart=0x10001000 align=1
incbin "rebuild/sections/text_raw.bin"

; Pad to full section size
times (0x23000 - 0x22846) db 0x00

; .rdata section (12288 bytes)
section .rdata follows=.text vstart=0x10024000 align=1
incbin "rebuild/sections/rdata_raw.bin"

; Pad to full section size
times (0x3000 - 0x2E81) db 0x00

; .data section (57344 bytes)
section .data follows=.rdata vstart=0x10027000 align=1
incbin "rebuild/sections/data_raw.bin"

; .reloc section (69632 bytes)
section .reloc follows=.data vstart=0x11768000 align=1
incbin "rebuild/sections/reloc_raw.bin"

; Pad to full section size
times (0x11000 - 0x10374) db 0x00

; Total file size should be 286720 bytes (0x46000)

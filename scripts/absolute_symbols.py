import struct

def absolute_object(symbols, pad_bytes=4):
    """COFF object defining each name as an ABSOLUTE symbol (section -1).

    Absolute symbols bind a name to a numeric value with no section, which is
    exactly what "this data lives at this address" means: no layout, no size, no
    order dependence, and nothing for the emitted-section count to grow.

    The one `.bss` section carries raw bytes even though it is uninitialized --
    `SizeOfRawData` 0 makes LINK refuse the member outright (LNK1106, round 90),
    and a section-less object is rejected as corrupt (LNK1136).
    """
    strtab = bytearray(b'\x04\x00\x00\x00')

    def nm(s):
        b = s.encode('ascii')
        if len(b) <= 8:
            return b.ljust(8, b'\0')
        off = len(strtab)
        strtab.extend(b + b'\0')
        return b'\0\0\0\0' + struct.pack('<I', off)

    sec = bytearray(40)
    sec[0:8] = b'.bss\0\0\0\0'
    struct.pack_into('<I', sec, 8, pad_bytes)          # VirtualSize
    struct.pack_into('<I', sec, 16, pad_bytes)         # SizeOfRawData
    struct.pack_into('<I', sec, 20, 20 + 40)           # PointerToRawData
    struct.pack_into('<I', sec, 36, 0xC0000080)

    syms = bytearray()
    syms += nm('.bss') + struct.pack('<IhHBB', 0, 1, 0, 3, 0)
    for name, value in symbols:
        syms += nm(name) + struct.pack('<IhHBB', value & 0xFFFFFFFF, -1, 0, 2, 0)

    # The string table starts with its own total length, in bytes, INCLUDING
    # that 4-byte field.  Leaving it at 4 while appending long names makes LINK
    # misread every entry: "Internal error during ReadSymbolTable", which is the
    # same failure mode as the COFF stripper bugs of rounds 49-53.
    struct.pack_into('<I', strtab, 0, len(strtab))

    nsym = len(symbols) + 1
    body = b'\x00' * pad_bytes
    sym_ptr = 20 + 40 + len(body)
    # 0x014C = IMAGE_FILE_MACHINE_I386.  Packing it as 0x4C01 stores the bytes
    # reversed and LINK reads the object as a foreign machine: LNK1136.
    hdr = struct.pack('<HHIIIHH', 0x014C, 1, 0, sym_ptr, nsym, 0, 0)
    return bytes(hdr) + bytes(sec) + body + bytes(syms) + bytes(strtab), nsym

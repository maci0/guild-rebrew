#!/usr/bin/env python3
"""Resolve COFF relocations in an MSVC6 .obj file's .text section.

Usage: resolve_relocs.py <obj_file> <output_text_bin> <base_va_hex> [SYM=ADDR ...]

Reads the .obj, extracts .text, applies relocations using the provided
symbol addresses, and writes the resolved .text bytes.

If no SYM=ADDR pairs are given and there are no relocations, it simply
extracts .text (equivalent to objcopy --only-section=.text -O binary).
"""

import struct
import sys


def parse_coff_obj(data):
    """Parse COFF .obj and return .text bytes, relocations, and symbol names."""
    machine, nsections, ts, symtab_off, nsyms, opthdr_sz, chars = struct.unpack_from(
        "<HHIIIHH", data, 0
    )

    text_data = None
    text_relocs = []

    off = 20 + opthdr_sz
    for i in range(nsections):
        name = data[off : off + 8].rstrip(b"\x00").decode()
        vsize, vaddr, rawsize, rawoff, relocoff, lineoff, nrelocs, nlines, sflags = (
            struct.unpack_from("<IIIIIIHHI", data, off + 8)
        )

        if name == ".text":
            text_data = bytearray(data[rawoff : rawoff + rawsize])
            for j in range(nrelocs):
                roff = relocoff + j * 10
                rvaddr, symidx, rtype = struct.unpack_from("<IIH", data, roff)

                sym_off = symtab_off + symidx * 18
                sym_name_raw = data[sym_off : sym_off + 8]
                if sym_name_raw[:4] == b"\x00\x00\x00\x00":
                    str_off = struct.unpack_from("<I", sym_name_raw, 4)[0]
                    strtab_off = symtab_off + nsyms * 18
                    end = data.index(b"\x00", strtab_off + str_off)
                    sym_name = data[strtab_off + str_off : end].decode()
                else:
                    sym_name = sym_name_raw.rstrip(b"\x00").decode()

                text_relocs.append((rvaddr, rtype, sym_name))
            break
        off += 40

    return text_data, text_relocs


def main():
    if len(sys.argv) < 4:
        print(
            f"Usage: {sys.argv[0]} <obj> <output> <base_va_hex> [SYM=ADDR ...]",
            file=sys.stderr,
        )
        sys.exit(1)

    obj_path = sys.argv[1]
    out_path = sys.argv[2]
    base_va = int(sys.argv[3], 16)

    # Parse SYM=ADDR pairs
    sym_addrs = {}
    for arg in sys.argv[4:]:
        sym, addr = arg.split("=", 1)
        sym_addrs[sym] = int(addr, 16)

    with open(obj_path, "rb") as f:
        data = f.read()

    text, relocs = parse_coff_obj(data)
    if text is None:
        print("ERROR: No .text section found", file=sys.stderr)
        sys.exit(1)

    # Apply relocations
    for vaddr, rtype, sym_name in relocs:
        if sym_name not in sym_addrs:
            print(f"ERROR: No address for symbol {sym_name}", file=sys.stderr)
            print(f"  Provide it as: {sym_name}=0xADDRESS", file=sys.stderr)
            sys.exit(1)

        target = sym_addrs[sym_name]
        if rtype == 6:  # IMAGE_REL_I386_DIR32
            struct.pack_into("<I", text, vaddr, target)
        elif rtype == 0x14:  # IMAGE_REL_I386_REL32
            rel = target - (base_va + vaddr + 4)
            struct.pack_into("<i", text, vaddr, rel)
        else:
            print(
                f"ERROR: Unknown relocation type 0x{rtype:x} for {sym_name}",
                file=sys.stderr,
            )
            sys.exit(1)

    with open(out_path, "wb") as f:
        f.write(text)


if __name__ == "__main__":
    main()

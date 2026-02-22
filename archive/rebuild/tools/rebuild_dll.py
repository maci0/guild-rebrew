#!/usr/bin/env python3
"""
DLL Rebuilder - Reconstructs server.dll from raw sections

This script reconstructs the DLL by:
1. Reading raw section data
2. Building PE headers
3. Concatenating sections with proper alignment
4. Setting correct checksum
"""

import struct
import sys
from pathlib import Path

# Section layout from original DLL
SECTIONS = {
    ".text": {
        "virtual_size": 0x00022846,
        "virtual_address": 0x00001000,
        "raw_size": 0x00023000,
        "raw_offset": 0x00001000,
        "characteristics": 0x60000020,  # CODE | EXECUTE | READ
    },
    ".rdata": {
        "virtual_size": 0x00002E81,
        "virtual_address": 0x00024000,
        "raw_size": 0x00003000,
        "raw_offset": 0x00024000,
        "characteristics": 0x40000040,  # INITIALIZED_DATA | READ
    },
    ".data": {
        "virtual_size": 0x0000E000,
        "virtual_address": 0x00027000,
        "raw_size": 0x0000E000,
        "raw_offset": 0x00027000,
        "characteristics": 0xC0000040,  # INITIALIZED_DATA | READ | WRITE
    },
    ".reloc": {
        "virtual_size": 0x00010374,
        "virtual_address": 0x01768000,
        "raw_size": 0x00011000,
        "raw_offset": 0x00035000,
        "characteristics": 0x42000040,  # INITIALIZED_DATA | READ | DISCARDABLE
    },
}

# PE Header constants
PE_SIGNATURE = b"PE\x00\x00"
MACHINE_I386 = 0x14C

# Original values from server.dll
ORIGINAL_TIMESTAMP = 0x3FDD84A0  # 2003-12-15 17:53:36
IMAGE_BASE = 0x10000000
SECTION_ALIGNMENT = 0x1000  # 4096
FILE_ALIGNMENT = 0x1000  # 4096
MAJOR_LINKER_VERSION = 6
MINOR_LINKER_VERSION = 0
ADDRESS_OF_ENTRY_POINT = 0x0001B9D4

# Data directories
DATA_DIRECTORIES = [
    (0x00026E30, 0x00000051),  # Export Directory
    (0x00026608, 0x00000064),  # Import Directory
    (0x00000000, 0x00000000),  # Resource Directory
    (0x00000000, 0x00000000),  # Exception Directory
    (0x00000000, 0x00000000),  # Security Directory
    (0x01768000, 0x00001CEC),  # Base Relocation Directory
    (0x00000000, 0x00000000),  # Debug Directory
    (0x00000000, 0x00000000),  # Description Directory
    (0x00000000, 0x00000000),  # Special Directory
    (0x00000000, 0x00000000),  # Thread Storage Directory
    (0x00000000, 0x00000000),  # Load Configuration Directory
    (0x00000000, 0x00000000),  # Bound Import Directory
    (0x00024000, 0x000001A0),  # Import Address Table
    (0x00000000, 0x00000000),  # Delay Import Directory
    (0x00000000, 0x00000000),  # CLR Runtime Header
    (0x00000000, 0x00000000),  # Reserved
]


def calculate_checksum(data: bytes, checksum_offset: int) -> int:
    """Calculate PE checksum."""
    acc = 0
    length = len(data)

    # Process as 16-bit words
    i = 0
    while i + 1 < length:
        if i == checksum_offset or i == checksum_offset + 1:
            word = 0
        else:
            word = data[i] | (data[i + 1] << 8)

        acc = (acc + word) & 0xFFFFFFFF
        acc = (acc & 0xFFFF) + (acc >> 16)
        i += 2

    # Handle odd byte
    if i < length:
        if i == checksum_offset:
            word = 0
        else:
            word = data[i]
        acc = (acc + word) & 0xFFFFFFFF
        acc = (acc & 0xFFFF) + (acc >> 16)

    # Final folds
    acc = (acc & 0xFFFF) + (acc >> 16)
    acc = (acc & 0xFFFF) + (acc >> 16)

    return (acc + length) & 0xFFFFFFFF


def create_dos_header() -> bytes:
    """Create DOS header and stub."""
    # DOS MZ header (64 bytes)
    dos_header = bytearray(64)
    dos_header[0:2] = b"MZ"  # e_magic
    dos_header[60:64] = struct.pack("<I", 0xE8)  # e_lfanew - offset to PE header

    # DOS stub (232 bytes, total 296 bytes before PE header at 0x128?)
    # Actually e_lfanew points to 0xE8, so we need 0xE8 bytes of DOS stub
    dos_stub = bytearray(0xE8 - 64)

    # Standard DOS stub program
    dos_stub_code = bytes(
        [
            0x0E,
            0x1F,
            0xBA,
            0x0E,
            0x00,
            0xB4,
            0x09,
            0xCD,
            0x21,
            0xB8,
            0x01,
            0x4C,
            0xCD,
            0x21,
        ]
    )
    dos_msg = b"This program cannot be run in DOS mode.\r\r\n$\x00"

    # Position the code and message
    dos_stub[0 : len(dos_stub_code)] = dos_stub_code
    dos_stub[14 : 14 + len(dos_msg)] = dos_msg

    return bytes(dos_header) + bytes(dos_stub)


def create_coff_header(num_sections: int) -> bytes:
    """Create COFF file header (20 bytes)."""
    header = bytearray(20)

    struct.pack_into("<H", header, 0, MACHINE_I386)  # Machine type
    struct.pack_into("<H", header, 2, num_sections)  # Number of sections
    struct.pack_into("<I", header, 4, ORIGINAL_TIMESTAMP)  # TimeDateStamp
    struct.pack_into("<I", header, 8, 0)  # PointerToSymbolTable
    struct.pack_into("<I", header, 12, 0)  # NumberOfSymbols
    struct.pack_into("<H", header, 16, 224)  # SizeOfOptionalHeader (PE32)
    struct.pack_into("<H", header, 18, 0x210E)  # Characteristics

    return bytes(header)


def create_optional_header() -> bytes:
    """Create PE32 optional header (224 bytes)."""
    header = bytearray(224)
    offset = 0

    # Standard fields (28 bytes)
    struct.pack_into("<H", header, offset, 0x10B)
    offset += 2  # Magic (PE32)
    header[offset] = MAJOR_LINKER_VERSION
    offset += 1  # MajorLinkerVersion
    header[offset] = MINOR_LINKER_VERSION
    offset += 1  # MinorLinkerVersion
    struct.pack_into("<I", header, offset, 0x00023000)
    offset += 4  # SizeOfCode
    struct.pack_into("<I", header, offset, 0x01755000)
    offset += 4  # SizeOfInitializedData
    struct.pack_into("<I", header, offset, 0)
    offset += 4  # SizeOfUninitializedData
    struct.pack_into("<I", header, offset, ADDRESS_OF_ENTRY_POINT)
    offset += 4  # Entry point
    struct.pack_into("<I", header, offset, 0x00001000)
    offset += 4  # BaseOfCode
    struct.pack_into("<I", header, offset, 0x00024000)
    offset += 4  # BaseOfData

    # NT additional fields (196 bytes)
    struct.pack_into("<I", header, offset, IMAGE_BASE)
    offset += 4  # ImageBase
    struct.pack_into("<I", header, offset, SECTION_ALIGNMENT)
    offset += 4  # SectionAlignment
    struct.pack_into("<I", header, offset, FILE_ALIGNMENT)
    offset += 4  # FileAlignment
    struct.pack_into("<H", header, offset, 4)
    offset += 2  # MajorOSVersion
    struct.pack_into("<H", header, offset, 0)
    offset += 2  # MinorOSVersion
    struct.pack_into("<H", header, offset, 0)
    offset += 2  # MajorImageVersion
    struct.pack_into("<H", header, offset, 0)
    offset += 2  # MinorImageVersion
    struct.pack_into("<H", header, offset, 4)
    offset += 2  # MajorSubsystemVersion
    struct.pack_into("<H", header, offset, 0)
    offset += 2  # MinorSubsystemVersion
    struct.pack_into("<I", header, offset, 0)
    offset += 4  # Win32VersionValue
    struct.pack_into("<I", header, offset, 0x01779000)
    offset += 4  # SizeOfImage
    struct.pack_into("<I", header, offset, 0x00001000)
    offset += 4  # SizeOfHeaders
    struct.pack_into("<I", header, offset, 0)
    offset += 4  # CheckSum (will be set later)
    struct.pack_into("<H", header, offset, 2)
    offset += 2  # Subsystem (WINDOWS_GUI)
    struct.pack_into("<H", header, offset, 0)
    offset += 2  # DllCharacteristics
    struct.pack_into("<I", header, offset, 0x00100000)
    offset += 4  # SizeOfStackReserve
    struct.pack_into("<I", header, offset, 0x00001000)
    offset += 4  # SizeOfStackCommit
    struct.pack_into("<I", header, offset, 0x00100000)
    offset += 4  # SizeOfHeapReserve
    struct.pack_into("<I", header, offset, 0x00001000)
    offset += 4  # SizeOfHeapCommit
    struct.pack_into("<I", header, offset, 0)
    offset += 4  # LoaderFlags
    struct.pack_into("<I", header, offset, 16)
    offset += 4  # NumberOfRvaAndSizes

    # Data directories (16 * 8 = 128 bytes)
    for rva, size in DATA_DIRECTORIES:
        struct.pack_into("<II", header, offset, rva, size)
        offset += 8

    return bytes(header)


def create_section_header(
    name: bytes, vsize: int, vaddr: int, rsize: int, roffset: int, characteristics: int
) -> bytes:
    """Create a single section header (40 bytes)."""
    header = bytearray(40)

    # Name (8 bytes, null-padded)
    name_bytes = name[:8].ljust(8, b"\x00")
    header[0:8] = name_bytes

    struct.pack_into("<I", header, 8, vsize)  # VirtualSize
    struct.pack_into("<I", header, 12, vaddr)  # VirtualAddress
    struct.pack_into("<I", header, 16, rsize)  # SizeOfRawData
    struct.pack_into("<I", header, 20, roffset)  # PointerToRawData
    struct.pack_into("<I", header, 24, 0)  # PointerToRelocations
    struct.pack_into("<I", header, 28, 0)  # PointerToLinenumbers
    struct.pack_into("<H", header, 32, 0)  # NumberOfRelocations
    struct.pack_into("<H", header, 34, 0)  # NumberOfLinenumbers
    struct.pack_into("<I", header, 36, characteristics)  # Characteristics

    return bytes(header)


def create_section_headers() -> bytes:
    """Create all section headers."""
    headers = b""
    for name, info in SECTIONS.items():
        headers += create_section_header(
            name.encode(),
            info["virtual_size"],
            info["virtual_address"],
            info["raw_size"],
            info["raw_offset"],
            info["characteristics"],
        )
    return headers


def rebuild_dll(output_path: str, sections_dir: str) -> None:
    """Rebuild DLL from raw sections."""
    sections_path = Path(sections_dir)

    # Build headers
    dos_header = create_dos_header()
    pe_sig = PE_SIGNATURE
    coff_header = create_coff_header(len(SECTIONS))
    optional_header = create_optional_header()
    section_headers = create_section_headers()

    # Calculate header size and pad to file alignment
    headers_size = (
        len(dos_header)
        + len(pe_sig)
        + len(coff_header)
        + len(optional_header)
        + len(section_headers)
    )
    padding_needed = FILE_ALIGNMENT - (headers_size % FILE_ALIGNMENT)
    if padding_needed == FILE_ALIGNMENT:
        padding_needed = 0
    header_padding = b"\x00" * padding_needed

    # Read section data
    section_data = {}
    for name in SECTIONS.keys():
        section_file = sections_path / f"{name[1:]}.bin"  # Remove leading dot
        if section_file.exists():
            with open(section_file, "rb") as f:
                section_data[name] = f.read()
        else:
            print(f"Warning: {section_file} not found, using empty section")
            section_data[name] = b""

    # Build the PE file
    pe_data = bytearray()

    # Headers (at offset 0)
    pe_data.extend(dos_header)
    pe_data.extend(pe_sig)
    pe_data.extend(coff_header)
    pe_data.extend(optional_header)
    pe_data.extend(section_headers)
    pe_data.extend(header_padding)

    # Verify headers end at correct offset
    assert len(pe_data) == 0x1000, f"Headers size mismatch: {len(pe_data)} != 4096"

    # Section data (at their respective offsets)
    # For simplicity, we'll just concatenate sections with their raw sizes
    for name, info in SECTIONS.items():
        data = section_data[name]
        # Pad to raw size if needed
        if len(data) < info["raw_size"]:
            data = data + b"\x00" * (info["raw_size"] - len(data))
        elif len(data) > info["raw_size"]:
            data = data[: info["raw_size"]]
        pe_data.extend(data)

    # Calculate and set checksum
    # Checksum offset: after DOS header (0xE8) + PE sig (4) + COFF header (20) + 0x40 into optional header
    checksum_offset = 0xE8 + 4 + 20 + 0x40
    checksum = calculate_checksum(bytes(pe_data), checksum_offset)
    struct.pack_into("<I", pe_data, checksum_offset, checksum)

    # Write output
    with open(output_path, "wb") as f:
        f.write(pe_data)

    print(f"Rebuilt DLL: {output_path}")
    print(f"Size: {len(pe_data)} bytes")
    print(f"Checksum: 0x{checksum:08X}")

    return checksum


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="Rebuild server.dll from sections")
    parser.add_argument(
        "-o", "--output", default="rebuild/Server/server.dll", help="Output DLL path"
    )
    parser.add_argument(
        "-s",
        "--sections",
        default="rebuild/sections",
        help="Directory containing section .bin files",
    )
    args = parser.parse_args()

    rebuild_dll(args.output, args.sections)

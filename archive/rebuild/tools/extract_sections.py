#!/usr/bin/env python3
"""
PE Section Extractor - Extracts raw sections from PE files

This tool extracts each section from a PE/DLL file as raw binary data,
preserving exact byte content for reconstruction.
"""

import struct
import sys
from pathlib import Path


def extract_sections(pe_path: str, output_dir: str):
    """Extract all sections from a PE file."""
    pe_path = Path(pe_path)
    output_dir = Path(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)

    with open(pe_path, "rb") as f:
        data = f.read()

    # Parse DOS header
    dos_magic = data[0:2]
    if dos_magic != b"MZ":
        raise ValueError(f"Invalid DOS magic: {dos_magic}")

    pe_offset = struct.unpack_from("<I", data, 0x3C)[0]
    print(f"PE header offset: 0x{pe_offset:04X}")

    # Verify PE signature
    pe_sig = data[pe_offset : pe_offset + 4]
    if pe_sig != b"PE\x00\x00":
        raise ValueError(f"Invalid PE signature: {pe_sig}")

    # Parse COFF header
    coff_offset = pe_offset + 4
    num_sections = struct.unpack_from("<H", data, coff_offset + 2)[0]
    timestamp = struct.unpack_from("<I", data, coff_offset + 4)[0]
    optional_header_size = struct.unpack_from("<H", data, coff_offset + 16)[0]
    characteristics = struct.unpack_from("<H", data, coff_offset + 18)[0]

    print(f"Number of sections: {num_sections}")
    print(f"Timestamp: 0x{timestamp:08X}")
    print(f"Optional header size: {optional_header_size}")
    print(f"Characteristics: 0x{characteristics:04X}")

    # Parse optional header for ImageBase
    optional_offset = coff_offset + 20
    magic = struct.unpack_from("<H", data, optional_offset)[0]
    print(
        f"Optional header magic: 0x{magic:04X} ({'PE32' if magic == 0x10B else 'PE32+'})"
    )

    if magic == 0x10B:  # PE32
        image_base = struct.unpack_from("<I", data, optional_offset + 28)[0]
        section_alignment = struct.unpack_from("<I", data, optional_offset + 32)[0]
        file_alignment = struct.unpack_from("<I", data, optional_offset + 36)[0]
        print(f"ImageBase: 0x{image_base:08X}")
        print(f"SectionAlignment: 0x{section_alignment:08X}")
        print(f"FileAlignment: 0x{file_alignment:08X}")

    # Parse section headers
    section_table_offset = optional_offset + optional_header_size

    print(
        f"\n{'Section':<12} {'V.Size':<10} {'V.Addr':<10} {'R.Size':<10} {'R.Offset':<10}"
    )
    print("-" * 60)

    sections = []
    for i in range(num_sections):
        sec_offset = section_table_offset + (i * 40)
        name = (
            data[sec_offset : sec_offset + 8]
            .rstrip(b"\x00")
            .decode("ascii", errors="ignore")
        )
        virtual_size = struct.unpack_from("<I", data, sec_offset + 8)[0]
        virtual_addr = struct.unpack_from("<I", data, sec_offset + 12)[0]
        raw_size = struct.unpack_from("<I", data, sec_offset + 16)[0]
        raw_offset = struct.unpack_from("<I", data, sec_offset + 20)[0]
        characteristics = struct.unpack_from("<I", data, sec_offset + 36)[0]

        print(
            f"{name:<12} {virtual_size:<10} {virtual_addr:<10} {raw_size:<10} {raw_offset:<10}"
        )

        sections.append(
            {
                "name": name,
                "virtual_size": virtual_size,
                "virtual_addr": virtual_addr,
                "raw_size": raw_size,
                "raw_offset": raw_offset,
                "characteristics": characteristics,
            }
        )

    # Extract sections
    print(f"\nExtracting sections to: {output_dir}")

    for sec in sections:
        name = sec["name"]
        raw_offset = sec["raw_offset"]
        raw_size = sec["raw_size"]

        if raw_size > 0 and raw_offset < len(data):
            section_data = data[raw_offset : raw_offset + raw_size]
            output_file = output_dir / f"{name.lstrip('.')}.bin"
            with open(output_file, "wb") as f:
                f.write(section_data)
            print(f"  {name}: {len(section_data)} bytes -> {output_file}")
        else:
            print(f"  {name}: Empty or invalid section")

    # Extract headers (from start to first section)
    first_section_offset = min(s["raw_offset"] for s in sections if s["raw_size"] > 0)
    header_data = data[:first_section_offset]
    header_file = output_dir / "header.bin"
    with open(header_file, "wb") as f:
        f.write(header_data)
    print(f"  Headers: {len(header_data)} bytes -> {header_file}")

    return sections


if __name__ == "__main__":
    import argparse

    parser = argparse.ArgumentParser(description="Extract sections from PE file")
    parser.add_argument("pe_file", help="Input PE file")
    parser.add_argument(
        "-o", "--output", default="sections", help="Output directory for sections"
    )
    args = parser.parse_args()

    extract_sections(args.pe_file, args.output)

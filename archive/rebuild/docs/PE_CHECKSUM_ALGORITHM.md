# PE Checksum Algorithm

## Overview

The PE (Portable Executable) checksum is a 32-bit value stored in the Optional Header. It's used by Windows for integrity checking, particularly for system files and drivers.

**Location in PE:** `OptionalHeader.CheckSum` (offset 0x40 in PE32 optional header)

## Algorithm Description

The checksum algorithm is a simple additive checksum with end-around carry:

1. **Initialize:** accumulator = 0
2. **Iterate:** Process file as 16-bit words (little-endian)
3. **Skip Field:** Treat the CheckSum field itself as zero during calculation
4. **Accumulate:** Add each word to accumulator
5. **Carry Fold:** After each addition, fold high 16 bits into low 16 bits
6. **Odd Byte:** If file size is odd, add final byte
7. **Final Fold:** Fold accumulator to 16 bits
8. **Add Length:** Add total file size in bytes
9. **Store:** Result is the 32-bit checksum

## Python Implementation

```python
import struct

def calculate_pe_checksum(data: bytes, checksum_offset: int = None) -> int:
    """
    Calculate PE checksum for a binary.
    
    Args:
        data: The binary data
        checksum_offset: Optional offset to CheckSum field (auto-detected if None)
    
    Returns:
        32-bit checksum value
    """
    if checksum_offset is None:
        # Auto-detect: CheckSum is at offset 0x40 from start of optional header
        # Optional header starts at: 0x18 (coff header) + 0x14 (optional header size field) = 0x3C
        # But actually PE offset + 0x18 + 0x40 = PE offset + 0x58
        # PE offset is at 0x3C in DOS header
        pe_offset = struct.unpack_from('<I', data, 0x3C)[0]
        optional_header_offset = pe_offset + 0x18
        # CheckSum is at offset 0x40 in optional header
        checksum_offset = optional_header_offset + 0x40
    
    acc = 0
    length = len(data)
    
    # Process as 16-bit words
    i = 0
    while i + 1 < length:
        # CheckSum field is treated as 0
        if i == checksum_offset:
            word = 0
        elif i == checksum_offset + 1:
            # Second byte of CheckSum field
            word = 0
        else:
            word = data[i] | (data[i + 1] << 8)
        
        acc = (acc + word) & 0xFFFFFFFF
        # End-around carry fold
        acc = (acc & 0xFFFF) + (acc >> 16)
        i += 2
    
    # Handle odd byte at end
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
    
    # Add file length
    return (acc + length) & 0xFFFFFFFF


def verify_pe_checksum(filepath: str) -> tuple[bool, int, int]:
    """
    Verify PE checksum of a file.
    
    Args:
        filepath: Path to PE file
    
    Returns:
        Tuple of (is_valid, stored_checksum, calculated_checksum)
    """
    with open(filepath, 'rb') as f:
        data = f.read()
    
    # Find CheckSum field
    pe_offset = struct.unpack_from('<I', data, 0x3C)[0]
    optional_header_offset = pe_offset + 0x18
    checksum_offset = optional_header_offset + 0x40
    
    # Read stored checksum
    stored_checksum = struct.unpack_from('<I', data, checksum_offset)[0]
    
    # Calculate checksum
    calculated_checksum = calculate_pe_checksum(data, checksum_offset)
    
    return (stored_checksum == calculated_checksum, stored_checksum, calculated_checksum)


def set_pe_checksum(input_path: str, output_path: str) -> int:
    """
    Calculate and set PE checksum.
    
    Args:
        input_path: Input PE file
        output_path: Output PE file with corrected checksum
    
    Returns:
        The calculated checksum value
    """
    with open(input_path, 'rb') as f:
        data = bytearray(f.read())
    
    # Find CheckSum field
    pe_offset = struct.unpack_from('<I', data, 0x3C)[0]
    optional_header_offset = pe_offset + 0x18
    checksum_offset = optional_header_offset + 0x40
    
    # Calculate new checksum
    new_checksum = calculate_pe_checksum(data, checksum_offset)
    
    # Write checksum to data
    struct.pack_into('<I', data, checksum_offset, new_checksum)
    
    # Write output file
    with open(output_path, 'wb') as f:
        f.write(data)
    
    return new_checksum


# Example usage
if __name__ == '__main__':
    import sys
    
    if len(sys.argv) < 2:
        print("Usage: python pe_checksum.py <pe_file>")
        sys.exit(1)
    
    filepath = sys.argv[1]
    is_valid, stored, calculated = verify_pe_checksum(filepath)
    
    print(f"File: {filepath}")
    print(f"Stored checksum:    0x{stored:08X} ({stored})")
    print(f"Calculated checksum: 0x{calculated:08X} ({calculated})")
    print(f"Checksum valid: {is_valid}")
```

## Using pefile Library

```python
import pefile

# Load PE file
pe = pefile.PE('server.dll')

# Get stored checksum
stored = pe.OPTIONAL_HEADER.CheckSum
print(f"Stored: 0x{stored:08X}")

# Verify (available in newer pefile versions)
try:
    is_valid = pe.verify_checksum()
    print(f"Valid: {is_valid}")
except AttributeError:
    # Manual verification
    import struct
    with open('server.dll', 'rb') as f:
        data = f.read()
    # ... use algorithm above

# Generate and set new checksum
new_checksum = pe.generate_checksum()
pe.OPTIONAL_HEADER.CheckSum = new_checksum
pe.write('server_fixed.dll')
```

## Checksum Fields Location

### PE32 (32-bit)
- PE Header offset: `DOS_HEADER.e_lfanew` (at file offset 0x3C)
- Optional Header offset: `PE_HEADER + 0x18`
- CheckSum offset: `Optional Header + 0x40`
- **File offset:** `e_lfanew + 0x18 + 0x40 = e_lfanew + 0x58`

### PE32+ (64-bit)
- PE Header offset: Same as PE32
- Optional Header offset: `PE_HEADER + 0x18`
- CheckSum offset: `Optional Header + 0x40` (same relative position)
- **File offset:** `e_lfanew + 0x18 + 0x40 = e_lfanew + 0x58`

## Important Notes

1. **Not Cryptographic:** PE checksum is NOT a hash - it's trivial to create collisions
2. **Windows Use:** Windows uses it for integrity checking during boot/load
3. **Signed Binaries:** Authenticode signatures don't use this checksum
4. **Zero Checksum:** Many DLLs have checksum of 0 (not calculated)
5. **Linker Setting:** MSVC `/RELEASE` sets checksum, without it stays 0

## Checksum Variations

The stored checksum may differ from calculated if:
- File has been modified after linking
- Certificate table appended (signed binaries)
- Overlay data added
- Manual hex editing

## Checksum Matching Strategy

For bit-identical reproduction:

1. **Extract original checksum:** Note the stored value
2. **Reproduce all bytes exactly:** Every byte affects checksum
3. **If mismatch:** Identify differing bytes, adjust padding
4. **Final resort:** Modify non-critical bytes (e.g., padding) to compensate

## Reference Implementation Sources

- Microsoft `CheckSumMappedFile` API (ImageHlp.dll)
- Wine implementation: `dlls/imagehlp/checksum.c`
- pefile library: `pefile.py` generate_checksum()
- LLVM: `llvm/tools/llvm-objcopy/CopyConfig.cpp`


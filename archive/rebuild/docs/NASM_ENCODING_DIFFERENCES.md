# NASM Encoding Differences - Documentation

## The Problem

When disassembling functions and re-assembling with NASM, some instructions have **multiple valid encodings** that produce the same behavior but different bytes.

### MOV Register-to-Register Encoding

x86 has two ways to encode `mov reg, reg`:

1. **0x89 form** (NASM default): `MOV r/m32, r32`
   - Example: `mov esi, eax` → `89 c6`
   - Direction: source is reg, destination is r/m

2. **0x8b form** (MSVC often uses): `MOV r32, r/m32`
   - Example: `mov esi, eax` → `8b f0`
   - Direction: source is r/m, destination is reg

Both execute identically but produce different machine code.

## Affected Instructions

| Instruction | NASM Produces | MSVC/Original | Difference |
|-------------|---------------|---------------|------------|
| `mov esi, eax` | `89 c6` | `8b f0` | Different encoding |
| `mov eax, esi` | `89 f0` | `8b c6` | Different encoding |
| `mov edx, ecx` | `89 ca` | `8b d1` | Different encoding |
| `mov ecx, edx` | `89 d1` | `8b ca` | Different encoding |

## Impact

- **Functionality**: Identical (same result)
- **Checksum**: Will differ (different bytes)
- **Size**: Same (same number of bytes)

## Solutions

### Option 1: Accept Functional Identity (Recommended for RE)

Use readable NASM assembly. The code works identically even if checksum differs.

**Pros:**
- Readable, modifiable assembly
- Standard NASM syntax
- Easy to understand and edit

**Cons:**
- Checksum won't match
- Can't prove bit-identical reconstruction

### Option 2: Use db for Specific Instructions

For instructions where encoding matters, use `db`:

```nasm
; Instead of:
mov     esi, eax

; Use:
db      0x8b, 0xf0      ; mov esi, eax (match original encoding)
```

**Pros:**
- Bit-identical output
- Can mix with regular instructions

**Cons:**
- Defeats purpose of readable assembly
- Harder to modify

### Option 3: Post-Processing Script

Create a tool to patch the assembled binary:

```bash
# After NASM assembly, patch specific offsets
# Replace 0x89c6 with 0x8bf0 at known locations
```

**Pros:**
- Keep readable source
- Get bit-identical output

**Cons:**
- Requires additional tooling
- More complex workflow

### Option 4: Use Different Assembler

Some assemblers allow forcing specific encodings:
- GAS (GNU assembler) has `.s` suffix
- YASM may have options
- Custom assembler

**Pros:**
- Could get both readable and bit-identical

**Cons:**
- Toolchain change
- Learning curve

## Recommendation

For this project, I recommend **Option 1** (readable assembly) for these reasons:

1. **Primary goal is reverse engineering** - you need to understand and modify code
2. **Functionality is identical** - the code works exactly the same
3. **Checksum verification can be done differently** - compare function outputs, not bytes
4. **Documentation captures intent** - the `.md` files explain what each function does

If you need bit-identical output for a specific reason (e.g., proving reconstruction capability), use **Option 2** (db directives) for those specific functions.

## Testing

To verify the assembly works correctly:

1. Assemble the readable NASM
2. Inject into a test process
3. Verify behavior matches original
4. Don't rely on checksum - rely on functional tests

## Example

Here's how to write a function with readable NASM:

```nasm
; fcn_10001860 - Output byte write helper
BITS 32
org 0x10001860

fcn_10001860:
    mov     eax, [esp+0x4]      ; deflate_state pointer
    mov     ecx, [esp+0x8]      ; value to write  
    push    esi
    push    edi
    mov     esi, [eax+0x8]       ; pending_buf
    mov     edi, [eax+0x14]      ; pending count
    mov     edx, ecx             ; NASM: 89ca, Orig: 8bd1 (same function)
    shr     edx, 0x8
    mov     [esi+edi], dl        ; write high byte
    mov     edx, [eax+0x14]
    mov     esi, [eax+0x8]
    inc     edx
    mov     [eax+0x14], edx
    pop     edi
    mov     [esi+edx], cl        ; write low byte
    mov     ecx, [eax+0x14]
    inc     ecx
    pop     esi
    mov     [eax+0x14], ecx
    ret
```

This assembles to working code with only minor byte differences in MOV encodings.

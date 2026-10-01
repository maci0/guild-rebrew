#!/usr/bin/env python3
"""Check native readonly game symbols against their reference bytes."""
import math
import re
import struct
import sys
from pathlib import Path

binary = Path(sys.argv[1] if len(sys.argv) > 1 else 'build/server.dll')
built = binary.read_bytes()
link_map = binary.with_suffix('.map').read_text()
reference = Path('original/Server/server.dll').read_bytes()
source = '\n'.join(path.read_text() for path in (
    Path('src/crt_region/game_float_constants.c'),
    Path('src/Develop/DieGildeAddOn/game/type_adjustments.c'),
))
pe = struct.unpack_from('<I', built, 60)[0]
image_base = struct.unpack_from('<I', built, pe + 24 + 28)[0]
section_start = pe + 24 + struct.unpack_from('<H', built, pe + 20)[0]
sections = []
for i in range(struct.unpack_from('<H', built, pe + 6)[0]):
    pos = section_start + 40 * i
    size, rva, raw_size, offset = struct.unpack_from('<4I', built, pos + 8)
    flags = struct.unpack_from('<I', built, pos + 36)[0]
    sections.append((rva, size, raw_size, offset, flags))

rows = re.findall(
    r'// GLOBAL: SERVER (0x[0-9a-fA-F]+)\s+(?:extern\s+)?const (float|double|int|struct TypeAdjustment) (\w+)((?:\[\d+\])*)\s*(?:=|;)',
    source,
)
literal_symbols = {
    '_g_stat_min_d': '__real@8@00000000000000000000',
    'g_const_one_d': '__real@8@3fff8000000000000000',
    'g_const_30': '__real@4@4003f000000000000000',
    'g_graveyard_const_a': '__real@4@4008fa00000000000000',
    'g_graveyard_const_b': '__real@4@40028000000000000000',
    'g_graveyard_const_c': '__real@4@40018000000000000000',
}
assert rows, 'No annotated readonly game symbols found'
for original_va, kind, name, dimensions in rows:
    length = {'double': 8, 'float': 4, 'int': 4, 'struct TypeAdjustment': 40}[kind] * math.prod(
        int(n) for n in re.findall(r'\d+', dimensions)
    )
    native_name = '_' + name
    if name in literal_symbols:
        assert not re.search(r'\s\d+:\w+\s+_' + name + r'\s', link_map), 'Duplicate literal owner: ' + name
        native_name = literal_symbols[name]
    symbol = re.search(r'\s\d+:\w+\s+' + re.escape(native_name) + r'\s+([0-9a-fA-F]+)', link_map)
    assert symbol, 'Missing native symbol: ' + name
    address = int(symbol[1], 16) - image_base
    if name in {
        'g_type_adjustments', 'g_type_adjustments_count',
        'g_type_adjustments_secondary', 'g_type_adjustments_secondary_count',
        'g_type_multipliers',
    }:
        assert address == int(original_va, 16) - image_base, 'Misplaced type table: ' + name
    section = next(s for s in sections if s[0] <= address < s[0] + s[1])
    rva, size, raw_size, offset, flags = section
    assert not flags & 0x80000000, 'Writable constant: ' + name
    assert address + length <= rva + min(size, raw_size), 'Truncated constant: ' + name
    start = offset + address - rva
    original_start = int(original_va, 16) - 0x10000000
    assert built[start:start + length] == reference[original_start:original_start + length], name
print(f'{len(rows)} native readonly game symbols match their reference bytes')

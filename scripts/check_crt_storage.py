"""Check recovered CRT storage after generating split-link inputs."""
from pathlib import Path

import lief
from emit_crt_data import member_object

if __name__ == "__main__":
    lock = lief.COFF.parse("build/split_poc/split/1001cfa1_.text.obj")
    assert next(s for s in lock.sections if s.name == ".bss").size == 96
    stdio = lief.COFF.parse("build/split_poc/split/1001baa4_.text.obj")
    buffer = next(s for s in stdio.symbols if s.name == "__bufin")
    assert buffer.section_idx == 0 and buffer.value == 4096
    locale = lief.COFF.parse("build/split_poc/crt_data/crt_13_lconv.obj")
    symbol = next(s for s in locale.symbols if s.name == "___lconv_static_null")
    section = list(locale.sections)[symbol.section_idx - 1]
    assert section.name == ".bss" and section.size == 1 and symbol.value == 0
    for member, filename in (
        ("intrncvt.obj", "crt_09_intrncvt.obj"),
        ("lconv.obj", "crt_13_lconv.obj"),
        ("constpow.obj", "crt_14_constpow.obj"),
    ):
        stock = lief.COFF.parse(list(member_object(Path(".scratch/libcmt/LIBCMT.sp6.LIB"), member)))
        emitted = lief.COFF.parse("build/split_poc/crt_data/" + filename)
        original = next(s for s in stock.sections if s.name == ".data")
        placed = next(s for s in emitted.sections if s.name == ".data")
        assert placed.characteristics == original.characteristics
    print("stock CRT storage: four locks, 4 KB stdio buffer, independent null byte")

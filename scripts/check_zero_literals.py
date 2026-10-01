"""Check zero-literal recovery against the project's generated CRT objects."""
from pathlib import Path

from split_blob import zero_literal_offsets

if __name__ == "__main__":
    objects = list(Path("build/split_poc/split").glob("*.obj"))
    assert objects, "generate the CRT split objects first"
    assert zero_literal_offsets(objects) == {
        "??_C@_01A@?$AA?$AA@": 0x20F0,
        "??_C@_13A@?$AA?$AA?$AA?$AA@": 0x20F4,
    }
    print("zero literals recovered from matching CRT code")

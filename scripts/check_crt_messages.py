#!/usr/bin/env python3
"""Check that stock CRT message strings have one owner in a native link."""

import argparse
from pathlib import Path

from split_coff import Coff, ar_members, name_resolver


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("binary", type=Path)
    parser.add_argument("--lib", type=Path, default=Path(".scratch/libcmt/LIBCMT.sp6.LIB"))
    args = parser.parse_args()
    members = list(ar_members(args.lib.read_bytes()))
    resolve = name_resolver(members)
    coff = next(Coff(body) for name, body in members
                if resolve(name).endswith("\\crt0msg.obj"))
    binary = args.binary.read_bytes()
    checked = 0
    for index, section in enumerate(coff.sections):
        if section["name"].rstrip(b"\0") != b".rdata":
            continue
        message = coff.section_body(index)
        if len(message) < 10:
            continue
        count = binary.count(message)
        if count != 1:
            raise SystemExit(f"Expected one copy, found {count}: {message!r}")
        checked += 1
    if checked != 20:
        raise SystemExit(f"Unexpected CRT message inventory: {checked}")
    print(f"{checked} CRT messages: one copy each")


if __name__ == "__main__":
    main()

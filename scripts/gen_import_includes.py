"""Write layout/server.dll/import-includes.rsp: one /INCLUDE per import, ordered so LINK emits the reference's IAT.

LINK allocates an IAT slot when it first loads the import-library member that defines `__imp__X`, then sorts
each DLL's slots through the tool runtime's qsort (docs/msvc6-link-layout.md section 73). The sort applies the
same positional permutation to any input of the same length (measured: every WS2_32 trial, whatever the member
order, permuted 16 inputs identically; KERNEL32's 81 slots stay in place except positions 0 and 56). So the file
lists the members in the order that the permutation maps onto the reference's slot order. The reference's import
table is the source of truth; decorated names (`@N`) come from the pragmas in crt_imports.c.

Left out on purpose: `__imp__RtlUnwind@16`. Its member also defines the `_RtlUnwind@16` thunk, which the CRT
references; loading it early places that thunk ahead of the WS2_32 thunks (reference VA 0x10023840) and shifts
every library function after it. It loads last (KERNEL32 slot 80, reference slot 73), so KERNEL32 slots 73 to 80
stay one position late.
"""

import re
from pathlib import Path

import pefile

REFERENCE = "original/Server/server.dll"
SOURCE = "src/crt_region/crt_imports.c"
SKIP_NAMES = {"RtlUnwind"}
# Output slot j takes input position PERMUTATION[j]; measured for 16 WS2_32 members.
WS2_PERMUTATION = (9, 14, 15, 8, 10, 7, 11, 6, 5, 4, 3, 2, 1, 0, 12, 13)
# Output slot 0 and 56 swap in the 81-slot KERNEL32 block.
KERNEL32_SWAP = (0, 56)


def project_root() -> Path:
    here = Path(__file__).resolve()
    for parent in here.parents:
        if (parent / "rebrew-project.toml").exists():
            return parent
    raise SystemExit("rebrew-project.toml not found above " + str(here))


def preimage(reference_order: list[str]) -> list[str]:
    """Input order whose WS2_32 permutation yields reference_order."""
    inputs = [""] * len(WS2_PERMUTATION)
    for slot, position in enumerate(WS2_PERMUTATION):
        inputs[position] = reference_order[slot]
    return inputs


def main() -> None:
    root = project_root()
    decorated = {
        m[1].split("@")[0]: m[1]
        for m in re.finditer(r'/include:__imp__([^"]+)"', (root / SOURCE).read_text())
    }
    pe = pefile.PE(str(root / REFERENCE))
    by_dll = {
        entry.dll.decode(): [i.name.decode() for i in entry.imports if i.name and i.name.decode() not in SKIP_NAMES]
        for entry in pe.DIRECTORY_ENTRY_IMPORT
    }
    kernel32 = list(by_dll["KERNEL32.dll"])
    a, b = KERNEL32_SWAP
    kernel32[a], kernel32[b] = kernel32[b], kernel32[a]
    ordered = kernel32 + by_dll["USER32.dll"] + preimage(by_dll["WS2_32.dll"]) + by_dll["WINMM.dll"]
    out = root / "layout/server.dll/import-includes.rsp"
    out.write_text("".join(f"/INCLUDE:__imp__{decorated[n]}\n" for n in ordered))
    print(f"{len(ordered)} imports -> {out.relative_to(root)}")


if __name__ == "__main__":
    main()

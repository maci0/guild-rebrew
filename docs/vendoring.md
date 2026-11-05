# Vendored libraries

zlib and minizip build from pinned pristine files plus ordered patches. Edit the
patch and manifest, not a generated source tree or a stock archive.

## Inputs and outputs

| Path | Role |
| --- | --- |
| `references/zlib-1.1.3/` | Untouched upstream release |
| `references/vendor/<name>/vendor.toml` | Input/output/checksum/patch manifest |
| `references/vendor/<name>/NNNN-*.patch` | One evidenced change per patch |
| `references/zlib/` | Generated zlib build sources |
| `references/minizip/` | Generated unzip.c/unzip.h |

Generated outputs are tracked because managed function bindings compile them.
CMake checks both manifests during configuration and refuses drift.

```sh
uv run rebrew library vendor references/vendor/zlib/vendor.toml references/vendor/minizip/vendor.toml
```

Check is the default. After reviewing patch/manifest edits, add `--apply` to
regenerate, then reconfigure. The checker stages exact manifest inputs, applies
patches with fuzz disabled and compares outputs. A failed check writes nothing.

## Reconstruction limits

| Patch | Purpose and limit |
| --- | --- |
| zlib 0001 | Native malloc-based allocator difference; original authorship unresolved |
| zlib 0002 | Shared version string; link-composition stand-in |
| zlib 0003 | selectany readonly tables; link-layout stand-in |
| zlib 0004 | File-scope selectany inflateSync mark; link-layout stand-in |
| minizip 0001 | Native 0.15a version literal; upstream fork not located |
| minizip 0002 | selectany copyright; link-layout stand-in |
| minizip 0003 | Native file-position extensions; authorship unresolved |

These patches reproduce evidence but do not establish the original distribution.
Removing a stand-in requires original ownership/composition evidence and complete
image checks. Equal imports or section sizes are insufficient.

Library attribution, selected raw-link provider and game recovery are separate
claims. Use the target's own runtime/callees and complete native body/operand
proof, not a family-wide address shift or a matching wrapper alone.

## Miles 6.1c

Miles is a pinned import library, not a generated vendor tree. Its canonical
[dependency note](../references/mss-6.1c/README.md) owns the download, hash and
runtime witnesses. Client configuration and pre-link checks enforce that pin.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/vendoring.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/vendoring.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| Vendored libraries | - |
| <a id="layout"></a>Layout | - |
| <a id="mechanism"></a>Mechanism | - |
| Miles 6.1c | - |
| <a id="zlib-113"></a>zlib 1.1.3 | `0x45ee00`, `0x45ee20`, `0x45f060`, `0x45f0a0`, `0x45f110`, `0x45f240`, `0x45f2c0`, `0x45f380`, `0x45f630`, `0x45f6d0`, `0x45f890`, `0x45f9e0`, `0x45fa90`, `0x462c40`, `0x462c60`, `0x462ea0`, `0x462fd0`, `0x463050`, `0x463100`, `0x463330`, `0x463490`, `0x4635e0`, `0x463670`, `0x64e66a`, `0x1040498`, `0x1002706c` |
| <a id="minizip-unzipc"></a>minizip (unzip.c) | `0x4649d2`, `0x465750`, `0x465790` |
| <a id="version-and-patch-audit-2026-10-11"></a>Version and patch audit (2026-10-11) | - |
| <a id="workaround-removal-probes-2026-10-11"></a>Workaround removal probes (2026-10-11) | - |

</details>

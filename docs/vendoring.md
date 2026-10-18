# Vendored libraries

The build compiles zlib 1.1.3 and minizip from pinned pristine sources plus
ordered patches. CMake refuses configuration when the generated sources differ.
Do not edit a generated tree or a stock archive by hand. Miles is a pinned
import library, not one of these trees: [Miles 6.1c](#miles-61c).

## Layout

| Path | Contents |
|---|---|
| `references/zlib-1.1.3/` | The zlib 1.1.3 release tarball, unpacked and untouched |
| `references/vendor/<name>/vendor.toml` | Upstream URL, version, tarball sha256, pristine directory, output tree, its file list, patch order |
| `references/vendor/<name>/NNNN-*.patch` | One change each: a header with its kind, reason and evidence, then a `-p1` unified diff |
| `references/vendor/zlib/pristine.sha256` | sha256 of every file in `references/zlib-1.1.3/` (`sha256sum -c` format, root-relative) |
| `references/zlib/` | Generated: the 25 zlib files the build compiles or includes |
| `references/minizip/` | Generated: `unzip.c` and `unzip.h`, from `references/zlib-1.1.3/contrib/minizip/` |

Generated trees are tracked because managed function bindings compile them
directly. Manifests pin inputs, checksums, outputs and patch order.

## Mechanism

```sh
uv run --frozen rebrew library vendor references/vendor/zlib/vendor.toml references/vendor/minizip/vendor.toml
# After editing a patch and its manifest:
uv run --frozen rebrew library vendor references/vendor/zlib/vendor.toml references/vendor/minizip/vendor.toml --apply
```

Check is the default and does not take `--apply`. It verifies every pristine
checksum, copies each manifest's listed files into a temporary stage, applies
GNU `patch -p1 --fuzz=0`, and compares that stage with the output tree. A
mismatch leaves the output unwritten. Paths cannot escape the root, use
symlinks, or overlap inputs and outputs.

On 2026-10-18 the default check with `--json` exited 0: zlib 25 files and 4
patches, minizip 2 files and 3 patches, both `mode` `check`. The pristine,
vendor, and generated trees were byte-for-byte unchanged.

CMake always runs that check at configure, without `--apply`. It uses
`.venv/bin/rebrew` when that file exists, otherwise `find_program(rebrew)`.
The command is both manifests plus `--root` set to the project source
directory. A nonzero status is `FATAL_ERROR`. Configure depends on
`references/vendor/*`, `references/zlib-1.1.3/*`, `references/zlib/*`, and
`references/minizip/*`. Upstream `tests/test_vendor.py` covers check, drift,
and `--apply`. Regenerate, then reconfigure, after a patch change.

## Miles 6.1c

Miles is not an input to `rebrew library vendor`. Pins, the hash check,
rejected candidates, and receipts are in
[references/mss-6.1c/README.md](../references/mss-6.1c/README.md). That note
also records the limit: the pin does not by itself identify the archive the
original linker selected.

`REBREW_BUILD_GOLD` and `REBREW_BUILD_GOLDTL` default off. When either is on,
configure includes `cmake/verify-mss32.cmake`, which fails if
`references/mss-6.1c/mss32.lib` is missing or its hash differs. For each
client target that exists, the link library list must contain that archive or
configure fails. The same script runs again as `PRE_LINK`.

## zlib 1.1.3

[Official tarball](https://zlib.net/fossils/zlib-1.1.3.tar.gz), SHA-256:
`cae5847bc0e1cf113d3f70d037400da3e47c2e2b7b1c96b0b08447a5fbb906f4`.
Canonical `references/zlib/gzio.c` replaces copied client bodies:

| Function | TL VA | Gold VA | Complete body |
|---|---|---|---|
| `gzwrite` | `0x45f630` | `0x463330` | 150 bytes |
| `gzprintf` | `0x45f6d0` | not established here | 95 bytes |
| `gzseek` | `0x45f890` | `0x463490` | 332 bytes |
| `gzrewind` | `0x45f9e0` | `0x4635e0` | 112 bytes |
| `gzread` | `0x45f380` | `0x463100` | 555 bytes TL, 556 Gold |
| `getLong` | `0x45fa90` | `0x463670` | 65 bytes |
| `destroy` | `0x45f2c0` | `0x463050` | 177 bytes TL, 176 Gold |
| `gzopen` | `0x45ee00` | `0x462c40` | 21 bytes |
| `gz_open` | `0x45ee20` | `0x462c60` | 566 bytes TL, 565 Gold |
| `check_header` | `0x45f110` | `0x462ea0` | 294 bytes |
| `get_byte` | `0x45f240` | `0x462fd0` | 114 bytes TL, 113 Gold |
| `gzdopen` | `0x45f060` | not established here | 59 bytes |
| `gzsetparams` | `0x45f0a0` | not established here | 97 bytes |

Complete native code, typed operands, reachable control flow, literal checks
and wrong-binding controls support these identities. Library attribution is
separate from a selected raw-link provider and from game progress. Gold uses
`/ML` / LIBC; server and TL use `/MT` / LIBCMT. The malloc wrapper alone is
inconclusive. `free`, `fread`, `fwrite`, `fseek`, `rewind`, and direct errno
access distinguish Gold. Check callees with that client's objects.

Additional canonical groups and receipts under `.scratch/goal21/`:

| Group | Recorded result / receipt directory |
| --- | --- |
| Write/printf/seek | Complete bodies; seek caller preserved at 449 bytes, still mismatched against Gold's 464. `zlib-source-ownership/` |
| Rewind | Four independent callee bindings and rejecting controls/client; 44 surrounding bodies preserved. `gzrewind-source-ownership/` |
| Read/destroy/runtime | TL excludes five/15 trailing NOPs; Gold read 556 bytes. `gold-crt-provider/` |
| `getLong` | 65 bytes, four `get_byte` calls/client. `gz-getlong-source-ownership/` |
| Gold `destroy` | 176 bytes/nine operands; eight callees supported by LIBC. `gz-destroy-source-ownership/` |
| Open family | Canonical public prototypes; Gold header excludes ten NOPs. `<fd:%d>` is an eight-byte compiler literal. `gz-open-family/` |
| TL `gzsetparams` | 97 bytes with supported `fwrite`/`deflateParams`. `gzsetparams-source-ownership/` |
| Close/flush | Both `do_flush`, `putLong`, `gzclose`, `gztell`; TL `gzflush`/`gzeof`/`gzerror`. Eleven profiles, 940 bytes/26 operands; Gold close excludes three NOPs. `gz-close-family/` |
| TL character wrappers | `gzgetc`/`gzgets`/`gzputc`/`gzputs`: 39/79/47/34 bytes; completes all 24 functions emitted by this TU. `gz-character-helpers/` |
| TL `minigzip.c` | Six bodies 37/192/173/177/233/417 bytes and 143 literal bytes. Source owns COMMON4 `prog` at `0x1040498`; no linked-data verdict. `minigzip-source-ownership/` |

Canonical `gzerror` expands `ALLOC` to native `malloc`; its empty and colon-space
literals match with `HAVE_STRERROR` unset. Gold flush/eof/error counterparts are
not asserted by this scope. Upstream PR28 fixed exported K&R pointer-return
inventory for `gzgets`/`gzerror`; older preservation receipts used direct COFF
extraction. TL `minigzip`'s CFG must model native `_exit` at `0x64e66a` as
noreturn; three unreachable compiler pops still belong to the byte extent.

Authorship of the non-stand-in patches is unresolved. The
[version audit](#version-and-patch-audit-2026-10-11) records the comparisons.
Current patches:

| Patch | Kind | Change |
|---|---|---|
| 0001-zcalloc-malloc | native allocator difference; source provenance unresolved | `zcalloc` returns `malloc(items * size)`; the reference calls LIBCMT `malloc` with an `imul` |
| 0002-shared-version-string | link-composition stand-in | `deflate.c` defines `char g_zlib_version[]` before `my_version`; `inflate.c` compares against it |
| 0003-selectany-readonly-tables | link-layout stand-in | 17 readonly tables and both copyright strings become `__declspec(selectany)` |
| 0004-inflatesync-mark-selectany | link-layout stand-in | `inflateSync`'s block-scope `mark[4]` becomes a file-scope selectany object |

The checked 1.1.2, 1.1.3, and 1.1.4 sources, and Vollant's `zlib113dll.zip`,
call `calloc`. zlib 1.2.0 uses `malloc` but is a different base. Stock version
literals already pool under `/O2` (`/Gf`); patch 0002 compensates for order,
not code generation. Stock `compress.c` places the literal at `0x1002706c`
but changes compiler-object and CRT composition. `/ORDER` places COMDATs
before ordinary readonly data. MSVC6 has no general data-COMDAT flag (`/Gy`
is functions), which is why 0003 and 0004 exist.

## minizip (unzip.c)

Base: the tarball's June 15, 1998 unzip 0.15. Its backward central-directory
scan matches TL `0x4649d2`; the March `unzlb015.zip` and zlib 1.1.2 scan forward.
The March archive SHA-256 is
`54b97df32ed9128b581a6d22d34e4e466096b6cf9333e7906dca5a0220f46eaf`.
Canonical source is `references/minizip/unzip.c`.

| Patch | Kind | Change |
|---|---|---|
| 0001-unz-copyright-0.15a | version string, no located upstream | `" unzip 0.15a Copyright 1998 Gilles Vollant "`, as in the server and both clients |
| 0002-unz-copyright-selectany | link-layout stand-in | `unz_copyright` becomes selectany so `/ORDER` places it (stock moves 5370 bytes) |
| 0003-game-file-position | native extensions; authorship unresolved | `unzGetFilePos`/`unzGoToFilePos` appended (TL 0x465750, 0x465790) |

The appended helpers access private `unz_s` and its static reader. Native TL
places them in the same unit. Checked Vollant 0.15 through 0.18 releases lack
them. Minizip 1.00 later uses the same names with a different API. Those names
are borrowed. Authorship of the game's extensions remains unresolved.

## Version and patch audit (2026-10-11)

Four patches are reconstruction stand-ins: zlib 0002, 0003, and 0004, and
minizip 0002. The other three preserve a native allocator change, a version
literal, and file-position extensions. They do not prove an author or an
original distribution.

Checked fossils 1.1.1 through 1.2.3, Vollant DLL and build archives, and an
exact-literal search did not locate this `unzip 0.15a` fork. Vollant's
[1.1.3a build](https://www.winimage.com/zLibDll/buildzlib113adll.zip), SHA-256
`cfa8689ed5b97c916f5ec2c1107750ea17a0bdc909e430e59dec17454172526f`, labels
zip 0.15a but directs copying ordinary unzip 0.15 unchanged. A miss does not
establish that no other fork exists. Receipt:
`.scratch/goal21/vendor-version-audit/`.

## Workaround removal probes (2026-10-11)

Isolated counterfactual links. Production inputs and the image were preserved:

| Candidate | Differing bytes | Finding |
|---|---:|---|
| Stock version literals instead of zlib 0002 | 17 | Function addresses, imports and section sizes stay unchanged; literal/pointer order differs |
| Stock literals plus stock `compress.c` | 16663 | Literal placement is correct, but one extra compiler object and CRT placement differ |
| Same, with the extension table owned by VFS rather than its standalone source | 16579 | Original compiler-object counts are restored, but 97 symbols still move; `.text` grows 16 bytes and `.reloc` grows 12 bytes |
| Ordinary read-only storage, removing zlib 0003/0004, minizip 0002 and `/ORDER` | 6123 | Original section sizes and compiler-object counts remain, but game pools, library tables and CRT read-only data move |

The ordinary-readonly probe differs at 5,339 `.rdata`, 275 `.text`, 62 `.data`
and 445 `.reloc` bytes. All four successful links retain import identities,
IAT addresses and hints. Correct sizes or object counts alone do not establish
native composition. Recover original readonly ownership and discarded inputs
before removing the patches. Recipes, complete comparisons, maps and hashes:
`.scratch/goal21/vendor-workaround-removal/`. Full audits remain in the
[historical archive](goal-history.md#full-notebooks).

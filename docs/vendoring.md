# Vendored libraries

server.dll links zlib 1.1.3 and minizip's unzip.c from source. Each is vendored as the
unmodified upstream release plus a list of local patches, and the build refuses to
configure unless the compiled tree equals pristine + patches.

## Layout

| Path | Contents |
|---|---|
| `references/zlib-1.1.3/` | The zlib 1.1.3 release tarball, unpacked and untouched |
| `references/vendor/<name>/vendor.toml` | Upstream URL, version, tarball sha256, pristine directory, output tree, its file list, patch order |
| `references/vendor/<name>/NNNN-*.patch` | One change each: a header with its kind, reason and evidence, then a `-p1` unified diff |
| `references/vendor/zlib/pristine.sha256` | sha256 of every file in `references/zlib-1.1.3/` (`sha256sum -c` format, root-relative) |
| `references/zlib/` | Generated: the 25 zlib files the build compiles or includes |
| `references/minizip/` | Generated: `unzip.c` and `unzip.h`, from `references/zlib-1.1.3/contrib/minizip/` |

The generated trees are committed because the function rows in
`rebrew-functions.toml` name them (`references/zlib/deflate.c`) and `rebrew verify`
compiles those files directly. Never edit them by hand.

## Mechanism

`scripts/vendor.py check` (run by CMake at configure, `CMakeLists.txt` "Vendored
libraries") does, per manifest:

1. Every file under the pristine directory is listed in the checksum file with a
   matching sha256, and every output file comes from a pinned pristine file.
2. Copies the listed files into `build/vendor-stage/<name>` and applies the patches in
   order with GNU `patch -p1 --fuzz=0`; a hunk that does not apply exactly fails.
3. Requires the output tree to hold exactly the listed files, byte-identical to the
   staged result.

Any failure prints the file and stops configure with `Vendored sources differ from
pristine upstream + patches`. Every pristine, patch, manifest and output file is a
configure dependency, so an edit re-runs the check on the next build.
`tests/test_vendor.py` covers each failure.

To change vendored code: edit or add a patch, list it in `vendor.toml`, then run
`.venv/bin/python scripts/vendor.py sync --stage .scratch/vendor-stage` to regenerate
the output tree, and rebuild.

## zlib 1.1.3

Upstream: <https://zlib.net/fossils/zlib-1.1.3.tar.gz>, sha256
`cae5847bc0e1cf113d3f70d037400da3e47c2e2b7b1c96b0b08447a5fbb906f4` (also published by
Gilles Vollant as `zlib113.zip`, same sources with CRLF line ends). The previous
in-place copy differed from the tarball in eight files (`crc32.c`, `deflate.c`,
`infblock.c`, `inflate.c`, `inftrees.c`, `trees.c`, `trees.h`, `zutil.c`); whitespace,
an inline data marker and two redundant `extern` lines changed no byte and were dropped.

| Patch | Kind | Change |
|---|---|---|
| 0001-zcalloc-malloc | native allocator difference; source provenance unresolved | `zcalloc` returns `malloc(items * size)`; the reference calls LIBCMT `malloc` with an `imul` |
| 0002-shared-version-string | link-composition stand-in | `deflate.c` defines `char g_zlib_version[]` before `my_version`; `inflate.c` compares against it |
| 0003-selectany-readonly-tables | link-layout stand-in | 17 readonly tables and both copyright strings become `__declspec(selectany)` |
| 0004-inflatesync-mark-selectany | link-layout stand-in | `inflateSync`'s block-scope `mark[4]` becomes a file-scope selectany object |

What was ruled out, by rebuilding with the stock text:

- **The checked 1.1.x releases do not have 0001.** zlib 1.1.2, 1.1.3 and 1.1.4 and Gilles Vollant's prebuilt
  `zlib113dll.zip` all call `calloc(items, size)`. zlib 1.2.0+ computes
  `malloc(items * size)`, but with 1.2 sources. Stock `zutil.c` moves 26164 bytes.
- **0002 is a link-order effect.** `/O2` implies `/Gf`, so the stock literal is already one
  pooled `.data` COMDAT and stock code is byte-identical; only the literal and the
  pointer swap (17 bytes). Linking stock `compress.c` (which the TL client links) places
  the literal exactly at `0x1002706c`, because `compress.obj` is the first object in link
  order whose code references `ZLIB_VERSION`. It is left out because it adds a game C
  object to the Rich header and moves the CRT member load order (16663 bytes differ).
- **0003 and 0004 follow from `/ORDER`.** The build places readonly game pools with
  `/ORDER` (msvc6-link-layout 30), which puts ordered COMDATs ahead of all ordinary
  `.rdata`, so the zlib tables before them must be COMDATs too. MSVC 6 has no flag that
  makes data COMDAT (`/Gy` covers functions, `/Gf`/`/GF` string literals). Stock tables
  move readonly data (10735 bytes; 6324 with no `/ORDER` at all); a stock `mark` moves
  4709 bytes.

## minizip (unzip.c)

Upstream: `contrib/minizip/unzip.c` and `unzip.h` of the same zlib 1.1.3 tarball,
pinned by the zlib checksum list. That file is Gilles Vollant's unzip 0.15 in its
1998-06-15 revision: `unzlocal_SearchCentralDir` scans backward
(`for (i=(int)uReadSize-3; (i--)>0;)`), as the TL client does at 0x4649d2. The
standalone `unzlb015.zip` (winimage.com, 1998-03-19, sha256
`54b97df32ed9128b581a6d22d34e4e466096b6cf9333e7906dca5a0220f46eaf`) and zlib 1.1.2's
copy scan forward, so they match worse. It was `src/Develop/Units/vfs/unzip.c`; it is
library code, so its three server rows are `LIBRARY` rows bound to
`references/minizip/unzip.c` (`src/library_minizip.h`, `rebrew library bind-source`).

| Patch | Kind | Change |
|---|---|---|
| 0001-unz-copyright-0.15a | version string, no located upstream | `" unzip 0.15a Copyright 1998 Gilles Vollant "`, as in the server and both clients |
| 0002-unz-copyright-selectany | link-layout stand-in | `unz_copyright` becomes selectany so `/ORDER` places it (stock moves 5370 bytes) |
| 0003-game-file-position | native extensions; authorship unresolved | `unzGetFilePos`/`unzGoToFilePos` appended (TL 0x465750, 0x465790) |

Searched for an upstream 0.15a: winimage.com zLibDll (`unzlb015.zip`, `zlib112dll.zip`,
`zlib113dll.zip`, `zlib113adll.zip`, `buildzlib113adll.zip`, `unzip16.zip`,
`unzip17.zip`, `zlib114dll.zip`), zlib fossils 1.1.1 to 1.2.3, and GitHub code
search. In those checked archives, Gilles Vollant's "0.15a" labels only `zip.c`: `zlib113dll.zip` (1998-07)
and the 2000 1.1.3a build carry `" zip 0.15a"` beside `" unzip 0.15"`, and the 1.1.3a
build notes say to take `unzip.c` from `contrib/minizip` unchanged.

The two appended functions are native extensions kept in this file because they read `unz_s`
and call the file's static `unzlocal_GetCurrentFileInfoInternal`; the TL client has
them inside the same unit. None of the checked Vollant releases from 0.15 to 0.18 (1998-2002) has them.
minizip 1.00 (zlib 1.2.1, 2003) added functions of the same names, credited to Ryan
Haksi, with a different interface (`unz_file_pos` struct, `UNZ_END_OF_LIST_OF_FILE`);
the names here are borrowed from it. Their absence from the checked published
releases does not establish that the game developers authored them; an unpublished
or third-party fork remains possible.

The client targets' two `unzip.c` rows (GOLD, GOLDTL) moved with the file and stay
`FUNCTION` rows, like the clients' zlib functions.


## Version and patch audit (2026-10-11)

Four of the seven patches compensate for the current reconstruction's link
composition or readonly placement: zlib 0002/0003/0004 and minizip 0002. They
remain required by the measured current link, but are not evidence that the
original developers changed those library sources. Recovering the original
object composition and data placement is the route to removing them.

The other three preserve observed native differences: zlib's malloc-based
allocator, minizip's `unzip 0.15a` literal, and the client's two file-position
extensions. The bytes establish those differences; they do not establish who
made them or which source distribution contained them.

Fresh downloads from the authors confirm that the pristine 1.1.3 source matches
[the official release](https://zlib.net/fossils/zlib-1.1.3.tar.gz). It contains
backward-scanning unzip 0.15, without the two file-position helpers. The checked
1.1.2/1.1.3/1.1.4 sources use calloc; 1.2.0 uses malloc on 32-bit systems but
retains unzip 0.15 without these helpers. 1.2.1 adds helpers with a different
interface, and labels unzip 1.00.

Gilles Vollant's [1.1.3a build archive](https://www.winimage.com/zLibDll/buildzlib113adll.zip)
(SHA256 `cfa8689ed5b97c916f5ec2c1107750ea17a0bdc909e430e59dec17454172526f`)
contains zip 0.15a and directs the builder to copy unzip.c unchanged from the
standard distribution. Both checked 1.1.3 and 1.1.3a binary archives contain
`zip 0.15a` alongside `unzip 0.15`, so the DLL distribution's suffix does not
identify the game's `unzip 0.15a` variant. An exact-literal GitHub code search
returned no results; that is a search limitation, not proof that no fork exists.

The strongest identified base remains zlib 1.1.3 with the June 1998 minizip
revision. The exact modified distribution remains unidentified. No vendor
source, patch body, generated file, archive, compiler flag or link rule was
changed by this audit. Download hashes, source comparisons, binary literals and
author build notes are recorded in `.scratch/goal21/vendor-version-audit/`.

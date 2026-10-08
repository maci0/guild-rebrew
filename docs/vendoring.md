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
| 0001-zcalloc-malloc | game build change | `zcalloc` returns `malloc(items * size)`; the reference calls LIBCMT `malloc` with an `imul` |
| 0002-shared-version-string | link-composition stand-in | `deflate.c` defines `char g_zlib_version[]` before `my_version`; `inflate.c` compares against it |
| 0003-selectany-readonly-tables | link-layout stand-in | 17 readonly tables and both copyright strings become `__declspec(selectany)` |
| 0004-inflatesync-mark-selectany | link-layout stand-in | `inflateSync`'s block-scope `mark[4]` becomes a file-scope selectany object |

What was ruled out, by rebuilding with the stock text:

- **No upstream has 0001.** zlib 1.1.2, 1.1.3 and 1.1.4 and Gilles Vollant's prebuilt
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

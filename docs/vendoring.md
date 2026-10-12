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

`rebrew library vendor references/vendor/zlib/vendor.toml references/vendor/minizip/vendor.toml` (run by CMake at configure, `CMakeLists.txt` "Vendored
libraries") does, per manifest:

1. Every file under the pristine directory is listed in the checksum file with a
   matching sha256, and every output file comes from a pinned pristine file.
2. Copies the listed files into a temporary staging directory and applies the patches in
   order with GNU `patch -p1 --fuzz=0`; a hunk that does not apply exactly fails.
3. Requires the output tree to hold exactly the listed files, byte-identical to the
   staged result.

Any failure prints the file and stops configure with `Vendored sources differ from
pristine upstream + patches`. Every pristine, patch, manifest and output file is a
configure dependency, so an edit re-runs the check on the next build.
Upstream Rebrew’s `tests/test_vendor.py` covers reproduction and failure cases.
The command validates and stages every manifest before sync changes any output;
paths must stay inside the root, with no symlinks or overlap between outputs and inputs.

To change vendored code: edit or add a patch, list it in `vendor.toml`, then run
`rebrew library vendor references/vendor/zlib/vendor.toml references/vendor/minizip/vendor.toml --sync` to regenerate
the output tree, and rebuild.

## zlib 1.1.3

The client inventory also binds these verified native bodies to the canonical
`references/zlib/gzio.c`, rather than maintaining separate game-source copies:

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

Unique stock-source matches and complete native-byte/operand controls support
these bindings. Verified duplicate source files are retired; the seek caller
keeps its compiled bytes and typed operands after binding the canonical name.
Gold's caller remains a size mismatch (449 compiled bytes versus 464 native).
The `gzwrite` definition is identical to pristine 1.1.3. These bodies do not
establish the complete original fork or remove the unresolved patches below.
Receipts: `.scratch/goal21/zlib-source-ownership/`.

`gzrewind` additionally has four independently supported native call targets,
four rejecting binding controls per client, complete reachable control flow,
and 44 preserved surrounding vendor bodies. TL's `rewind` and `fseek` uniquely
match LIBCMT; Gold's uniquely match single-thread LIBC. Further full-body
`free`, `fread` and `fwrite` evidence, stock `crt0dat.obj`'s errno definition,
and the complete native gzip bodies establish Gold's `/ML` and `LIBC` settings.
The public malloc wrapper matches both runtimes and does not distinguish them.
Server and TL retain `/MT` and `LIBCMT`. Gold's raw link remains unbuilt.
Receipts: `.scratch/goal21/gzrewind-source-ownership/`.

TL's existing canonical `gzread` (`0x45f380`) and `destroy` (`0x45f2c0`)
also reproduce their complete 555- and 177-byte native bodies. Their previous
560- and 192-byte measurements included five and fifteen unreachable NOPs.
Rebrew's guarded size repair records RELOC for both without changing source
or flags. Full native bytes, typed operands, rejecting binding controls and
reachable control flow support these extents. Receipts:
`.scratch/goal21/gold-crt-provider/TL-*-extent-proof.json`.

Gold `gzread` now uses unchanged canonical `gzio.c` under `/ML`, replacing
the copy that manually declared the CRT errno global. Its complete 556 native
bytes, 11 typed operands, seven rejecting binding controls and 205 reachable
instructions match; the fresh CLI result is RELOC556. Native openers in both
clients pass the complete `1.1.3` version literal. Other copied gzip functions
have verified canonical candidates but still await ownership/caller cleanup.
Neither these facts nor the version literal establish the entire original fork
or remove the unresolved patches below. Receipts:
`.scratch/goal21/gold-crt-provider/`.

Both clients' little-endian `getLong` now bind canonical `gzio.c`. Complete
65-byte bodies, four typed calls to independently supported `get_byte`,
rejecting binding controls and all 25 reachable instructions match. Native
callee resolution must use each client's compiled object: the server's `/MT`
object correctly fails Gold's `/ML` callee check. The unowned shared copy is
retired without changing callers, flags, vendor source or data. Before/after
objects preserve all 44 surrounding vendor bodies. Fresh measurements are
RELOC65 in both; this is library attribution, not game reversing. Receipts:
`.scratch/goal21/gz-getlong-source-ownership/`.

Gold's private `destroy` now uses canonical `gzio.c`, retiring the copied
`vfs_CloseStream` stand-in and its manual errno declaration. Complete native
176-byte/9-operand/71-instruction checks and five rejecting bindings match;
indexing the Gold objects plus stock LIBC supports all eight direct calls.
The fresh result is RELOC176, with all 22 surrounding vendor bodies unchanged.
No caller, vendor source, flags, data or storage changes are introduced.
Receipts: `.scratch/goal21/gz-destroy-source-ownership/`.

The opener/helper dependency group now binds canonical source together. Six
copied files are retired, including the mislabeled CRT `mlock.c` gzip wrapper.
Three callers use the public interfaces from `zlib.h`; their complete 177-,
233- and 417-byte bodies and typed operands remain unchanged. All 44 vendor
bodies in both clients are preserved. Gold's old header extent included ten
unreachable NOPs; guarded repair records RELOC294. Two previously unbound Gold
private functions now have verified library identities. All 22 bound gzip
functions freshly pass RELOC. The descriptor format `<fd:%d>` including NUL
is an eight-byte compiler literal in native `.data`, not a named allocation;
its managed row records the canonical source and actual compiler symbol without
assigning a data-byte verdict. Receipts: `.scratch/goal21/gz-open-family/`.

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


## Workaround removal probes (2026-10-11)

Fresh isolated MSVC 6 builds tested removal against the current 286720-byte
raw reference. Production sources, objects, link inputs and image were held
unchanged; these are counterfactual links, not accepted release builds.

| Candidate | Differing bytes | Finding |
|---|---:|---|
| Stock version literals instead of zlib 0002 | 17 | Function addresses, imports and section sizes stay unchanged; literal/pointer order differs |
| Stock literals plus stock `compress.c` | 16663 | Literal placement is correct, but one extra compiler object and CRT placement differ |
| Same, with the extension table owned by VFS rather than its standalone source | 16579 | Original compiler-object counts are restored, but 97 symbols still move; `.text` grows 16 bytes and `.reloc` grows 12 bytes |
| Ordinary read-only storage, removing zlib 0003/0004, minizip 0002 and `/ORDER` | 6123 | Original section sizes and compiler-object counts remain, but game pools, library tables and CRT read-only data move |

The last probe also removes selectany from the three game read-only scaffold
units, the `mark` anchor and the 15 external anchors for tables restored to
private stock storage. Of its differences, 5339 are in `.rdata`, 275 in
`.text`, 62 in `.data` and 445 in `.reloc`. All four successful links retain
the reference's import identities, IAT addresses and hints. This rules out
extra imports as their cause; matching section sizes or compiler-object counts
alone does not establish a correct link.

Moving the extension table to its using module is a plausible ownership repair,
but it does not by itself establish the original object composition. Adding
stock `compress.c` still changes CRT placement even though its compressor bodies
are discarded. These candidates therefore cannot replace the current patches
while preserving raw identity. No new dummy code, archive edits or postlink
byte fixes were introduced. The remaining removal work is to recover the
original read-only owners and object composition, alongside discarded server
source. Recipes, maps, logs, complete byte comparisons and preserved-input
hashes are in `.scratch/goal21/vendor-workaround-removal/`.

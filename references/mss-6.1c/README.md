# TL Miles dependency: 6.1c; original import archive unresolved

**Gold TL linking is blocked until the original SDK import archive is verified.**
The configured path is `references/mss-6.1c/mss32.lib`, currently absent.
Putting an arbitrary file there does not remove the CMake block. Do not use
OpenMiles, another SDK release, or a generated import library as the original.

The reference EXE imports 51 named APIs from `MSS32.DLL`. All 51 PE import hints
match the sorted export-name indexes of the original Miles 6.1c runtime found at
`../openmiles/Guild/mss_backup/MSS32.DLL`. Its version resource identifies RAD Game
Tools and 6.1c. The active DLL in `../openmiles/Guild/` is an OpenMiles replacement;
the backup is the relevant runtime evidence.

| Input | SHA-256 |
| --- | --- |
| `original/Europa1400Gold_TL.exe` | `6fe7a24c93192f6511bc8595eb82fd166db44f6cbeaf7c2f036838f3b6b4af45` |
| Guild backup `MSS32.DLL` (348,160 bytes) | `2a515199cc7a2e1ccd8d756efdaab07cedd5c3052309ef1c7499c2560e2097bd` |
| `../openmiles/references/MSS-6.1/6.1c-mss32.dll` | `ddb8c4180836d63c81d1657f169c461f42be10795641b0f39cae7acb799ced11` |

The second 6.1c DLL has the same export interface but different code bytes and PE
timestamp. A version label or import-interface agreement does not establish
identical runtime bytes or recover the exact SDK archive originally linked.

| Rejected candidate | Required names supplied | Matching import hints |
| --- | ---: | ---: |
| OpenMiles references `MSS-6.0/mss32.lib` | 51/51 | 0/51 |
| OpenMiles references `MSS-6.1/Libraries/Win32/DebugRelease/mss32.lib` | 36/51 | 0/51 |
| Historical re3 SDK archive, SHA-256 `7df3aff6b82329b5f6ca6b3321f64a596fc7a0edcb626aacd68a6fb792ab20a2` | 51/51 | 0/51 |

The directory labeled `MSS-6.1` contains a **7.2g** runtime under
`Binaries/Win32/DebugRelease`; its directory name is not version evidence.
The historical re3 archive was downloaded unchanged from
[this pinned revision](https://git.shihaam.dev/archivemirrors/re3/src/commit/fce2e02444a056cc420be6b32844de039fbfafac/milessdk/lib/mss32.lib).
[RAD's release history](https://www.radgametools.com/msshist.htm) documents 6.1c.

Before unblocking, establish SDK provenance and check the archive's emitted
imports against every reference name and hint. Pin the accepted archive's SHA-256
in the build and check it both during configuration and immediately before the
link, so replacement after configuration is rejected. An interface match alone
must not be reported as proof of the original archive's complete byte identity.

Audit inputs/results are in `.scratch/text-accounting-20261016/`:
`miles-runtime-versions.json`, `all-miles-library-fingerprints.json`,
`re3-miles-fingerprint.json`, and `miles-version-requirement.json`.

`LUA50.lib` remains removed from the TL provisional link list: there are no TL
Lua imports, unresolved Lua names, or target-bound Lua annotations. Existing
`library_lua50.h` annotations belong to GOLD. This is not a general proof that
the image contains no Lua-derived bytes.

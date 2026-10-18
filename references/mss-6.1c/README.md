# Miles 6.1c build dependency

Both clients select the pristine SDK archive at
`references/mss-6.1c/mss32.lib`. Its SHA-256 is
`34882ed6295c6d7937a505ccab6f32b50a47433856431565ef49860d6bd45f9d`
(253,742 bytes). The ignored binary is a reproducible build input; it does not
uniquely establish the archive originally selected by the game's linker.

The source is [ProjectDreamland/area51, pinned commit
dfaa140222e8918c47b844af15dd10150b05a9a9](https://github.com/ProjectDreamland/area51/blob/dfaa140222e8918c47b844af15dd10150b05a9a9/xCore/3rdParty/Miles6/lib/win/Mss32.lib).
[Download the unchanged archive](https://raw.githubusercontent.com/ProjectDreamland/area51/dfaa140222e8918c47b844af15dd10150b05a9a9/xCore/3rdParty/Miles6/lib/win/Mss32.lib) from that revision's
`xCore/3rdParty/Miles6/lib/win/Mss32.lib`, then check the SHA-256 above.
The Git blob ID is `79105dce07956c70a0e6bc4156236f3e91a36bea`.
The same snapshot's header identifies 6.1c, dated 15-Oct-01; its runtime is
byte-identical to the Guild backup listed below.

All 351 archive import names and hints agree with that runtime's exports.
Actual isolated LINK probes emit exactly the reference's 51 TL and 31 Gold
MSS32 imports, including every hint. These probes are separate from complete
game builds; neither client has a verified complete raw image yet.

`cmake/verify-mss32.cmake` checks the fixed hash during configuration and
immediately before each client link. The archive and verifier are link
dependencies, and configuration checks that this path is selected in the
target's library list. Missing or changed bytes fail. Do not substitute
OpenMiles, another release, or a generated import library.

The runtime witness is `../openmiles/Guild/mss_backup/MSS32.DLL`, identified
as RAD Game Tools 6.1c. The active DLL in `../openmiles/Guild/` is an OpenMiles
replacement; use the backup for original runtime evidence.

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

Current provenance, complete archive comparison, raw LINK probes and checksum
rejecting controls are in `.scratch/goal83-miles-candidates/`:
`source-pin.json`, `downloads.json`, `comparison.json`, `link-probe.json`, and
`checksum-controls-production.json`. No archive bytes were patched.

Audit inputs/results are in `.scratch/text-accounting-20261016/`:
`miles-runtime-versions.json`, `all-miles-library-fingerprints.json`,
`re3-miles-fingerprint.json`, and `miles-version-requirement.json`.

`LUA50.lib` remains removed from the TL provisional link list: there are no TL
Lua imports, unresolved Lua names, or target-bound Lua annotations. Existing
`library_lua50.h` annotations belong to GOLD. This is not a general proof that
the image contains no Lua-derived bytes.

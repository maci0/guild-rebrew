# Original build facts

These are native/compiler observations. [Current work](TODO.md) owns status;
[build instructions](build.md) own setup and reference hashes.

## Original project

The server embeds `D:\Develop\DieGildeAddOnServer\server.c` and paths under
`D:\Develop\DieGildeAddOn`. GoldTL embeds
`D:\develop\DieGildeAddOnVc\Release\Europa1400Exp_TL.pdb` and paths under
`D:\develop\units`. Preserve the case of an attested path.
An embedded path identifies a source unit; it does not place every recovered
function in that unit.
Use [source layout](source-layout.md) and [naming](naming_conventions.md) for those decisions.

## Configured build

| Context | Server | GoldTL | Gold |
| --- | --- | --- | --- |
| Project compiler profile | Plain VC6 SP5 | SP5 Processor Pack | SP5 Processor Pack |
| Configured runtime | /MT, LIBCMT | /MT, LIBCMT | /ML, LIBC |

The same `CL.EXE` version can use different code generators. Game-only x87 compare
patterns and complete same-source controls distinguish plain VC6 from Processor
Pack; Rich headers also describe library objects. Some bodies are identical
under both generators, so one matching function cannot select the profile.

Default game optimization is `/O2 /Gd`. Effective per-target/TU inputs live in
`rebrew-project.toml` and managed metadata. Independently built libraries can have
other evidenced contexts. Historical flag probes are not production overrides.

## Cross-target recovery

Match reference bytes, native calls, fields and literals before sharing a body.
Equal names or a score of 100 do not establish equal layouts or providers.
DirectInput is one concrete boundary. The observed interface prefixes in
`src/client_input.h` distinguish Gold's version 7 from GoldTL's version 8.

Client data can be absent from the server despite adjacent shared code. Library
bands can contain different code generators. Neither adjacency nor a constant VA
shift establishes a counterpart.

Use `.venv/bin/rebrew source import-related --help` for reviewed shared-source imports.
Source sharing still requires destination compilation and complete operand checks.

## Archived techniques

Original notebook: `docs/general-knowledge.md` in the [documentation archive](goal-history.md#full-notebooks).

- Original build and native facts
- Where to read
- Original build (`0x005e0000`, `0x0064ffff`, `0x10000000`, `0x10009320`, `0x10009350`)
- Toolchain observations (verified with commands; round 938)
- Deliverable mechanics
- Game domain
- The `command_c` discovery boundaries are an INVENTORY artefact, not a coverage gap (`0x1000d8a0`, `0x1000d930`)
- Round 1039 reproduced a retired postlink image
- Round 1043's structural checks did not establish completion
- Round 1054: a Wine drive map was unnecessary for these `__FILE__` literals
- Round 1078's completed-data claim measured a postlinked image (`0x10035000`, `0x1176759c`)
- Round 1089's non-text parity came from copying and was retracted
- Finding code we already reversed in another target: `rebrew source import-related`
- The three binaries: one compiler version, two code generators (round 1379, definitive) (`0x000a2306`, `0x00302354`)
- Game code only (round 1379c) (`0x00459940`, `0x00492990`, `0x004fffb0`)
- Does the Processor Pack work for the SERVER target? (round 1379e) (`0x004514d0`, `0x00453b30`, `0x1000c3c0`, `0x100100a0`, `0x100151e0`)
- Using the two clients as a reference for the remaining server work (round 1380)
- Native findings (`0x00401470`, `0x00402aa0`, `0x00405870`, `0x00406410`, `0x00406560`, `0x0040cba0`, `0x0040dd90`, `0x0040eca0`, `0x00410710`, `0x00410740`, `0x00410770`, `0x004112e0`, `0x00411820`, `0x004124b0`, `0x0041e350`, `0x0041e3e0`, `0x0041e410`, `0x0041e440`, `0x0041e490`, `0x0041e4d0`, `0x00420b70`, `0x00420ba0`, `0x004210a0`, `0x004210ed`, `0x0042114a`, `0x00421262`, `0x00421290`, `0x00421328`, `0x00422ba0`, `0x00422c30`, `0x00422c60`, `0x004247e0`, `0x00424810`, `0x00435500`, `0x00450a00`, `0x00450b20`, `0x00450c5c`, `0x00453890`, `0x004737e0`, `0x00476c80`, `0x00499a50`, `0x00499ad0`, `0x0049a010`, `0x004a1130`, `0x004a16f0`, `0x004bc5a0`, `0x004bcb80`, `0x004c4d30`, `0x004cef30`, `0x004e58e0`, `0x004e5af0`, `0x004e73c0`, `0x004e73f0`, `0x004e7600`, `0x004e77e0`, `0x004fe5e2`, `0x004fe60c`, `0x00501030`, `0x0050108a`, `0x005010a3`, `0x005010b2`, `0x005010dc`, `0x00503e80`, `0x00504100`, `0x00504e70`, `0x00505df0`, `0x00508e40`, `0x00509ee0`, `0x0050a640`, `0x0050dac0`, `0x005a3580`, `0x005a35c2`, `0x005de784`, `0x005eaad6`, `0x005ecef0`, `0x005ed0a8`, `0x005eee50`, `0x005eee60`, `0x005fcc78`, `0x005fcc7c`, `0x005fcc80`, `0x00600190`, `0x00602840`, `0x0061aa00`, `0x0062e108`, `0x00633174`, `0x00633178`, `0x0063317c`, `0x00633180`, `0x0064d3f8`, `0x0066080a`, `0x00662384`, `0x0066417c`, `0x00664340`, `0x0066cc40`, `0x0066cc50`, `0x00675058`, `0x00675da8`, `0x0067bbdc`, `0x0067bbe0`, `0x0067bbe4`, `0x0067edf8`, `0x006814a8`, `0x0068d934`, `0x00699748`, `0x006f1bc5`, `0x00770ae0`, `0x00770b60`, `0x007f4c00`, `0x00868050`, `0x00889f74`, `0x0090e094`, `0x009b4a40`, `0x009b8dc0`, `0x00f8ab80`, `0x00f8abc8`, `0x01011980`, `0x010119c8`, `0x0143ab0c`, `0x01460b00`, `0x01467360`, `0x014673cc`, `0x014a5c6c`, `0x014cbcc0`, `0x014ce8a0`, `0x014ce90c`, `0x10014ee0`, `0x10019be0`, `0x1002d878`)

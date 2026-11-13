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
Gold uses DirectInput 7 and GoldTL uses DirectInput 8. The observed interface
prefixes in `src/client_input.h` share an ABI; the factories and versions differ.

Client data can be absent from the server despite adjacent shared code. Library
bands can contain different code generators. Neither adjacency nor a constant VA
shift establishes a counterpart.

Use `uv run rebrew source import-related --help` for reviewed shared-source imports.
Source sharing still requires destination compilation and complete operand checks.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.

# Original build facts

Native and compiler observations. [Current work](TODO.md) has status.
[Build instructions](build.md) have setup and reference hashes. Paths below
were checked in the local reference images on 2026-11-24.

## Original project

The server image embeds `D:\Develop\DieGildeAddOnServer\server.c` and paths
under `D:\Develop\DieGildeAddOn` and `D:\Develop\Units`. GoldTL embeds
`D:\develop\DieGildeAddOnVc\Release\Europa1400Exp_TL.pdb` and source paths such
as `D:\develop\units\Msx\msx.c` and `D:\develop\units\net\net.c`. Gold has
paths under `D:\develop\units` and `D:\develop\Units`.

Preserve the case of attested paths. Check function placement independently of
the presence of a source-unit string. [Source layout](source-layout.md) · [Naming](naming_conventions.md)

## Configured build

Compiler profiles and runtimes in `rebrew-project.toml`

| Context | Server | GoldTL | Gold |
| --- | --- | --- | --- |
| Project compiler profile | `msvc-6.0-sp5` | `msvc-6.0-sp5-pp` | `msvc-6.0-sp5-pp` |
| Configured runtime | `/MT`, `LIBCMT.lib` | `/MT`, `LIBCMT.lib` | `/ML`, `LIBC.lib` |

The same `CL.EXE` version can use different code generators. Game-only x87
compare patterns and complete same-source controls distinguish plain VC6 from
the Processor Pack. Rich headers also describe library objects. Some bodies
are identical under both generators, so one matching function cannot select
the profile. The project file records the lock from round 1379: the server
image has the plain VC6 compare idiom, and GoldTL game code (outside the
declared D3DX8 band) has the Processor Pack idiom.

Default game optimization is `/O2 /Gd`. Effective per-target and per-TU inputs
live in `rebrew-project.toml` and managed metadata. Independently built
libraries can have other evidenced contexts. Historical flag probes are not
production overrides.

## Cross-target recovery

Match reference bytes, native calls, fields and literals before sharing a body.
Equal names, or a score of 100, do not establish equal layouts or providers.
Gold uses DirectInput 7 and GoldTL uses DirectInput 8. The observed interface
prefixes in `src/client_input.h` share an ABI. The factories and versions differ.

Client data can be absent from the server despite adjacent shared code. Library
bands can contain different code generators. Neither adjacency nor a constant
VA shift establishes a counterpart.

`uv run --frozen rebrew source import-related --help` documents reviewed
shared-source imports. Sharing still requires destination compilation and
complete operand checks.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.

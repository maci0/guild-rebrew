# docs/

Every file here is empirical: a claim cites the address, round, or command
that produced it. Live numbers (verify count, `.text` residue, `.data`
divergence) are the `scripts/gate.sh` defaults; a figure written anywhere in
these files is the value at the time it was written.

## Which file to open

| When you are | Open | Keyed by |
|---|---|---|
| Reshaping C that compiles but does not match | `msvc6-c-shapes.md` (start at its "Index by symptom") | section number |
| Chasing a register choice (`eax`/`ecx`/`edx`, callee-saved homes, slot map) | `msvc6-allocator.md` (its "Index"), then `codegen-walls.md` §1 | Finding number, function |
| About to try a spelling that may already be exhausted | `codegen-walls.md` | section number |
| Reading a score, a residue number, or a tool's verdict | `measure-traps.md` (§1: only the linked residue decides) | section number |
| Touching link order, `.data`/`.rdata`, imports, or postlink | `msvc6-link-layout.md` | section number |
| Deciding whether a client-only function belongs in the server build | `client-only-sweep.md` (appendix to `msvc6-link-layout.md` 5f) | TL VA |
| Running agents, parallel sessions, or the build tooling | `workflow-traps.md` | section number |
| Needing a fact about the original build, toolchain, or targets | `general-knowledge.md` | topic |
| Naming a function, global, or source file | `naming_conventions.md` | prefix, source file |
| Changing vendored zlib or minizip code | `vendoring.md` | patch number |
| Checking whether a residue function has a known semantic bug | `behavioral-verdicts.md` | function |
| Looking up game, binary, or community facts | `game-compendium.md` | topic |
| Picking up open work or reading round history | `TODO.md` (latest `**Round-N:**` note under Continuation notes) | round |

## Before probing an address

Look it up first; the entries are keyed by address, and a keyword grep only
finds what you already know the words for:

```sh
python3 scripts/whathas.py 0x<VA>              # every doc entry citing this VA
python3 scripts/whathas.py 0x<VA> --window 64  # widen the band
```

`whathas.py` searches `msvc6-c-shapes.md`, `msvc6-allocator.md`,
`codegen-walls.md`, `measure-traps.md`, `workflow-traps.md`, and `TODO.md`.

## Conventions

- `msvc6-c-shapes.md` is levers that work, `codegen-walls.md` is levers
  measured not to exist, `measure-traps.md` is instruments that lie. A new
  finding goes in exactly one of them; cross-link instead of copying.
- Section numbers are cited across files, by `whathas.py` output, and in
  source headers. Append new sections with the next free number; never
  renumber or reuse one.
- Server addresses are `0x100xxxxx`; client addresses (`0x4xxxxx` to
  `0x6xxxxx`) name the target (GOLDTL or GOLD) beside them, since the two
  clients place the same function at different VAs.

# Data ownership

A C definition or selected library member allocates storage. Headers declare it;
users reference it. An address, extern declaration, inventory row or byte match
alone does not identify an owner.

| Kind | Meaning |
| --- | --- |
| Object | One definition or selected archive member supplies bytes |
| Import | The linker/loader owns the pointer slot |
| Compiler literal | A compiler-owned object emits the complete literal |
| Alias/view | An evidenced offset and extent within an existing allocation |
| Span | A layout interval with no standalone allocation |

## Establish the object

Record the VA, complete extent, section, provenance and actual owner. Include
terminators and all evidenced elements; adjacency is not an array bound. A
zero-filled virtual tail has no file-backed payload and does not prove a BSS
source declaration.

Use the owning subsystem header for game declarations and the CRT header for
runtime declarations. Stock libraries retain their storage. Interior views need
an evidenced backing object; unknown extents/owners remain unknown.

Spans must not overlap named objects without an explicit relationship. Shrink or
retire a span when the underlying extent changes. Lint W037 checks definition
sizes and W038 checks unbacked overlaps. A layout recipe or copied reference blob
does not justify a new allocation.

## Keep access views bounded

The private 24-byte VFS directory entry is distinct from the pooled stream whose
constructor requests 320 bytes and accesses mode flags at +0x13c. A pointer
contract can remain opaque while its full layout is unknown.

Likewise, changing stream formals, adding declaration identities or binding a
literal does not create storage or earn a data verdict. Keep native access width,
C type, complete extent and allocation ownership as separate claims.

## Review and verify

Use `rebrew data list --all-targets --json`, target-specific `data bss`, and
`lint --all-targets` to inspect the catalog. Change rows only through locked
writers. Compare bytes and placement against the matching raw image/map; owner
assignment itself does not promote a verdict.

The [ownership audit](data-ownership-evidence.json) retains CRT/overlap evidence.
[Link layout](msvc6-link-layout.md) covers physical placement; [AGENTS.md](../AGENTS.md)
owns the full storage rules.

## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/data-ownership.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/data-ownership.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| Data ownership | - |
| <a id="extents-and-layout"></a>Extents and layout | - |
| <a id="historical-storage-investigation-october-4"></a>Historical storage investigation, October 4 | `0x10034684`, `0x10035408`, `0x11766788` |
| <a id="check-changes"></a>Check changes | - |
| <a id="vfs-stream-and-directory-entry-are-distinct-goal81-2026-10-17"></a>VFS stream and directory entry are distinct (Goal81, 2026-10-17) | `0x6b7fe4`, `0x6b7fec` |
| <a id="stream-contracts-do-not-create-storage-owners-goal82-2026-10-17"></a>Stream contracts do not create storage owners (Goal82, 2026-10-17) | `0x6500c2`, `0x699820`, `0x6a22a8`, `0x6a22c0`, `0x6a23ac`, `0x6a23d0`, `0x10058e0`, `0x10058e4` |

</details>

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

The private `VFS_FILE` record in `src/Develop/Units/vfs/vfs.c` is 24 bytes
on x86. It is distinct from `VFS_DIR` and from the pooled stream, which requests
320 bytes and accesses mode flags at +0x13c. A pointer contract can remain opaque
while its full layout is unknown.

Likewise, changing stream parameters, adding declaration identities or binding a
literal does not create storage or earn a data verdict. Keep native access width,
C type, complete extent and allocation ownership as separate claims.

## Review and verify

Use `uv run rebrew data list --all-targets --json`,
`uv run rebrew data bss --target server.dll --json`, and
`uv run rebrew lint --all-targets --json` to inspect the catalog. Change rows only through locked
writers. Compare bytes and placement against the matching raw image/map; owner
assignment itself does not promote a verdict.

The [ownership audit](data-ownership-evidence.json) retains CRT/overlap evidence.
[Link layout](msvc6-link-layout.md) covers physical placement; [AGENTS.md](../AGENTS.md)
owns the full storage rules.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.

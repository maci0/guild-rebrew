# Pure-C 1:1 Rebuilt Functions (MSVC6)

This tracks which `server.dll` functions we have successfully reimplemented in pure C and compiled with MSVC6 to produce byte-identical machine code.

Verification for all entries below:

- Function bytes: compiled `.text` slice is `cmp`-identical to the extracted original bytes.
- Full DLL: `make -C rebuild/c verify` produces `rebuild/Server/server_from_c.dll` that is identical to `original/Server/server.dll` (MD5/SHA256 match).

## Targets

- Reccmp annotation target alias used in this repo: `SERVER`

## Current List

| Function | VA Start | Size | C Source | Bytes Built | Inject `.text` Offset | Status |
|---|---:|---:|---|---|---:|---|
| Init | 0x10009320 | 48B | `rebuild/c/init.c` | `rebuild/c/build/init_48.bin` | 0x8320 | ✅ 1:1 |
| Exit | 0x10009350 | 68B | `rebuild/c/exit.c` | `rebuild/c/build/exit_68.bin` | 0x8350 | ✅ 1:1 |
| fcn_10003140 | 0x10003140 | 33B | `rebuild/c/fcn_10003140.c` | `rebuild/c/build/fcn_10003140_33.bin` | 0x2140 | ✅ 1:1 |

## Build / Verify

```bash
make -C rebuild/c verify
```

## Notes

- Offsets: `.text` raw begins at file offset `0x1000`, so the injection offset is `(file_offset - 0x1000)`.
- Annotations: see `rebuild/docs/MSVC6_PURE_C_WORKFLOW.md`.

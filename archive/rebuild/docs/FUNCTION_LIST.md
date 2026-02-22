# Function List - server.dll

## Summary

- **Total Functions**: 471 (r2 `aflj` inventory)
- **Documented**: 32
- **In Progress**: 0
- **Pending**: 439

Reference inventory:
- `rebuild/docs/R2_FUNCTIONS.md`

## Function Table

| Function | Start Address | End Address | Size | Description | Status | Doc Link |
|----------|---------------|-------------|------|-------------|--------|----------|
| fcn_10002fc0 | 0x10002fc0 | 0x10003138 | 376B | Table lookup + emit blocks via 0x10024024 | ✅ Complete | [fcn_10002fc0.md](functions/fcn_10002fc0.md) |
| fcn_10003140 | 0x10003140 | 0x10003161 | 33B | Index variable-length entry table | ✅ Complete | [fcn_10003140.md](functions/fcn_10003140.md) |
| fcn_10003170 | 0x10003170 | 0x100031cf | 95B | Byte classification via jump tables | ✅ Complete | [fcn_10003170.md](functions/fcn_10003170.md) |
| fcn_10003260 | 0x10003260 | 0x10003317 | 183B | Detect call instruction patterns before a pointer | ✅ Complete | [fcn_10003260.md](functions/fcn_10003260.md) |
| fcn_10003320 | 0x10003320 | 0x100034b4 | 404B | Large init/config routine + table loops | ✅ Complete | [fcn_10003320.md](functions/fcn_10003320.md) |
| fcn_100034c0 | 0x100034c0 | 0x10003513 | 83B | Reset globals + log loop | ✅ Complete | [fcn_100034c0.md](functions/fcn_100034c0.md) |
| fcn_10003520 | 0x10003520 | 0x100035c0 | 160B | Global-flag gated dispatch/emit routine | ✅ Complete | [fcn_10003520.md](functions/fcn_10003520.md) |
| fcn_100035c0 | 0x100035c0 | 0x10003637 | 119B | Global-flag gated helper (emit + notify) | ✅ Complete | [fcn_100035c0.md](functions/fcn_100035c0.md) |
| fcn_10003640 | 0x10003640 | 0x100036c4 | 132B | Flag-gated format + dispatch | ✅ Complete | [fcn_10003640.md](functions/fcn_10003640.md) |
| fcn_100036d0 | 0x100036d0 | 0x1000381c | 332B | Stream/header parse + flag-driven skipping | ✅ Complete | [fcn_100036d0.md](functions/fcn_100036d0.md) |
| fcn_10003820 | 0x10003820 | 0x10003892 | 114B | Stream byte reader / refill helper | ✅ Complete | [fcn_10003820.md](functions/fcn_10003820.md) |
| fcn_100038a0 | 0x100038a0 | 0x10003951 | 177B | Stream/state cleanup + free fields | ✅ Complete | [fcn_100038a0.md](functions/fcn_100038a0.md) |
| fcn_10002640 | 0x10002640 | 0x10002762 | 290B | Dispatch/logging handler | ✅ Complete | [fcn_10002640.md](functions/fcn_10002640.md) |
| fcn_100020a0 | 0x100020a0 | 0x1000220f | 367B | Longest match search (zlib) | ✅ Complete | [fcn_100020a0.md](functions/fcn_100020a0.md) |
| fcn_10001cf0 | 0x10001cf0 | 0x10001d61 | 113B | Read input data (zlib) | ✅ Complete | [fcn_10001cf0.md](functions/fcn_10001cf0.md) |
| fcn_10001bc0 | 0x10001bc0 | 0x10001ce2 | 290B | Slide hash window (zlib) | ✅ Complete | [fcn_10001bc0.md](functions/fcn_10001bc0.md) |
| fcn_10001910 | 0x10001910 | 0x100019ba | 170B | Deflate end/cleanup (zlib) | ✅ Complete | [fcn_10001910.md](functions/fcn_10001910.md) |
| fcn_10001890 | 0x10001890 | 0x10001902 | 114B | Flush pending output (zlib) | ✅ Complete | [fcn_10001890.md](functions/fcn_10001890.md) |
| fcn_10001860 | 0x10001860 | 0x1000188e | 47B | Output byte write helper (zlib) | ✅ Complete | [fcn_10001860.md](functions/fcn_10001860.md) |
| fcn_100015b0 | 0x100015b0 | 0x1000185f | 685B | Deflate parameter processing (zlib) | ✅ Complete | [fcn_100015b0.md](functions/fcn_100015b0.md) |
| fcn_10001330 | 0x10001330 | 0x10001529 | 505B | Deflate state initialization (zlib) | ✅ Complete | [fcn_10001330.md](functions/fcn_10001330.md) |
| fcn_100011f0 | 0x100011f0 | 0x10001325 | 309B | CRC32 update function (zlib) | ✅ Complete | [fcn_100011f0.md](functions/fcn_100011f0.md) |
| fcn_10001130 | 0x10001130 | 0x100011e3 | 179B | Network/socket initialization | ✅ Complete | [fcn_10001130.md](functions/fcn_10001130.md) |
| fcn_10006f40 | 0x10006f40 | 0x10006fa6 | 102B | deflate_state clear/init (zlib) | ✅ Complete | [fcn_10006f40.md](functions/fcn_10006f40.md) |
| fcn_10006ec0 | 0x10006EC0 | 0x10006F2C | 108B | Tree init helper | ✅ Complete | [fcn_10006ec0.md](functions/fcn_10006ec0.md) |
| fcn_100019c0 | 0x100019C0 | 0x10001A53 | 147B | Memory clear and setup | ✅ Complete | [fcn_100019c0.md](functions/fcn_100019c0.md) |
| fcn_10001530 | 0x10001530 | 0x100015A3 | 115B | Structure initialization | ✅ Complete | [fcn_10001530.md](functions/fcn_10001530.md) |
| fcn_10001000 | 0x10001000 | 0x1000112E | 302B | CRC32/checksum calculation | ✅ Complete | [fcn_10001000.md](functions/fcn_10001000.md) |
| fcn_10007580 | 0x10007580 | 0x100078E0 | 864B | Data processing/compression | ✅ Complete | [fcn_10007580.md](functions/fcn_10007580.md) |
| entry0 | 0x1001B9D4 | 0x1001BA71 | 157B | DLL entry point (DllMain) | ✅ Complete | [entry0.md](functions/entry0.md) |
| Init | 0x10009320 | 0x10009350 | 48B | Initialize server component | ✅ Complete | [Init.md](functions/Init.md) |
| Exit | 0x10009350 | 0x10009394 | 68B | Cleanup and shutdown | ✅ Complete | [Exit.md](functions/Exit.md) |

## Progress

32/471 functions documented (~6.8% complete)

All documented functions verified:
- ✅ Bit-identical NASM assembly
- ✅ Full documentation with C code
- ✅ DLL rebuild maintained

Last Updated: February 14, 2026

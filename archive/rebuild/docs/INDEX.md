# Documentation Index

This folder is the canonical documentation set for the DLL rebuild.

## Start Here

- `rebuild/docs/NATIVE_TOOLCHAIN.md` - End-to-end rebuild pipeline (NASM + optional MSVC experiments)
- `rebuild/docs/FUNCTION_LIST.md` - Master table of functions and status
- `rebuild/docs/functions/` - One doc per function

## Workflows

- `rebuild/docs/MSVC6_PURE_C_WORKFLOW.md` - Pure-C (MSVC6) function reimplementation workflow
- `rebuild/docs/FUNCTION_LEVEL_MATCH_WORKFLOW.md` - Byte-identical function matching workflow

## Tooling

- `rebuild/docs/TOOLING_REFERENCE.md` - Tools, commands, and common checks
- `rebuild/docs/NASM_ENCODING_DIFFERENCES.md` - Why NASM vs MSVC bytes differ; when `db` is required

## Reference

- `rebuild/docs/PE_CHECKSUM_ALGORITHM.md` - PE checksum notes (reference only; the target is bit-identical output)
- `rebuild/docs/R2_FUNCTIONS.md` - r2-derived function address/size inventory
- `rebuild/docs/MSVC_BUILD_GUIDE.md` - MSVC6 toolchain details

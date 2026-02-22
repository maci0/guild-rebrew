HANDOFF CONTEXT
===============
- "update docs and modularize the matcher engine"
- "consolidate tools and implement persistent caching"
- "ensure all md files are up to date"
GOAL
----
Reverse-engineer all ~471 functions in server.dll to byte-identical C89 source code compiled with MSVC6, maintaining a high-performance modular GA engine and a persistent build cache.
WORK COMPLETED
--------------
- Modularized the GA engine into the `matcher` Python package.
- Consolidated GA engine logic into `matcher.py` (powered by PyGAD).
- Implemented SQLite-backed persistent caching in `BuildCache` to accelerate iterative reversing.
- Updated all primary documentation (AGENTS.md, WORKFLOW.md, TOOLS.md, GA_MODEL_TRAINING.md).
- Added `pycparser` dependency for future AST-aware mutation support.
- Refactored `validate.py` into `catalog.py` (metadata) and `verify.py` (compilation).
- Verified the converged engine with bit-perfect diffing and relocation masking.
CURRENT STATE
-------------
- GA Engine: Unified, modular, and cached.
- Documentation: Fully synchronized with new architecture.
- Build Cache: `build_cache.db` stores all successful compilations.
- Toolchain: MSVC6 under Wine verified with ~60ms latency per call.
- Dependencies: `pefile`, `capstone`, `pygad`, `pycparser`.
PENDING TASKS
-------------
- Transition remaining regex-based mutations to AST-aware implementations in `rebrew.mutator`.
- Continue reversing functions using the new modular engine.
- Prioritize near-misses (1-5 byte diffs) using the GA's new persistent cache.
KEY FILES
---------
- tools/matcher.py - Unified GA entry point
- tools/matcher/ - Modular GA logic (core, compiler, scoring, parsers, mutator)
- tools/catalog.py - Annotation cataloging and dashboard JSON generation
- tools/verify.py - Bulk compilation verification
- build_cache.db - SQLite compilation result cache
- AGENTS.md - Master project reference (updated)
IMPORTANT DECISIONS
-------------------
- Canonical header format chosen: `/* name @ 0xVA (SizeB) - /flags - MATCH_TYPE [ORIGIN] */`
- GAME functions compile with /O2; MSVCRT/CRT functions with /O1 (sometimes /O1 /Oy-)
- JMP thunks (WS2_32 imports) cannot be tested at .obj level - they're linker-generated
- GA matcher is useful for near-misses (1-5 byte diffs) and flag sweeps
EXPLICIT CONSTRAINTS
--------------------
- "Continue, don't stop until you reversed all known functions 1:1; do not ask for permission for tool usage, you have it. Make sure to keep the catalog updated as you go along."
- C89 only (MSVC6): no `for(int i=...)`, no `//` comments, declare vars at block top
- "we use uv not pip" - Use `uv run python` for all Python commands
CONTEXT FOR CONTINUATION
------------------------
- ReVa Assistant is now available for Ghidra decompilation
- matcher.py has been documented in AGENTS.md - use --diff-only for quick comparison, --flag-sweep for finding optimal flags
- Near-miss functions are documented in AGENTS.md under "Near-Miss Status" table
- The test harness uses `uv run python reversed/test_func.py <src.c> <symbol> --va 0xVA --size N --cflags "/O2"`
- All .c files need the canonical header for catalog rebuild to work

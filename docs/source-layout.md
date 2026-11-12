# Source layout

Use one shared tree under `src/Develop/`, following attested `D:\Develop` paths.
Label inferred placement. A byte match does not establish the original TU.

Paths in this table are relative to `src/Develop/`.

| Location | Role |
| --- | --- |
| `DieGildeAddOn/game/` | Game units such as spiel, sim and aemter |
| `DieGildeAddOn/command/` | Command and lobby units |
| `DieGildeAddOn/auxillary/` | Plant subsystem; retain the attested spelling |
| `DieGildeAddOn/loadsave/` | Save/load code |
| `DieGildeAddOnServer/` | Server entry and shared declarations |
| `Units/` | Error, allocation, VFS, network, audio and renderer units |
| `Unassigned/` | Bodies whose original module/TU remains unresolved |

Reconstructed filenames and private headers may be inferred even when the parent
unit is attested. Native paths, diagnostics, counterparts and dependencies provide
placement evidence; automatic address clustering alone does not.

## Move, merge or split

Use `rebrew source organize review` to inspect all-target providers, native order,
compiler context and storage instances. Preserve baselines, includes, declaration
order and flags. Update managed identities through Rebrew writers, then compare
complete objects/operands and rebuilt images with `source organize check`.

Do not split a native sequence merely because recovered definitions currently
live in different files. A shared file may contain target-specific definitions;
the same symbol spelling can also name independent functions.

[Data ownership](data-ownership.md) covers storage and declarations. Keep types
in the owning subsystem header or private source and bind stable IDs through
`rebrew types bind`. Use `Units/d3/d3_object.h` for current D3 layouts.

Use `rebrew source units --json` for native path witnesses. Current definition
bindings belong in managed function metadata; merge receipts belong in
[provenance](provenance.md).

## Archived techniques

Original notebook: `docs/source-layout.md` in the [documentation archive](goal-history.md#full-notebooks).

- Moving sources (`0x0045f6c0`)
- MSX and D3 placement, October 11 (`0x0041fc10`, `0x0041fd70`, `0x0041fe10`, `0x00420120`, `0x004205e0`, `0x00420650`, `0x00420690`, `0x00420700`, `0x00420760`, `0x00420780`, `0x00420840`, `0x00423930`, `0x00423a90`, `0x00423b30`, `0x00423df0`, `0x00424250`, `0x004242c0`, `0x00424300`, `0x00424370`, `0x004243d0`, `0x004243f0`, `0x004244b0`, `0x00438780`, `0x00478860`, `0x00f8aae0`, `0x014611a0`, `0x014cc360`)
- Character subsystem placement (2026-10-11)
- Shared character scene and script helpers (2026-10-11) (`0x00402540`, `0x00402aa0`, `0x004033c0`, `0x00403bc0`, `0x00406790`, `0x00407330`, `0x0040c4f0`, `0x0040d410`)
- D3 type identities and full byte extents (2026-10-11)
- Shared client allocator helper checkpoint (2026-10-11)
- Client placement views (Goal75, 2026-10-17) (`0x00442d50`, `0x00447300`, `0x004cbe5a`, `0x004cbefc`, `0x004cc9da`, `0x004cca7c`, `0x0058fa00`, `0x0058fa60`, `0x0058fc80`, `0x0058fd20`, `0x005982d0`, `0x00598330`, `0x00598550`, `0x005985f0`)
- Scene command declaration boundary (Goal80, 2026-10-17) (`0x00525b40`)
- Network local-address placement (2026-11-01) (`0x00420d20`)
- Entity lookup and pricing placement (2026-11-01) (`0x00508e40`, `0x0050b980`)
- Line renderer placement (2026-11-01)
- Gold DirectDraw dialog placement candidate (2026-11-01) (`0x0041c830`)
- Shared client table search (2026-11-01) (`0x004f36e0`, `0x004f5810`)
- Office-slot type review (2026-11-01) (`0x1000b880`, `0x1000b8be`, `0x1000b90a`)
- Client crime counter (2026-11-01)
- Client cutscene readiness (2026-11-01) (`0x004c69c0`, `0x004c7550`, `0x004cd590`)
- Client cutscene execution (2026-11-01) (`0x004cca10`, `0x004cd590`)
- Client cutscene record lookup (2026-11-01) (`0x004e50a0`, `0x004e5120`, `0x004e5180`, `0x004e6a30`, `0x004e6ab0`, `0x004e6b10`)
- Gold queue-state lookup candidate (2026-11-01) (`0x004c3480`, `0x004c350f`, `0x004c3ae0`, `0x004c3b02`, `0x00519b17`, `0x00f31160`, `0x00f31166`, `0x00f81160`, `0x00f81166`)
- Shared client cutscene-record candidate (2026-11-01) (`0x00451840`, `0x00453e70`, `0x004e50a0`, `0x00519ad0`, `0x0052ae70`, `0x005305a0`)
- Gold D3 camera-position candidate (2026-11-01) (`0x0042ea90`, `0x0042ebb4`, `0x004379a0`, `0x00438a80`, `0x00438af0`, `0x00438d40`, `0x00438e60`, `0x0043b670`, `0x0043b6b0`, `0x0043b6e0`, `0x0043b790`, `0x0045cdf0`, `0x0045d680`, `0x0045d7e6`, `0x00531c2c`, `0x005fb5b0`, `0x0067a370`, `0x00fb9598`, `0x00fb98f4`, `0x00fc2700`, `0x00fc28f4`, `0x00fc52f0`)
- VFS finish-files consolidation candidate (2026-11-02) (`0x0042edf0`, `0x0042ee30`, `0x0042f5c0`, `0x0042f600`, `0x0042f620`, `0x005eab80`, `0x00633400`, `0x00633408`, `0x0065f220`, `0x006b7fe0`, `0x006b7fe8`, `0x0087b3c0`, `0x00b46741`)
- VFS archive-scanner candidate (2026-11-02) (`0x0042fb20`, `0x00430130`)
- Gold texture-wrapper candidate (2026-11-02) (`0x00448200`)
- VFS case-normalization contract (2026-11-02) (`0x0042e520`, `0x0042ecf0`)
- Client image-name lookup candidate (2026-11-02) (`0x0045a2e0`, `0x0045a3a0`, `0x0045a521`, `0x0045a666`, `0x0045db30`, `0x0045dbf0`)
- Client task-queue removal candidate (2026-11-02) (`0x004047a0`, `0x004050c0`, `0x00406210`, `0x00406db0`)
- Shared client game-matrix declarations (2026-11-02)
- Character action queue consolidation (2026-11-02) (`0x00402aa0`, `0x00404810`, `0x004048b0`, `0x00405130`, `0x00405180`, `0x004051d0`, `0x00405350`, `0x004053a0`, `0x00405400`, `0x00405460`, `0x004054b0`, `0x00405510`, `0x00405610`, `0x004061a0`, `0x00406580`)

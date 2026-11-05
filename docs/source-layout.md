# Source layout

Use one shared tree under `src/Develop/`, following attested `D:\Develop` paths.
Label inferred placement. A byte match does not establish the original TU.

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

Headers own declarations. C definitions or selected library members own storage.
Keep types in the owning subsystem header or private source and bind stable type
IDs through `rebrew types bind`. Use `Units/d3/d3_object.h` for current D3 layouts.

Native unit witnesses and past moves are indexed below. Their historical body
counts and source paths are not a current inventory.


## Archived findings

<details>
<summary>Historical sections and address lookup</summary>

The [November 5 archive](archive/2026-11-05-documentation.tar.xz) preserves the full
`docs/source-layout.md` notebook, including corrections and receipt paths. Entries below locate
historical claims, not current instructions or verdicts. Hex values include
code/data addresses and constants.

```sh
tar -xOf docs/archive/2026-11-05-documentation.tar.xz docs/source-layout.md | less
```

| Historical section | Referenced hex values |
| --- | --- |
| Source layout | - |
| <a id="moving-sources"></a>Moving sources | `0x45f6c0` |
| <a id="msx-and-d3-placement-october-11"></a>MSX and D3 placement, October 11 | `0x41fc10`, `0x41fd70`, `0x41fe10`, `0x420120`, `0x4205e0`, `0x420650`, `0x420690`, `0x420700`, `0x420760`, `0x420780`, `0x420840`, `0x423930`, `0x423a90`, `0x423b30`, `0x423df0`, `0x424250`, `0x4242c0`, `0x424300`, `0x424370`, `0x4243d0`, `0x4243f0`, `0x4244b0`, `0x438780`, `0x478860`, `0xf8aae0`, `0x14611a0`, `0x14cc360` |
| <a id="character-subsystem-placement-2026-10-11"></a>Character subsystem placement (2026-10-11) | - |
| <a id="shared-character-scene-and-script-helpers-2026-10-11"></a>Shared character scene and script helpers (2026-10-11) | `0x402540`, `0x402aa0`, `0x4033c0`, `0x403bc0`, `0x406790`, `0x407330`, `0x40c4f0`, `0x40d410` |
| <a id="d3-type-identities-and-full-byte-extents-2026-10-11"></a>D3 type identities and full byte extents (2026-10-11) | - |
| <a id="shared-client-allocator-helper-checkpoint-2026-10-11"></a>Shared client allocator helper checkpoint (2026-10-11) | - |
| <a id="client-placement-views-goal75-2026-10-17"></a>Client placement views (Goal75, 2026-10-17) | `0x442d50`, `0x447300`, `0x4cbe5a`, `0x4cbefc`, `0x4cc9da`, `0x4cca7c`, `0x58fa00`, `0x58fa60`, `0x58fc80`, `0x58fd20`, `0x5982d0`, `0x598330`, `0x598550`, `0x5985f0` |
| <a id="scene-command-declaration-boundary-goal80-2026-10-17"></a>Scene command declaration boundary (Goal80, 2026-10-17) | `0x525b40` |
| <a id="network-local-address-placement-2026-11-01"></a>Network local-address placement (2026-11-01) | `0x420d20` |
| <a id="entity-lookup-and-pricing-placement-2026-11-01"></a>Entity lookup and pricing placement (2026-11-01) | `0x508e40`, `0x50b980` |
| <a id="line-renderer-placement-2026-11-01"></a>Line renderer placement (2026-11-01) | - |
| <a id="gold-directdraw-dialog-placement-candidate-2026-11-01"></a>Gold DirectDraw dialog placement candidate (2026-11-01) | `0x41c830` |
| <a id="shared-client-table-search-2026-11-01"></a>Shared client table search (2026-11-01) | `0x4f36e0`, `0x4f5810` |
| <a id="office-slot-type-review-2026-11-01"></a>Office-slot type review (2026-11-01) | `0x1000b880`, `0x1000b8be`, `0x1000b90a` |
| <a id="client-crime-counter-2026-11-01"></a>Client crime counter (2026-11-01) | - |
| <a id="client-cutscene-readiness-2026-11-01"></a>Client cutscene readiness (2026-11-01) | `0x4c69c0`, `0x4c7550`, `0x4cd590` |
| <a id="client-cutscene-execution-2026-11-01"></a>Client cutscene execution (2026-11-01) | `0x4cca10`, `0x4cd590` |
| <a id="client-cutscene-record-lookup-2026-11-01"></a>Client cutscene record lookup (2026-11-01) | `0x4e50a0`, `0x4e5120`, `0x4e5180`, `0x4e6a30`, `0x4e6ab0`, `0x4e6b10` |
| <a id="gold-queue-state-lookup-candidate-2026-11-01"></a>Gold queue-state lookup candidate (2026-11-01) | `0x4c3480`, `0x4c350f`, `0x4c3ae0`, `0x4c3b02`, `0x519b17`, `0xf31160`, `0xf31166`, `0xf81160`, `0xf81166` |
| <a id="shared-client-cutscene-record-candidate-2026-11-01"></a>Shared client cutscene-record candidate (2026-11-01) | `0x451840`, `0x453e70`, `0x4e50a0`, `0x519ad0`, `0x52ae70`, `0x5305a0` |
| <a id="gold-d3-camera-position-candidate-2026-11-01"></a>Gold D3 camera-position candidate (2026-11-01) | `0x0042ea90`, `0x0042ebb4`, `0x4379a0`, `0x438a80`, `0x438af0`, `0x438d40`, `0x438e60`, `0x43b670`, `0x43b6b0`, `0x43b6e0`, `0x43b790`, `0x45cdf0`, `0x45d680`, `0x45d7e6`, `0x00531c2c`, `0x5fb5b0`, `0x67a370`, `0xfb9598`, `0xfb98f4`, `0xfc2700`, `0xfc28f4`, `0xfc52f0` |
| <a id="vfs-finish-files-consolidation-candidate-2026-11-02"></a>VFS finish-files consolidation candidate (2026-11-02) | `0x0042edf0`, `0x0042ee30`, `0x0042f5c0`, `0x0042f600`, `0x0042f620`, `0x005eab80`, `0x00633400`, `0x00633408`, `0x0065f220`, `0x006b7fe0`, `0x006b7fe8`, `0x0087b3c0`, `0x00b46741` |
| <a id="vfs-archive-scanner-candidate-2026-11-02"></a>VFS archive-scanner candidate (2026-11-02) | `0x0042fb20`, `0x00430130` |
| <a id="gold-texture-wrapper-candidate-2026-11-02"></a>Gold texture-wrapper candidate (2026-11-02) | `0x00448200` |
| <a id="vfs-case-normalization-contract-2026-11-02"></a>VFS case-normalization contract (2026-11-02) | `0x42e520`, `0x42ecf0` |
| <a id="client-image-name-lookup-candidate-2026-11-02"></a>Client image-name lookup candidate (2026-11-02) | `0x0045a2e0`, `0x0045a3a0`, `0x0045a521`, `0x0045a666`, `0x0045db30`, `0x0045dbf0` |
| <a id="client-task-queue-removal-candidate-2026-11-02"></a>Client task-queue removal candidate (2026-11-02) | `0x004047a0`, `0x004050c0`, `0x00406210`, `0x00406db0` |
| <a id="shared-client-game-matrix-declarations-2026-11-02"></a>Shared client game-matrix declarations (2026-11-02) | - |
| <a id="character-action-queue-consolidation-2026-11-02"></a>Character action queue consolidation (2026-11-02) | `0x00402aa0`, `0x00404810`, `0x004048b0`, `0x00405130`, `0x00405180`, `0x004051d0`, `0x00405350`, `0x004053a0`, `0x00405400`, `0x00405460`, `0x004054b0`, `0x00405510`, `0x00405610`, `0x004061a0`, `0x00406580` |

</details>

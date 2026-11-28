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
| `DieGildeAddOn/unknown/` | Existing unresolved placement; review alongside `Unassigned/` before moving it |

Reconstructed filenames and private headers may be inferred even when the parent
unit is attested. Native paths, diagnostics, counterparts and dependencies provide
placement evidence; automatic address clustering alone does not.

## Subsystem directories

Native paths attested in the binaries' strings: `DieGildeAddOn\auxillary\plant.c`,
`DieGildeAddOn\command\command.c`, `DieGildeAddOn\command\lobbycommands.c`,
`DieGildeAddOn\game\{aemter,alchemistry_logic,friedhof_logic,sim,spiel}.c`,
`DieGildeAddOn\loadsave\loadsave.c`, `DieGildeAddOnServer\server.c`, `Units\d2.v1\GFX.C`,
`Units\d3\{d3_d3d,d3_engine,d3_interface,d3_sky,ts_texture}.c`, `Units\d3_tools\d3_tools.c`,
`Units\dd_vesa\Dd_vesa.c`, `Units\Error\Error.c`, `Units\m_alloc\m_alloc.c`,
`Units\Msx\msx.c`, `Units\net\{broadcast,net}.c`, `Units\vfs\vfs.c`.

A file whose original unit is unknown goes to the directory of its function's subsystem prefix
([prefixes](naming_conventions.md#module-prefix-system)); this places the file, not its TU.

| Prefixes | Directory | Basis |
| --- | --- | --- |
| `cm_`, `lb_` | `DieGildeAddOn/command/` | attested command and lobby units |
| `ls_` | `DieGildeAddOn/loadsave/` | attested loadsave unit |
| `gm_`, `he_`, `ai_`, `hst_`, `ahm_`, `amt_`, `ch_`, `cut_`, `gv_`, `gs_`, `lc_`, `rd_` | `DieGildeAddOn/game/` | attested game units |
| `main_`, `init_`, `io_`, `sv_`, `am_`, `ob_` | `DieGildeAddOn/game/` | inferred: client entry and state; `WinMain` is there |
| `evt_`, `ecmd_` | `DieGildeAddOn/game/` | inferred: event scripts beside their host `hst_` |
| `msx_` | `Units/Msx/` | attested audio unit |
| `sb_`, `sbs_` | `Units/Msx/` | inferred: sample banks of the audio unit |
| `nt_` | `Units/net/` | attested network unit |
| `vfs_` | `Units/vfs/` | attested VFS unit |
| `txt_` | `Units/vfs/` | inferred: every txt_ function loads, parses, looks up or releases text-bank data, whose type and file loader (`vfs_text.c`, `txt_loadTextFile.c`) are in the VFS unit |
| `dd_` | `Units/dd_vesa/` | attested display driver unit |
| `d2_`, `gfx_`, `shp_` | `Units/d2.v1/` | attested 2D unit; `shp_` inferred |
| `d3_`, `d3snd_`, `d3sm_`, `d3e_`, `d3d_` | `Units/d3/` | attested D3 engine; `d3sm_`, `d3e_` inferred |
| `m_`, `hp_` | `Units/m_alloc/` | attested allocation unit; `hp_` inferred |

Files whose function is unnamed, and prefixes without a subsystem (`rt_`, `tb_`, `client_`,
`gold_`, `z_`, `wr_`), stay in `Unassigned/`. Files a server row names are not
moved by prefix.

## Move, merge or split

Use `rebrew source organize review` to inspect all-target providers, native order,
compiler context and storage instances. Preserve baselines, includes, declaration
order and flags. Update managed identities through Rebrew writers. Recheck
complete objects and operand bindings, then compare preserved and rebuilt raw
images with `rebrew source organize check`.

Do not split a native sequence merely because recovered definitions currently
live in different files. A shared file may contain target-specific definitions;
the same symbol spelling can also name independent functions.

[Data ownership](data-ownership.md) covers storage and declarations. Keep types
in the owning subsystem header or private source and bind stable IDs through
`rebrew types bind`. Use `Units/d3/d3_object.h` for current D3 layouts.

Use `rebrew source units --json` for native path witnesses. Current definition
bindings belong in managed function metadata; merge receipts belong in
[provenance](provenance.md).

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.

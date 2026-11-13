# Naming conventions

Attested diagnostic/path spellings win, including original errors such as
`gm_ObjectsAvailble` and German nouns such as `Objekt`. A semantic role or a
community label does not establish the original name. Mark inferred names.

## Module prefix system

Use an evidenced module prefix. Do not invent one for a unit that lacks it.
Error and broadcast helpers retain unprefixed descriptive names where no original
prefix is attested. A `fio_` infix identifies module file I/O, as in
`amt_fio_LoadAemter`.

| Prefixes | Subsystems |
| --- | --- |
| `cm_`, `gm_`, `lb_` | Commands, game/entities, lobby |
| `ahm_`, `gv_`, `sim_`, `amt_`, `ls_`, `plt_` | Alchemy, graveyards, simulation, offices, persistence, plants |
| `m_`, `vfs_`, `srv_` | Allocation, virtual files, server |
| `ch_`, `ai_`, `he_`, `cut_` | Characters, AI, events, cutscenes |
| `d2_`, `d3_`, `txt_`, `lc_`, `rd_` | UI, renderer, text, location, records |
| `sv_`, `io_`, `init_`, `main_`, `nt_`, `ob_`, `gs_`, `am_` | Client state, I/O, startup, main loop, network, objects, court, method registry |
| `evt_`, `ecmd_`, `hst_`, `msx_`, `sbs_` | Event scripts, event commands, script host, MSX audio, sample banks |

Asset/config prefixes are not automatically function prefixes.

Prefix witnesses in the current source tree:

| Prefix | Witness |
| --- | --- |
| `evt_` | `src/Develop/Units/vfs/GOLDTL.evt_LoadScript.c`, diagnostic naming `evt_LoadScript` |
| `ecmd_` | `src/Develop/Unassigned/GOLDTL.ecmd_LoadScene.c`, diagnostic naming `ecmd_LoadScene` |
| `hst_` | `src/Develop/Unassigned/GOLDTL.hst_ParseText_Fake_1st_Pass.c`, diagnostic naming `hst_ParseText_Fake_1st_Pass` |
| `msx_` | `src/Develop/Units/Msx/msx.c`, assertion path `D:\develop\units\Msx\msx.c`; attests the unit, not a function spelling |
| `sbs_` | `docs/name-ledger.tsv`, `sbs:CreateSB` witness for `sbs_CreateSB`; definition in `src/Develop/Units/m_alloc/GOLDTL.sbs_CreateSB.c` |

## Function naming

Use `prefix_VerbNoun` for inferred function names, with the original module style.
Keep English verbs and German game nouns where the binary uses them.
`cm_Chk*` usually validates and `cm_Ex*` executes, but recover each actual contract;
the names do not prove its signature or return values.

Use CRT headers for library functions. A private runtime helper's identity does
not make it a game routine or prove a selected archive provider.

## Variable naming

- Preserve attested globals such as `lpGebaeudePROT`, `lpObjekteINST`,
  `gm_ObjektNr2MinimalHersteller` and `cm_LastSyncCount` exactly.
- Inferred module globals use `<module>_CamelCase`. Heap table pointers use `lp`
  plus a German noun and PROT/INST where supported; typed pointers use `tp_`.
- Actual file statics use `s_`. Packet/struct fields use German snake_case.
- Compiler literals have no C source identifier. Their metadata rows use
  `str_<content>`, `flt_<value>` or `dbl_<value>`.
- Keep unresolved address labels and layout-span names until evidence supports a
  name, backing object and owner. Do not create new global `g_` naming conventions.
- Local names are inferred descriptions. Renaming one can still affect compilation
  context, so preserve compiler-sensitive forms until measured.

## Struct naming

Use `UPPER_CASE` for inferred types. Unknown fields retain offset/unknown labels;
access width or a stride does not prove a complete original type or allocation.

## Enum / constant naming

Follow the attested `prefix_UPPER_SNAKE` style, for example `cmdt_ALLOC_SPIELER`,
`ob_MARKTSTAND`. Preserve exceptions such as `GM_WINTER`.

## Rename safely

Use `rebrew source rename` with the target-qualified `MODULE.0xVA` identity where
spelling is ambiguous. Preview scope, providers, callers and linker anchors;
apply the reviewed digest, then verify affected targets. Naming does not earn a
byte verdict. [Source layout](source-layout.md) owns placement guidance.

[`name-ledger.tsv`](name-ledger.tsv) records reviewed naming
batches: old and new name, `attested` or `inferred`, confidence, TL/GOLD/server twins
and the evidence. An `attested` name comes from a string, script command or twin
symbol in the binary; an `inferred` name is a description of the verified body and
may change when better evidence appears.

Recheck the current managed binding before using a recorded name or address.

Older write-ups are in the [archive](goal-history.md#full-notebooks) under this filename.

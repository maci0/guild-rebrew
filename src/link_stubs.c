/* link_stubs.c - the single definition for symbols whose owner TU is not
 * linked at that address yet.
 *
 * Not part of the rebrew matching pipeline: rebrew test compiles one TU
 * and does not see this file.
 *
 * What lives where:
 *   - one definition, in the .c the linker places at that address;
 *   - extern declarations, in game_data.h when more than one TU uses the
 *     name, otherwise next to the use;
 *   - string bytes that the reference stores as literals stay literals in
 *     the using TU.  A named array there is emitted before those literals.
 *   - constants whose bytes already sit in the .rdata restore blob are
 *     defined here as writable objects, so .rdata is not given a second
 *     copy.  Do not mark them const and do not move them into an earlier TU.
 *
 * A file-scope name with no extern and no initializer is a tentative
 * definition (COMMON).  The linker parks COMMON past the other contributions.
 * Give such a symbol an initializer here, or an extern at every other TU.
 */

// SUPPORT: SERVER placeholder data definitions keep the link closed while
// TUs progressively claim their globals (owner TU extern-declares under its
// own DATA/GLOBAL marker; this file holds the single definition meanwhile)

// VA anchors live on the owner TUs by design — no VA markers here, so E013
// (duplicate VA) and W021/W022 scaffolding noise stay silent.

/* Global variable stubs */
#include <time.h>

/* g_game_speed_index is defined in alchemistry_logic3.c at 0x1002c3f4.
 * A second `_g_game_speed_index` here was a different symbol
 * (__g_game_speed_index) with no reader. */
float _g_stat_max = 0;
double _g_stat_max_d = 0;
float _g_stat_min = 0;
double _g_stat_min_d = 0;
/* fcn_10016ea0 was a 4-byte DATA stub for 0x10016ea0, which is the function
 * gm_SubObjectNoKill (spiel_dumpD.c).  gv_HireProductionWorker.c and
 * gv_ExtendProductionTime.c called it as a function, so the link resolved
 * those calls to a data address.  Both now call gm_SubObjectNoKill directly.
 * (scripts/gen_link_stubs.py no longer exists; edit by hand.) */
float g_output_share[1] = {0.0f};
int g_field_worker_count[4] = {0};
int g_field_entry_count[4] = {0};
/* Address-only stubs removed. The bytes already have owners:
 *   0x1002d444/45c/474  allocation-tag literals
 *   0x1002d4f0          g_save_header_tail in ls_LoadSavegameHeader.c
 *   0x10031004          the spiel.c path, pushed as an immediate
 *   0x10031484/b8       string literals in the spiel TUs
 * Nothing referenced the g_<va> names. */

unsigned char* g_EntityListStart = 0;
unsigned char* g_EntitySearchPtr = 0;
unsigned char g_FilterActive = 0;
int g_FilterId = 0;
unsigned char g_FilterType = 0;
unsigned short g_FilterVal25 = 0;
unsigned short g_FilterVal27 = 0;
unsigned char g_FilterVal30 = 0;
int g_SearchCount = 0;
unsigned char g_SearchFlag = 0;
void* g_SomeGlobal = 0;
char* g_action_table_base = 0;
int g_active_player_count = 0;
/* g_alloc_counter is defined in Units/m_alloc/m_alloc.c (0x10034638). */
char* g_array_base = 0;
int g_console_handle = 0;
float g_const_42_0 = 0;
float g_const_1_over_32767 = 0;
/* g_default_group_name / _4 are gone: they are the two dwords of "_main_:" at
 * 0x10028938, now DEFINED in Units/m_alloc/m_alloc.c as the real 8-byte string.
 * Zeroed stubs here put them at 0x100366dc and left the reference's eight bytes
 * missing from .data entirely. */
/* g_next_family_index and gm_CurrentHumanFamilyCount are defined in spiel62.c. */
char* g_item_def_table = 0;
// GLOBAL: SERVER 0x10035a0c
unsigned int g_entity_records[768] = {0};
float g_const_1_0 = 0;
float g_const_neg_1_0 = 0;
// DATA: SERVER 0x100256cc
float g_const_0_0 = 0;
// DATA: SERVER 0x10025680
float g_graveyard_const_a = 0;
// DATA: SERVER 0x100257c4
float g_graveyard_const_b = 0;
// DATA: SERVER 0x100257c8
float g_graveyard_const_c = 0;
int g_mem_pool_overflow_flag = 0;
char g_msg_buf[1] = {0};
int g_object_count = 0;
char g_office_slots[0x3f0];

/* g_query_limit is defined in gm_NextEntityQueryMatch.c. */
short g_record_table[1] = {0};
char* g_table = 0;
/* vfs_CleanupSubobject, vfs_CompressBlock, vfs_GetErrnoPtr,
 * vfs_StreamClose, vfs_WriteBufferLocked were int-sized data stubs
 * named after functions. Nothing references them. compress_block is
 * static inside references/zlib-1.1.3/trees.c; the other four names
 * were dead prototypes already dropped from the vfs sources. */

/* Big BSS arrays (declared `extern TYPE x[]` in sources; must be DEFINED
 * non-tentatively here — tentative defs become COMMON weak symbols the
 * linker parks at the END of .data, pushing folded operand bases (symbol +
 * struct offset) out of the postlink rewrite range and breaking byte
 * identity.  Real sparse layout (8 slots at 0x101deb00) is the data-restore
 * TU's job; sizes here just need to fit the .data VS and stay in range.) */
unsigned char g_connections[0x264264] = {0};
unsigned int g_player_slot_field = 0;
unsigned int g_player_slot_overflow = 0;
// GLOBAL: SERVER 0x114ffe24
char g_player_slot_overflow_pad[0x264260] = {0};

/* BSS tail pad: grows .data VS to the original's 0x174059c (zero-init -> .bss).
 * Sized so the section ends exactly there: the layout-map coverage rule
 * (`_map_coverage`) accepts a data pointer only when it lands inside the
 * REFERENCE's .data span, which is its VirtualSize, so a pad that overshoots
 * pushes the common symbols past the end and every operand that names one
 * fails (docs/TODO.md round 139).  Re-measure with `rebrew data --bss` or by
 * comparing our .data VS against 0x174059c after any data change: 0x329c of
 * pad was the surplus when this was written. */
/* Grew by 0x60 when the unreferenced g_<va> / fcn_1001a6a1 / $T57600
 * stubs were removed, so the section end stays at the reference
 * VirtualSize 0x174059c. */
/* Shrunk by 0xfc when g_log_buffer moved as char[256] instead of the
 * old 4-byte stub. Grew by 0x14 when the five unused vfs_* int stubs
 * were removed. */
/* Grew by 0xe70 when __bufin stopped occupying 0x1000 of BSS and the
 * mlock critsect block grew by 0x190.  The following commons have to
 * stay below the reference .data end 0x1176759c: a displacement of
 * g_list_head+0x4a is otherwise past that end, and postlink will not
 * rewrite an operand that does not point into the reference span.
 * 0x60 is a multiple of the linker's 32-byte tail alignment. */
unsigned char g_bss_tail[0x1267a98] = {0};

/* String literal globals */

/* Special forwarding stubs */
extern int __stdcall ServerMainThread(void*);

/* removed round 1386: unreferenced in the tree, and its body was emitted at
   0x10023850 -- past the reference .text end.  Re-add only with a caller. */

/* The compiler emits an undefined __fltused reference from any TU that uses
 * floating point.  In the original binary that reference pulled LIBCMT's
 * fpinit.obj, whose .rdata (the "IsProcessorFeaturePresent"/"KERNEL32"
 * loader helper + __real constants) would otherwise land in OUR .rdata after
 * the restored blob and duplicate the bytes the blob already carries at the
 * original RVA.  Defining the marker here satisfies the reference without
 * pulling fpinit.obj — the FPU init code itself lives in run_000.c.
 * The value is never read; presence is all the linker checks. */
int _fltused = 0;

/* --- Auto-added stubs for symbols lost during naked->C conversion --- */
int g_worker_entry_count = 0;
/* GROUP B: game memset/memmove (0x10021240 / 0x1001b200) - stubs until the
 * crt mem TUs are reversed; postlink rewrites call targets to the reference
 * VAs. */
int g_field_worker_count_wt0[4] = {0};
int g_field_worker_count_wt1[4] = {0};
int g_field_worker_count_wt2[4] = {0};
int g_field_worker_count_wt3[4] = {0};
/* 0x10034624 g_array_count and 0x10034640 g_array_ptr are defined in
 * gm_Open.c. 0x10034628..34 g_stat1..4 are defined in m_alloc2.c.
 * 0x10034638 g_alloc_counter is defined in m_alloc.c. */
/* 0x117640a0..c0 are g_alloc_root_* above. 0x117640c4 is g_list_head
 * in srv_LoadBuf.c. */
float g_const_21_0 = 0;
// GLOBAL: SERVER 0x1009aca0
unsigned char g_entity_base[1] = {0};
// GLOBAL: SERVER 0x1009b760
int g_entity_end = 0;
unsigned char* g_entity_ptr = 0;
/* Sell msgs: real .data strings (ExSell imm32); overlay GLOBAL on alchemistry_logic2.c */
/* g_player_slots_base removed: ExSell uses g_connections@0x101deb00 */
char g_relationship_matrix_primary[] = {0};
char g_relationship_matrix_secondary[] = {0};
int g_sim_ents = 0;
/* g_unknown_1de450 removed round 932: it was a SECOND definition of the same
   address as `char* g_item_def_table` above (line 78), and wrongly typed `int`
   against that `char*`.  Two symbols for one .data address is the naming rule's
   "one word, one meaning" broken, and it is why operands naming it resolved into
   the stub region instead of the attested symbol. */
/* inflate_blocks / inflate_blocks_free are provided by the vendored
 * references/zlib-1.1.3/infblock.c; stubs here would shadow the real ones. */

/* --- CRT locale stubs: resolve symbols that would otherwise pull
 * LIBCMT's locale objects (setlocal.obj/getqloc.obj/w_loc.obj/a_loc.obj),
 * which reference NLS APIs (EnumSystemLocalesA, GetLocaleInfoA, ...) that
 * the original binary does NOT import.  The original's locale data lives
 * in the restored .data gap (data_restore.c); postlink rewrites .text
 * operands to the reference addresses.  C names below map to the LIBCMT
 * symbols via MSVC6 cdecl decoration (C foo -> symbol _foo). --- */
int __setlc_active = 0;            /* ___setlc_active */
/* Zero, so this is a real .bss definition. A non-zero initializer is 4
 * bytes of .data immediately before the gap blob and shifts that blob
 * off the reference. The symbol still keeps crt0.obj out of the link. */
int __app_type = 0;
int __unguarded_readlc_active = 0; /* ___unguarded_readlc_active */
int __lc_handle = 0;               /* ___lc_handle */
int __lc_codepage = 0;             /* ___lc_codepage */
int __lc_collate_cp = 0;           /* ___lc_collate_cp */
/* ___mb_cur_max and __pctype are the nlsdata1 / ctype tables. The split
 * link emits those .data sections; a zero here would be a second
 * definition and the tables would stay out of raw .data. */
int __crtGetLocaleInfoA = 0;       /* ___crtGetLocaleInfoA */
int __crtGetLocaleInfoW = 0;       /* ___crtGetLocaleInfoW */
int __get_qualified_locale = 0;    /* ___get_qualified_locale */

/* --- CRT-copy helpers referenced by the crt_region CRT layer that are not
 * yet reversed; stubs satisfy the link, postlink rewrites call targets to
 * the reference VAs. --- */
/* _getptd (0x1001d131) comes from LIBCMT tidtable.obj. A stub returning 0
 * would make the __errno / __doserrno accessors in crt_region/flsall.c
 * dereference a null per-thread block. */
char* __cdecl fcn_1001af30(const char* s, int c); /* 0x1001af30 - strchr */
char* __cdecl fcn_1001af30(const char* s, int c) { return 0; }
unsigned long __cdecl fcn_10020ff8(const char*, char**, int, void*); /* 0x10020ff8 - _strtoxl */
unsigned long __cdecl fcn_10020ff8(const char* s, char** e, int b, void* l) { return 0; }

/* --- CRT malloc stub: satisfy _malloc without pulling crt_region/malloc.c
 * (__try SEH-cookie .rdata that inflates the IAT→IMPORT gap). Postlink
 * rewrites call sites to the reference VAs. --- */
/* g_max_players is defined in ServerMainThread.c. */
int g_game_speed_table[5] = {0};
float g_color_scale = 0;
// GLOBAL: SERVER 0x100a8c94
unsigned int g_entity_slot_table[] = {0};
// DATA: SERVER 0x100241a0
unsigned int g_crc_table[256] = {0};
char* g_entity_type_table = 0;
unsigned short* g_query_base = 0;
/* Initialized so these are this file's BSS contribution, not COMMON
 * parked after every other TU.  Reference addresses: g_players_synced
 * 0x11764090, g_next_tick_time 0x101deaf0, g_host_flags 0x101de464,
 * g_module_path 0x101de9a0. */

/* removed round 1385: this stub displaced LIBCMT.lib(fputc.obj) at
   0x10023890; the reference's _putc is the library body. */


void (*g_panic_callback)(void) = 0;

/* --- .rdata float/double constants ---
 * Real operands of fmul/fadd/fsubr in the target, so a zero stub would
 * silently change behaviour; the literals below reproduce the original bytes
 * exactly (verified against server.dll at the annotated VAs).
 *
 * Deliberately NOT const: the originals live inside the rdata_restore blob
 * (0x100252e8..0x10026608), which already contributes those bytes to .rdata.
 * Emitting these as const would append a duplicate 0x20 bytes to .rdata and
 * shift the section, breaking the postlink layout check. As mutable objects
 * they land in .data, whose contents postlink replaces from the reference.
 *
 * `f88` is a dword fmul (float) in the target, unlike its qword neighbours. */
/* Uninitialized on purpose. The values live in the .rdata restore blob.
 * An initializer here is initialized .data and lands on top of the CRT
 * tables the gap blob has to copy from the reference. Postlink rewrites
 * the .text operands to the .rdata addresses. */
// DATA: SERVER 0x100256a0
float g_const_1_0f;
// DATA: SERVER 0x100256b0
float g_const_0_5;
// DATA: SERVER 0x100256b4
float g_const_0_1;
// DATA: SERVER 0x100256b8
float g_const_0_33;
// DATA: SERVER 0x100256c4
float g_const_30;
// DATA: SERVER 0x100256c8
float g_const_7;
// DATA: SERVER 0x10025714
float g_const_0_25;
double g_const_2;
double g_const_0_001;
// DATA: SERVER 0x100257d0
double g_const_half;
double g_const_one_d;
double g_const_0_2;
float g_const_0_6;
double g_const_8;
double g_const_900;
// DATA: SERVER 0x10025fa0
double g_const_1_over_720;
// DATA: SERVER 0x10025fa8
float g_const_896_0;
// DATA: SERVER 0x10025fac
float g_const_0_06875;
// DATA: SERVER 0x10025fb0
float g_const_2_2;
// DATA: SERVER 0x10025fb4
float g_const_1_5;
float g_const_0_01;

/* Tick rate read from the server ini by ServerMainThread; the binary's
 * initial value is 0 and the profile read overwrites it at startup. */

/* Small-block-heap pool region list, zero-init .data (BSS) in the original. */
/* __sbh_cntHeaderList and __sbh_pHeaderList are defined in
 * crt_region/data_globals.c. */

/* Game's private toupper (0x1001b0c0), called by OpenVfsStream. Forwarded to
 * the CRT rather than stubbed: OpenVfsStream uppercases path characters, so a
 * stub returning 0 would corrupt every lookup. */
int __cdecl crt_toupper(int c)
{
	if (c >= 'a' && c <= 'z') {
		return c - ('a' - 'A');
	}
	return c;
}

/* --- Call targets renamed to their real CRT entry points (2026-09-10) ---
 * The round-trip catalog work renamed vfs2.c's calls off dead local stubs onto
 * the real CRT symbols at their reference VAs (crt_locked_putc 0x1001add6,
 * _crt_locked_call4a 0x1001a931). Those names have no definition in the tree,
 * so the link needs them satisfied here; postlink rewrites the call targets to
 * the reference VAs (same contract as every other stub in this file).
 * NOTE: `rebrew gen-stubs` now classifies a called symbol as a function (it
 * scans both bare prototypes and call sites), but regenerating would still
 * drop the rest of this file's stubs, so these two stay by hand. */
int __cdecl _crt_locked_call4a(void* a, int b, int c, void* d)
{
	(void) a;
	(void) b;
	(void) c;
	(void) d;
	return 0;
}

/* Symbols in a member we must not pull (charmax is four bytes already
 * inside crt0msg's table). A real zero definition keeps that member out.
 * lconv and constpow's initialized tables are the library sections
 * scripts/emit_crt_data.py emits; a one-byte stand-in here would be a
 * second definition. ___lconv_static_null is a byte inside the ioinit
 * commons span, pinned in scripts/split_link.sh. */
char tzapiused = 0;
char lastTZ = 0;
int _charmax = 0;

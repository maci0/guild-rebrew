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
 *   - remaining constant placeholders are writable to avoid duplicating the
 *     .rdata restore blob. Recovered readonly constants move to native owner
 *     objects, which replace their corresponding blob spans.
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
/* fcn_10016ea0 was a 4-byte DATA stub for 0x10016ea0, which is the function
 * gm_SubObjectNoKill (spiel_dumpD.c).  gv_HireProductionWorker.c and
 * gv_ExtendProductionTime.c called it as a function, so the link resolved
 * those calls to a data address.  Both now call gm_SubObjectNoKill directly.
 * (scripts/gen_link_stubs.py no longer exists; edit by hand.) */
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
// GLOBAL: SERVER 0x1003543c
int g_active_player_count;
/* g_alloc_counter is defined in Units/m_alloc/m_alloc.c (0x10034638). */
char* g_array_base = 0;
int g_console_handle = 0;
/* g_default_group_name / _4 are gone: they are the two dwords of "_main_:" at
 * 0x10028938, now DEFINED in Units/m_alloc/m_alloc.c as the real 8-byte string.
 * Zeroed stubs here put them at 0x100366dc and left the reference's eight bytes
 * missing from .data entirely. */
/* g_next_family_index and gm_CurrentHumanFamilyCount are defined in spiel62.c. */
int g_mem_pool_overflow_flag = 0;
char g_msg_buf[1] ;
int g_object_count = 0;

/* g_query_limit is defined in gm_NextEntityQueryMatch.c. */
short g_record_table[1] ;
char* g_table = 0;
/* vfs_CleanupSubobject, vfs_CompressBlock, vfs_GetErrnoPtr,
 * vfs_StreamClose, vfs_WriteBufferLocked were int-sized data stubs
 * named after functions. Nothing references them. compress_block is
 * static inside references/zlib-1.1.3/trees.c; the other four names
 * were dead prototypes already dropped from the vfs sources. */

/* Eight regular player slots and one admin slot, all with the same record layout. */

/* String literal globals */

/* Special forwarding stubs */
extern int __stdcall ServerMainThread(void*);

/* removed round 1386: unreferenced in the tree, and its body was emitted at
   0x10023850 -- past the reference .text end.  Re-add only with a caller. */

/* LIBCMT fpinit.obj owns _fltused and the floating-point initialization. */

/* --- Auto-added stubs for symbols lost during naked->C conversion --- */
/* GROUP B: game memset/memmove (0x10021240 / 0x1001b200) - stubs until the
 * crt mem TUs are reversed; postlink rewrites call targets to the reference
 * VAs. */
/* 0x10034624 g_array_count and 0x10034640 g_array_ptr are defined in
 * gm_Open.c. 0x10034628..34 g_stat1..4 are defined in m_alloc2.c.
 * 0x10034638 g_alloc_counter is defined in m_alloc.c. */
/* 0x117640a0..c0 are g_alloc_root_* above. 0x117640c4 is g_list_head
 * in srv_LoadBuf.c. */
/* Five seasonal building tables: 0x10-byte header and 0x55 records per table. */
/* Sell msgs: real .data strings (ExSell imm32); overlay GLOBAL on alchemistry_logic2.c */
/* g_player_slots_base removed: ExSell uses g_connections@0x101deb00 */
/* Each entity has one relationship byte for every one of the 0x300 entities. */
int g_sim_ents = 0;
/* g_unknown_1de450 removed round 932: it was a SECOND definition of the same
   address as `char* g_item_def_table` above (line 78), and wrongly typed `int`
   against that `char*`.  Two symbols for one .data address is the naming rule's
   "one word, one meaning" broken, and it is why operands naming it resolved into
   the stub region instead of the attested symbol. */
/* inflate_blocks / inflate_blocks_free are provided by the vendored
 * references/zlib-1.1.3/infblock.c; stubs here would shadow the real ones. */

/* LIBCMT nlsdata2.obj supplies the 32-byte locale BSS block, including
 * six locale handles and the two codepage scalars. It has no dependencies
 * on locale setup functions or additional imports. */

/* Four city records, as traversed by ls_LoadTownData. */
// DATA: SERVER 0x100241a0
unsigned int g_crc_table[256] ;
/* Initialized so these are this file's BSS contribution, not COMMON
 * parked after every other TU.  Reference addresses: g_players_synced
 * 0x11764090, g_next_tick_time 0x101deaf0, g_host_flags 0x101de464,
 * g_module_path 0x101de9a0. */

/* removed round 1385: this stub displaced LIBCMT.lib(fputc.obj) at
   0x10023890; the reference's _putc is the library body. */


void (*g_panic_callback)(void) = 0;

/* Tick rate read from the server ini by ServerMainThread; the binary's
 * initial value is 0 and the profile read overwrites it at startup. */

/* Small-block-heap pool region list, zero-init .data (BSS) in the original. */
/* LIBCMT sbheap.obj owns __sbh_cntHeaderList and __sbh_pHeaderList. */

/* LINK /ORDER places these COMMON globals; large arrays align naturally. */
// GLOBAL: SERVER 0x100358a0
unsigned char g_slot_table[0x300 * 0x21c];
// GLOBAL: SERVER 0x1009aca0
unsigned char g_entity_base[16 * 0xac];
// GLOBAL: SERVER 0x1009b760
unsigned char g_town_records[5 * 0x2a90];
// GLOBAL: SERVER 0x100a8c30
char* g_entity_type_table;
// GLOBAL: SERVER 0x100a8c34
unsigned short* g_query_base;
// GLOBAL: SERVER 0x100a8c38
int g_query_match_count;
// GLOBAL: SERVER 0x100a8c40
unsigned char g_city_records[4 * 0x2f4];
// GLOBAL: SERVER 0x100a9820
char g_relationship_matrix_primary[0x300 * 0x300];
// GLOBAL: SERVER 0x10139820
int g_manufacturer_types[25];
/* Query traversal can retain one pointer for each of the 0x5008 object records. */
// GLOBAL: SERVER 0x101398a0
int g_dispatch_table_b[0x5008];
// GLOBAL: SERVER 0x1014d8c0
unsigned char* g_entity_ptr;
// GLOBAL: SERVER 0x1014d8e0
char g_relationship_matrix_secondary[0x300 * 0x300];
// GLOBAL: SERVER 0x101dd8e0
int g_minimum_manufacturer[732];
// GLOBAL: SERVER 0x101de450
char* g_item_def_table;
// GLOBAL: SERVER 0x101de454
int g_aux_entity_count;
/* Versioned save header: 0x9c fixed bytes followed by a 0x60-byte tail. */
// GLOBAL: SERVER 0x101de460
int g_save_info[63];
// GLOBAL: SERVER 0x101de55c
int g_aux_entity_buffer;
// GLOBAL: SERVER 0x101de560
int g_recv_game_buffer;
/* 42 office records, initialized and traversed at a 24-byte stride. */
/* Save-session state read as one 24-byte block by srv_RecvGame. */
// GLOBAL: SERVER 0x101de580
unsigned char g_save_session_state[24];
// GLOBAL: SERVER 0x101de5a0
char g_office_slots[42 * 24];
// GLOBAL: SERVER 0x101de9a0
char g_module_path[0x104];
#include "Develop/download_state.h"
// GLOBAL: SERVER 0x101deac0
struct DownloadState g_download_state;
// GLOBAL: SERVER 0x101deaec
int g_net_socket;
// GLOBAL: SERVER 0x101deaf0
unsigned int g_next_tick_time;
// GLOBAL: SERVER 0x101deb00
unsigned char g_connections[9 * 0x264264];

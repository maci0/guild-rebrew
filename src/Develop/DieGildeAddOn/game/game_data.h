/* Declarations for game globals used from more than one translation unit.
 * No storage lives here.
 *
 * A definition belongs in exactly one .c file:
 *   - the TU whose link position already covers that address
 *     (spiel_data.c owns g_next_object_id, m_alloc.c owns g_alloc_counter,
 *     alchemistry_logic3.c owns g_game_speed_index);
 *   - otherwise link_stubs.c, which is linked last.  That file holds the
 *     late pool and the writable stand-ins for constants whose bytes
 *     already sit in the .rdata restore blob.  Copying one of those into
 *     an earlier TU puts a named global ahead of that TU's string literals
 *     and shifts the matched .data run.
 *   - a string the reference stores as a literal stays a literal in the
 *     TU that uses it.  A named array in that TU is emitted before the
 *     literals.
 *
 * A file-scope declaration without extern and without an initializer is a
 * tentative definition.  Several of those for one name, or one of them
 * beside the real initializer, is a second symbol.  Use extern here.
 */

#ifndef GAME_DATA_H
#define GAME_DATA_H

extern int g_query_limit; /* 0x10035450, gm_NextEntityQueryMatch.c */
extern int g_next_object_id; /* 0x10030b6c, spiel_data.c */
extern int g_current_year; /* 0x10035880, gm_NextEntityQueryMatch.c */
extern int g_citizen_count; /* 0x10035434, gm_NextEntityQueryMatch.c */
extern unsigned char g_current_season; /* 0x10035439 */

// DATA: SERVER 0x100256cc
extern const float g_const_0_0;
// DATA: SERVER 0x100257c8
extern float g_graveyard_const_c;
// DATA: SERVER 0x100257d0
extern double g_const_half;
// DATA: SERVER 0x10025fa0
extern double g_const_1_over_720;
// DATA: SERVER 0x10025fa8
extern float g_const_896_0;
// DATA: SERVER 0x10025fac
extern float g_const_0_06875;
// DATA: SERVER 0x10025fb0
extern float g_const_2_2;
// DATA: SERVER 0x10025fb4
extern float g_const_1_5;

#endif /* GAME_DATA_H */

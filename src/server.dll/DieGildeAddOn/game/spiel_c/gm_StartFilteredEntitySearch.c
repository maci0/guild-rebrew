/* gm_StartFilteredEntitySearch — sets up a filtered entity search. */

/* RELOC 2026-09-06 (269 -> 296/296). Two coupled changes to the 9-global setup
 * block closed the last gap:
 *   - `g_filter_extra5` and `g_query_filter_extra4` declared `unsigned char`
 *     (matching spiel_dumpD.c) and stored as plain `0xff`. With `char` and a
 *     `(char) 0xff` cast msvc6 emits two 7-byte immediate stores; unsigned lets
 *     it common the constant into a register, which is what the target does.
 *   - the `g_filter_extra5` store written FIRST, ahead of the two 0x7fff word
 *     stores. That ordering makes msvc6 hoist `mov cl,0xff` above the word
 *     stores and frees ecx from the zero role, so the zero lands in edx and is
 *     reused for the null-check `cmp` and the three zero stores, exactly as the
 *     reference does at 0x100170e5.
 * The two levers only work together: unsigned globals alone (extra5 store left
 * in its old slot) score 125/296 and drop to STUB, because the CSE happens but
 * the zero stays in ecx and the whole block shifts.
 *
 * Earlier steps, kept for the record:
 *   - 241 -> 262: case 2 advances arg_ptr *before* the strcpy, matching the
 *     target's `mov edi,[edx+4]; add edx,4` at 0x10017173.
 *   - 262 -> 269: dropping the `src` local and passing the post-increment slot
 *     straight to strcpy. The local delayed `add edx,4` by one slot.
 *
 * Dead ends measured before the fix, all at the old `char` declarations:
 * hoisting the constants into locals (`char ff = 0xff`, `int zero = 0`, either
 * or both, int/unsigned char/volatile/register spellings), chained assignment
 * across the ff or 0x7fff pair (237), reading one global back from the other
 * (241), every ff literal spelling (255/241), a zero local feeding the null
 * test and all three zero stores (241), eight permutations of the nine store
 * statements (231-238), volatile on the setup globals (260/249/223), and the
 * /O1 /Ox /Og /Oy and #pragma optimize sweeps. Using memcpy as a strcpy
 * stand-in is not equivalent and must not be used: 176/296 and STUB. */
#include <string.h>

// FUNCTION: SERVER 0x100170e0

#pragma intrinsic(memcpy, memset, strcpy)

extern char* g_entity_type_table; /* 0x100a8c30 */
extern unsigned char* g_entity_ptr; /* 0x1014d8c0 */
extern unsigned char* g_query_filter_base; /* 0x10035464 */
extern short g_query_filter_extra2; /* 0x10030b8c */
extern short g_query_filter_extra3; /* 0x10030b8e */
extern unsigned char g_filter_extra5; /* 0x10030b84 */
extern int g_query_filter_extra1; /* 0x10030b88 */
extern unsigned char g_query_filter_extra4; /* 0x10030b90 */
extern char* g_dynasty_field_44; /* 0x10035444 */
extern char g_dynasty_field_49; /* 0x10035449 */
extern int g_dynasty_field_4c; /* 0x1003544c */
extern char g_dynasty_field_48; /* 0x10035448 */

void* __cdecl FindNextFilteredEntity(void);

/* Initializes the filter state from a list of (type, value) vararg pairs.
 * Type 0 = extra5 (byte), 1 = extra1 (int), 2 = dynasty string copy,
 * 3 = extra2 (short), 4 = extra3 (short), 5 = extra4 (byte), 6 = field_48.
 * Returns the first filtered entity. */
unsigned short* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...)
{
	int* arg_ptr;
	int i;

	if (g_entity_type_table == 0) {
		return (unsigned short*) 0;
	}

	g_filter_extra5 = 0xff;
	g_query_filter_extra2 = 0x7fff;
	g_query_filter_extra3 = 0x7fff;
	g_query_filter_extra1 = -1;
	g_dynasty_field_44 = 0;
	g_query_filter_extra4 = 0xff;
	g_dynasty_field_49 = 1;
	g_dynasty_field_4c = 0;
	g_dynasty_field_48 = 0;

	if (arg_count > 0) {
		arg_ptr = &arg_count;

		for (i = arg_count; i > 0; i--) {
			unsigned char ftype;

			arg_ptr++;
			ftype = *(unsigned char*) arg_ptr;
			switch (ftype) {
			case 0:
				g_filter_extra5 = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 1:
				g_query_filter_extra1 = *(arg_ptr + 1);
				arg_ptr++;
				break;
			case 2:
				arg_ptr++;
				strcpy(g_dynasty_field_44, *(char**) arg_ptr);
				break;
			case 3:
				g_query_filter_extra2 = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 4:
				g_query_filter_extra3 = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 5:
				g_query_filter_extra4 = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 6:
				g_dynasty_field_48 = 1;
				break;
			default:
				break;
			}
		}
	}

	g_query_filter_base = g_entity_ptr;
	return (unsigned short*) FindNextFilteredEntity();
}

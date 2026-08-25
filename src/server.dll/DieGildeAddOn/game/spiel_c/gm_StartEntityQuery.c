/* gm_StartEntityQuery — sets up an entity query from a vararg filter list. */

/* NOTE: structure is faithful to the reference (loop, switch, flag dispatch,
 * shared query tail all match), but the entry allocation cannot be reproduced
 * byte-for-byte: the reference parks the zero in eax (table load in ecx,
 * count stores via eax-moffs, esi pushed only around the loop); MSVC 6.0
 * insists on loading the table into eax and parking the zero in esi whenever
 * the check_container tail is present (see docs/msvc6-allocator.md
 * "Finding 1/2"). Best effort: 151/316 bytes. */

// FUNCTION: SERVER 0x10016460

#include "../../../Units/Error/error.h"

#include <stddef.h>

extern char* g_item_def_table; /* 0x101de450 */
extern int g_query_filter_max_id; /* 0x10030b94 */
extern int g_query_filter_owner; /* 0x10030b98 */
extern short g_query_filter_type; /* 0x10030b9c */
extern char g_query_filter_state; /* 0x10030b9e */
extern char g_query_flag1; /* 0x1003545c */
extern char g_query_flag2; /* 0x1003545d */
extern char g_query_flag3; /* 0x1003545e */
extern char g_query_active; /* 0x10035454 */
extern int g_query_count; /* 0x10035458 */
extern int g_query_match_count; /* 0x100a8c38 */
extern unsigned short* g_query_cursor; /* 0x10035468 */
extern unsigned short* g_query_base; /* 0x100a8c34 */

void* __cdecl gm_NextEntityQueryMatch(void);

/* Initializes the query state from a list of (type, value) vararg pairs.
 * Type 0 = max id (word), 1 = owner (int), 3 = type (word), 4 = state
 * (byte), 5 = flag3, 6 = flag2, 7 = flag1. When flag1 is set the cursor
 * starts at the global query base; otherwise the container id is used.
 * Returns the first match, or NULL when no container id was given. */
unsigned short* __cdecl gm_StartEntityQuery(int container_id, int arg_count, int first_arg, ...)
{
	int* arg_ptr;
	int i;
	unsigned char flag1;
	unsigned char flag2;

	if (g_item_def_table == 0) {
		return (unsigned short*) 0;
	}

	flag1 = 0;
	flag2 = 0;

	g_query_filter_max_id = 0x7fff;
	g_query_filter_owner = -1;
	g_query_filter_type = (short) 0xffff;
	g_query_filter_state = (char) 0xff;
	g_query_flag3 = 0;
	g_query_flag1 = flag1;
	g_query_flag2 = flag2;
	g_query_active = 1;
	g_query_count = 0;
	g_query_match_count = 0;

	if (arg_count > 0) {
		arg_ptr = &arg_count;
		i = arg_count;

		do {
			arg_ptr++;
			switch (*(unsigned char*) arg_ptr) {
			case 0:
				arg_ptr++;
				g_query_filter_max_id = *(unsigned short*) arg_ptr;
				break;
			case 1:
				g_query_filter_owner = *(arg_ptr + 1);
				arg_ptr++;
				break;
			case 2:
				break;
			case 3:
				g_query_filter_type = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 4:
				g_query_filter_state = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 5:
				g_query_flag3 = 1;
				break;
			case 6:
				flag2 = 1;
				break;
			case 7:
				flag1 = 1;
				break;
			}
			i--;
		} while (i != 0);

		g_query_flag1 = flag1;
		g_query_flag2 = flag2;

		if (flag1 != 0) {
			container_id = (int) g_query_base;
			if (flag2 != 0) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xb66, "gm_ff_Objekt: Invalid Combination of Flags", 1);
				return (unsigned short*) 0;
			}
			goto query_tail;
		}
	}

	if (container_id == 0) {
		return (unsigned short*) container_id;
	}

query_tail:
	g_query_cursor = (unsigned short*) container_id;
	return gm_NextEntityQueryMatch();
}

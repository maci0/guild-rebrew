/* gm_ff_Objekt — sets up an entity query from a vararg filter list. */

/* NOTE: the entry allocation is order-sensitive. Each flag must be zeroed
 * immediately before its own global store (flag1/g_query_flag1, then
 * flag2/g_query_flag2), after the filter stores; that keeps flag1 in dl and
 * flag2 in bl. Zeroing both flags up front commons the value into bl and
 * costs the g_query_flag3/g_query_flag1 stores. The -1 filter values are
 * written as unsigned literals into unsigned globals so MSVC 6.0 emits
 * immediate stores instead of commoning -1 into a register. */

// FUNCTION: SERVER 0x10016460

#include "../../../Units/Error/error.h"

#include <stddef.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

extern int g_query_filter_max_id; /* 0x10030b94 */
extern int g_query_filter_owner; /* 0x10030b98 */
extern unsigned short g_query_filter_type; /* 0x10030b9c */

void* __cdecl gm_NextEntityQueryMatch(void);

/* Initializes the query state from a list of (type, value) vararg pairs.
 * Type 0 = max id (word), 1 = owner (int), 3 = type (word), 4 = state
 * (byte), 5 = flag3, 6 = flag2, 7 = flag1. When flag1 is set the cursor
 * starts at the global query base; otherwise the container id is used.
 * Returns the first match, or NULL when no container id was given. */
unsigned short* __cdecl gm_ff_Objekt(int container_id, int arg_count, int first_arg, ...)
{
	int* arg_ptr;
	int i;
	unsigned char flag1;
	unsigned char flag2;

	if (g_item_def_table == 0) {
		return (unsigned short*) 0;
	}

	g_query_filter_max_id = 0x7fff;
	g_query_filter_owner = 0xffffffff;
	g_query_filter_type = 0xffff;
	g_query_filter_state = 0xff;
	g_query_flag3 = 0;

	flag1 = 0;
	g_query_flag1 = flag1;
	flag2 = 0;
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
			if (flag2 != 0) {
				LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0xb66, "gm_ff_Objekt: Invalid Combination of Flags", 1);
				return (unsigned short*) 0;
			}
			container_id = (int) g_query_base;
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

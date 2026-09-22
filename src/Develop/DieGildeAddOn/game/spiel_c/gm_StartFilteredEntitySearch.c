#include <string.h>
#include "rebrew_types.h"
#include "rebrew_globals.h"

// FUNCTION: GOLDTL 0x503fe0
// SIZE: 288
// FUNCTION: SERVER 0x100170e0

#pragma intrinsic(memcpy, memset, strcpy)

extern unsigned char* g_query_filter_base; /* 0x10035464 */
extern short g_query_filter_extra2; /* 0x10030b8c */
extern short g_query_filter_extra3; /* 0x10030b8e */
extern unsigned char g_filter_extra5; /* 0x10030b84 */
extern int g_query_filter_extra1; /* 0x10030b88 */
extern unsigned char g_query_filter_extra4; /* 0x10030b90 */
extern int g_dynasty_field_44; /* 0x10035444 */
extern char g_dynasty_field_49; /* 0x10035449 */
extern int g_dynasty_field_4c; /* 0x1003544c */
extern char g_dynasty_field_48; /* 0x10035448 */

void* __cdecl gm_FindNextFilteredEntity(void);

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
				strcpy((char*) g_dynasty_field_44, *(char**) arg_ptr);
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
	return (unsigned short*) gm_FindNextFilteredEntity();
}


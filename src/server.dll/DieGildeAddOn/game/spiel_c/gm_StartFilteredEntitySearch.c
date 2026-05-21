#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
typedef int(__cdecl* ALLOCFN)(int, int, int);

#pragma intrinsic(memcpy, memset)

// SIZE 0x2c
typedef struct {
	char pad[0x24];
	int(__cdecl* func)(int, int);
	int field_28;
} DISPATCH_OBJ;

#pragma pack(push, 1)
// SIZE 0x43
typedef struct {
	short active;
	int id;
	char pad[0x3d];
} Record;
#pragma pack(pop)

extern char* g_entity_table; /* 0x101de450 */
;
extern unsigned char* g_entity_ptr;
extern int g_entity_type_table;
void* __cdecl FindNextFilteredEntity(void);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
extern short g_query_filter_extra2;
extern short g_query_filter_extra3;
extern char g_filter_extra5;
extern int g_query_filter_extra1;
extern char g_query_filter_extra4;
extern char* g_dynasty_field_44;
extern char g_dynasty_field_49;
extern int g_dynasty_field_4c;
extern char g_dynasty_field_48;
extern unsigned char* g_query_filter_base;

// FUNCTION: SERVER 0x100170e0
// gm_StartFilteredEntitySearch

unsigned short* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...)
{
	int* arg_ptr;
	int i;

	if (g_entity_type_table == 0) {
		return (unsigned short*) 0;
	}

	g_query_filter_extra2 = 0x7fff;
	g_query_filter_extra3 = 0x7fff;
	g_filter_extra5 = (char) 0xff;
	g_query_filter_extra1 = -1;
	g_query_filter_extra4 = (char) 0xff;
	g_dynasty_field_44 = 0;
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
				strcpy(g_dynasty_field_44, *(char**) (arg_ptr + 1));
				arg_ptr++;
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

/* Searches a structure/record table for a matching entry.
 * Linear search by comparison field. */

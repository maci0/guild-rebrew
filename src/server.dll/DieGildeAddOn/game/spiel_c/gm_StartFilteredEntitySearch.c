#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <string.h>
typedef int(__cdecl* ALLOCFN)(int, int, int);

#pragma intrinsic(memcpy, memset)

// SIZE 0x2c
#pragma pack(push, 1)
// SIZE 0x43
typedef struct {
	short active;
	int id;
	char pad[0x3d];
} Record;
#pragma pack(pop)

extern char* g_entity_table; /* 0x101de450 */
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

#ifdef REBREW_ALLOW_NAKED
__declspec(naked) unsigned short* __cdecl gm_StartFilteredEntitySearch(int arg_count, ...)
{
	__asm {
		_emit 0xa1
		_emit 0x30
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		_emit 0x33
		_emit 0xd2
		_emit 0x3b
		_emit 0xc2
		_emit 0x75
		_emit 0x03
		_emit 0x33
		_emit 0xc0
		_emit 0xc3
		_emit 0xb8
		_emit 0xff
		_emit 0x7f
		_emit 0x00
		_emit 0x00
		_emit 0xb1
		_emit 0xff
		_emit 0x66
		_emit 0xa3
		_emit 0x8c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0x66
		_emit 0xa3
		_emit 0x8e
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0x8b
		_emit 0x44
		_emit 0x24
		_emit 0x04
		_emit 0x88
		_emit 0x0d
		_emit 0x84
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0x3b
		_emit 0xc2
		_emit 0xc7
		_emit 0x05
		_emit 0x88
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xff
		_emit 0xff
		_emit 0xff
		_emit 0xff
		_emit 0x89
		_emit 0x15
		_emit 0x44
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x88
		_emit 0x0d
		_emit 0x90
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xc6
		_emit 0x05
		_emit 0x49
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x01
		_emit 0x89
		_emit 0x15
		_emit 0x4c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x88
		_emit 0x15
		_emit 0x48
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x0f
		_emit 0x8e
		_emit 0x9e
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0x55
		_emit 0x56
		_emit 0x57
		_emit 0x8d
		_emit 0x54
		_emit 0x24
		_emit 0x10
		_emit 0x8b
		_emit 0xe8
		_emit 0x83
		_emit 0xc2
		_emit 0x04
		_emit 0x33
		_emit 0xc0
		_emit 0x8a
		_emit 0x02
		_emit 0x83
		_emit 0xf8
		_emit 0x06
		_emit 0x77
		_emit 0x7f
		_emit 0xff
		_emit 0x24
		_emit 0x85
		_emit 0xec
		_emit 0x71
		_emit 0x01
		_emit 0x10
		_emit 0x8a
		_emit 0x42
		_emit 0x04
		_emit 0x83
		_emit 0xc2
		_emit 0x04
		_emit 0xa2
		_emit 0x84
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xeb
		_emit 0x6b
		_emit 0x8b
		_emit 0x4a
		_emit 0x04
		_emit 0x83
		_emit 0xc2
		_emit 0x04
		_emit 0x89
		_emit 0x0d
		_emit 0x88
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xeb
		_emit 0x5d
		_emit 0x8b
		_emit 0x7a
		_emit 0x04
		_emit 0x83
		_emit 0xc2
		_emit 0x04
		_emit 0x83
		_emit 0xc9
		_emit 0xff
		_emit 0x33
		_emit 0xc0
		_emit 0xf2
		_emit 0xae
		_emit 0xf7
		_emit 0xd1
		_emit 0x2b
		_emit 0xf9
		_emit 0x8b
		_emit 0xc1
		_emit 0x8b
		_emit 0xf7
		_emit 0x8b
		_emit 0x3d
		_emit 0x44
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0xc1
		_emit 0xe9
		_emit 0x02
		_emit 0xf3
		_emit 0xa5
		_emit 0x8b
		_emit 0xc8
		_emit 0x83
		_emit 0xe1
		_emit 0x03
		_emit 0xf3
		_emit 0xa4
		_emit 0xeb
		_emit 0x34
		_emit 0x66
		_emit 0x8b
		_emit 0x4a
		_emit 0x04
		_emit 0x83
		_emit 0xc2
		_emit 0x04
		_emit 0x66
		_emit 0x89
		_emit 0x0d
		_emit 0x8c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xeb
		_emit 0x24
		_emit 0x66
		_emit 0x8b
		_emit 0x42
		_emit 0x04
		_emit 0x83
		_emit 0xc2
		_emit 0x04
		_emit 0x66
		_emit 0xa3
		_emit 0x8e
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xeb
		_emit 0x15
		_emit 0x8a
		_emit 0x4a
		_emit 0x04
		_emit 0x83
		_emit 0xc2
		_emit 0x04
		_emit 0x88
		_emit 0x0d
		_emit 0x90
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xeb
		_emit 0x07
		_emit 0xc6
		_emit 0x05
		_emit 0x48
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x01
		_emit 0x4d
		_emit 0x0f
		_emit 0x85
		_emit 0x6e
		_emit 0xff
		_emit 0xff
		_emit 0xff
		_emit 0x5f
		_emit 0x5e
		_emit 0x5d
		_emit 0x8b
		_emit 0x15
		_emit 0xc0
		_emit 0xd8
		_emit 0x14
		_emit 0x10
		_emit 0x89
		_emit 0x15
		_emit 0x64
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0xe9
		_emit 0x95
		_emit 0xfd
		_emit 0xff
		_emit 0xff
		_emit 0x90
		_emit 0x58
		_emit 0x71
		_emit 0x01
		_emit 0x10
		_emit 0x65
		_emit 0x71
		_emit 0x01
		_emit 0x10
		_emit 0x73
		_emit 0x71
		_emit 0x01
		_emit 0x10
		_emit 0x9c
		_emit 0x71
		_emit 0x01
		_emit 0x10
		_emit 0xac
		_emit 0x71
		_emit 0x01
		_emit 0x10
		_emit 0xbb
		_emit 0x71
		_emit 0x01
		_emit 0x10
		_emit 0xc9
		_emit 0x71
		_emit 0x01
		_emit 0x10
	}
}
#else
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
	g_dynasty_field_44 = 0;
	g_query_filter_extra4 = (char) 0xff;
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
#endif

/* Searches a structure/record table for a matching entry.
 * Linear search by comparison field. */
unsigned char g_entity_end;
unsigned int g_1009b764;
char* g_slot_array;
unsigned char g_entity_base;
int g_some_limit;

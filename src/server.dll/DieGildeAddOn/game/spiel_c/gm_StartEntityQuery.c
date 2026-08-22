// FUNCTION: SERVER 0x10016460
#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <stdlib.h>
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
extern unsigned short* g_query_base;
extern char* g_item_def_table;
void* __cdecl gm_NextEntityQueryMatch(void);
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
extern unsigned short* g_query_cursor;
extern char g_query_active;
extern char g_query_flag2;
extern int g_query_count;
extern int g_query_filter_max_id;
extern int g_query_filter_owner;
extern short g_query_filter_type;
extern char g_query_filter_state;
extern char g_query_flag1;
extern char g_query_flag3;
extern int g_query_match_count;


#ifdef REBREW_ALLOW_NAKED
__declspec(naked) unsigned short* __cdecl gm_StartEntityQuery(int container_id, int arg_count, int first_arg, ...)
{
	__asm {
		_emit 0x8b
		_emit 0x0d
		_emit 0x50
		_emit 0xe4
		_emit 0x1d
		_emit 0x10
		_emit 0x33
		_emit 0xc0
		_emit 0x3b
		_emit 0xc8
		_emit 0x53
		_emit 0x75
		_emit 0x02
		_emit 0x5b
		_emit 0xc3
		_emit 0x8b
		_emit 0x4c
		_emit 0x24
		_emit 0x0c
		_emit 0x32
		_emit 0xd2
		_emit 0x32
		_emit 0xdb
		_emit 0x3b
		_emit 0xc8
		_emit 0xc7
		_emit 0x05
		_emit 0x94
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xff
		_emit 0x7f
		_emit 0x00
		_emit 0x00
		_emit 0xc7
		_emit 0x05
		_emit 0x98
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xff
		_emit 0xff
		_emit 0xff
		_emit 0xff
		_emit 0x66
		_emit 0xc7
		_emit 0x05
		_emit 0x9c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xff
		_emit 0xff
		_emit 0xc6
		_emit 0x05
		_emit 0x9e
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xff
		_emit 0xc6
		_emit 0x05
		_emit 0x5e
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x00
		_emit 0x88
		_emit 0x15
		_emit 0x5c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x88
		_emit 0x1d
		_emit 0x5d
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0xc6
		_emit 0x05
		_emit 0x54
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x01
		_emit 0xa3
		_emit 0x58
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0xa3
		_emit 0x38
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		_emit 0x0f
		_emit 0x8e
		_emit 0xab
		_emit 0x00
		_emit 0x00
		_emit 0x00
		_emit 0x56
		_emit 0x8d
		_emit 0x44
		_emit 0x24
		_emit 0x10
		_emit 0x8b
		_emit 0xf1
		_emit 0x83
		_emit 0xc0
		_emit 0x04
		_emit 0x33
		_emit 0xc9
		_emit 0x8a
		_emit 0x08
		_emit 0x83
		_emit 0xf9
		_emit 0x07
		_emit 0x77
		_emit 0x52
		_emit 0xff
		_emit 0x24
		_emit 0x8d
		_emit 0x7c
		_emit 0x65
		_emit 0x01
		_emit 0x10
		_emit 0x83
		_emit 0xc0
		_emit 0x04
		_emit 0x33
		_emit 0xc9
		_emit 0x66
		_emit 0x8b
		_emit 0x08
		_emit 0x89
		_emit 0x0d
		_emit 0x94
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xeb
		_emit 0x3b
		_emit 0x8b
		_emit 0x48
		_emit 0x04
		_emit 0x83
		_emit 0xc0
		_emit 0x04
		_emit 0x89
		_emit 0x0d
		_emit 0x98
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xeb
		_emit 0x2d
		_emit 0x66
		_emit 0x8b
		_emit 0x48
		_emit 0x04
		_emit 0x83
		_emit 0xc0
		_emit 0x04
		_emit 0x66
		_emit 0x89
		_emit 0x0d
		_emit 0x9c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xeb
		_emit 0x1d
		_emit 0x8a
		_emit 0x48
		_emit 0x04
		_emit 0x83
		_emit 0xc0
		_emit 0x04
		_emit 0x88
		_emit 0x0d
		_emit 0x9e
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		_emit 0xeb
		_emit 0x0f
		_emit 0xc6
		_emit 0x05
		_emit 0x5e
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x01
		_emit 0xeb
		_emit 0x06
		_emit 0xb3
		_emit 0x01
		_emit 0xeb
		_emit 0x02
		_emit 0xb2
		_emit 0x01
		_emit 0x4e
		_emit 0x75
		_emit 0x9f
		_emit 0x84
		_emit 0xd2
		_emit 0x88
		_emit 0x15
		_emit 0x5c
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x88
		_emit 0x1d
		_emit 0x5d
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0x5e
		_emit 0x74
		_emit 0x32
		_emit 0x84
		_emit 0xdb
		_emit 0x74
		_emit 0x1d
		_emit 0x6a
		_emit 0x01
		_emit 0x68
		_emit 0x50
		_emit 0x12
		_emit 0x03
		_emit 0x10
		_emit 0x68
		_emit 0x66
		_emit 0x0b
		_emit 0x00
		_emit 0x00
		_emit 0x68
		_emit 0x04
		_emit 0x10
		_emit 0x03
		_emit 0x10
		_emit 0xe8
		_emit 0xe6
		_emit 0xd0
		_emit 0xfe
		_emit 0xff
		_emit 0x83
		_emit 0xc4
		_emit 0x10
		_emit 0x33
		_emit 0xc0
		_emit 0x5b
		_emit 0xc3
		_emit 0xa1
		_emit 0x34
		_emit 0x8c
		_emit 0x0a
		_emit 0x10
		_emit 0xa3
		_emit 0x68
		_emit 0x54
		_emit 0x03
		_emit 0x10
		_emit 0xe8
		_emit 0x20
		_emit 0xfd
		_emit 0xff
		_emit 0xff
		_emit 0x5b
		_emit 0xc3
		_emit 0x8b
		_emit 0x44
		_emit 0x24
		_emit 0x08
		_emit 0x85
		_emit 0xc0
		_emit 0x75
		_emit 0xec
		_emit 0x5b
		_emit 0xc3
		_emit 0xe1
		_emit 0x64
		_emit 0x01
		_emit 0x10
		_emit 0xf1
		_emit 0x64
		_emit 0x01
		_emit 0x10
		_emit 0x2c
		_emit 0x65
		_emit 0x01
		_emit 0x10
		_emit 0xff
		_emit 0x64
		_emit 0x01
		_emit 0x10
		_emit 0x0f
		_emit 0x65
		_emit 0x01
		_emit 0x10
		_emit 0x1d
		_emit 0x65
		_emit 0x01
		_emit 0x10
		_emit 0x26
		_emit 0x65
		_emit 0x01
		_emit 0x10
		_emit 0x2a
		_emit 0x65
		_emit 0x01
		_emit 0x10
		_emit 0x90
		_emit 0x90
		_emit 0x90
		_emit 0x90
	}
}
#else
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
		arg_ptr = &first_arg;

		for (i = arg_count; i > 0; i--) {
			unsigned char ftype;

			ftype = *(unsigned char*) arg_ptr;
			switch (ftype) {
			case 0:
				arg_ptr++;
				g_query_filter_max_id = *(unsigned short*) arg_ptr;
				break;
			case 1:
				g_query_filter_owner = *(arg_ptr + 1);
				arg_ptr++;
				break;
			case 2:
				g_query_filter_type = *(short*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 3:
				g_query_filter_state = *(char*) (arg_ptr + 1);
				arg_ptr++;
				break;
			case 4:
				g_query_flag3 = 1;
				break;
			case 5:
				flag2 = 1;
				break;
			case 6:
				flag1 = 1;
				break;
			case 7:
				break;
			}
		}

		g_query_flag1 = flag1;
		g_query_flag2 = flag2;

		if (flag1 == 0) {
			goto check_container;
		}

		if (flag2 != 0) {
			LogMessageInternal("D:\\Develop\\DieGildeAddOn\\objekte", 0xb66, "query flags conflict", 1);
			return (unsigned short*) 0;
		}

		g_query_cursor = g_query_base;
		return gm_NextEntityQueryMatch();
	}

check_container:
	if (container_id != 0) {
		g_query_cursor = g_query_base;
		return gm_NextEntityQueryMatch();
	}

	return (unsigned short*) 0;
}
#endif

/* Allocates an object slot in an entity's inventory.
 * Finds the next free slot and returns its index. */
unsigned int g_player_slot_overflow;

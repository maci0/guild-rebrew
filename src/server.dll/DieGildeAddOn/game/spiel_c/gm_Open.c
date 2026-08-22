#include "../../../Units/Error/error.h"
#include "../../../Units/m_alloc/m_alloc.h"

#include <stdio.h>
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
void __cdecl gm_InitObjektHersteller(void);
void __cdecl gm_InitEntitySlots(void);
int __cdecl _getpid(void);
extern int g_entity_type_table;
extern char* g_item_def_table;
extern int g_1014d8c0;
extern int g_100a8c34;
extern int g_100a8cf8;
extern int g_1009b764;
extern int g_1002dde0;

#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original/Server/server.dll 0x10015950 (861B)
__declspec(naked) int __cdecl gm_Open(int map_id)
{
    __asm {
        _emit 0x81
        _emit 0xec
        _emit 0x08
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x53
        _emit 0x56
        _emit 0x57
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x18
        _emit 0x12
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0xd3
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x04
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0xd1
        _emit 0xdc
        _emit 0xfe
        _emit 0xff
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x04
        _emit 0x12
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0xd6
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x04
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0xbb
        _emit 0xdc
        _emit 0xfe
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x20
        _emit 0xba
        _emit 0xf8
        _emit 0x8c
        _emit 0x0a
        _emit 0x10
        _emit 0xb8
        _emit 0x64
        _emit 0xb7
        _emit 0x09
        _emit 0x10
        _emit 0xbb
        _emit 0xe8
        _emit 0x03
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0x4a
        _emit 0xb0
        _emit 0x8d
        _emit 0x78
        _emit 0x0c
        _emit 0x89
        _emit 0x48
        _emit 0xfc
        _emit 0x8b
        _emit 0x0a
        _emit 0x89
        _emit 0x18
        _emit 0x89
        _emit 0x48
        _emit 0x04
        _emit 0x89
        _emit 0x58
        _emit 0x08
        _emit 0x81
        _emit 0xc2
        _emit 0xf4
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xb9
        _emit 0xa0
        _emit 0x0a
        _emit 0x00
        _emit 0x00
        _emit 0xbe
        _emit 0xe0
        _emit 0xdd
        _emit 0x02
        _emit 0x10
        _emit 0x05
        _emit 0x90
        _emit 0x2a
        _emit 0x00
        _emit 0x00
        _emit 0x81
        _emit 0xfa
        _emit 0xbc
        _emit 0x9b
        _emit 0x0a
        _emit 0x10
        _emit 0xf3
        _emit 0xa5
        _emit 0x7c
        _emit 0xce
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0xf0
        _emit 0x11
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0xe3
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x04
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0x61
        _emit 0xdc
        _emit 0xfe
        _emit 0xff
        _emit 0x68
        _emit 0xd8
        _emit 0x11
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0x78
        _emit 0xca
        _emit 0x00
        _emit 0x00
        _emit 0xe8
        _emit 0x92
        _emit 0x0b
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x18
        _emit 0xa3
        _emit 0x30
        _emit 0x8c
        _emit 0x0a
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x26
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0xb8
        _emit 0x11
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0xe8
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x04
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0x30
        _emit 0xdc
        _emit 0xfe
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x83
        _emit 0xc8
        _emit 0xff
        _emit 0x5f
        _emit 0x5e
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0x08
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xc3
        _emit 0x68
        _emit 0xa0
        _emit 0x11
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0x00
        _emit 0xa9
        _emit 0x00
        _emit 0x00
        _emit 0xe8
        _emit 0x51
        _emit 0x0b
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0xf8
        _emit 0xb9
        _emit 0x40
        _emit 0x2a
        _emit 0x00
        _emit 0x00
        _emit 0x33
        _emit 0xc0
        _emit 0x89
        _emit 0x3d
        _emit 0xc0
        _emit 0xd8
        _emit 0x14
        _emit 0x10
        _emit 0xf3
        _emit 0xab
        _emit 0xa1
        _emit 0xc0
        _emit 0xd8
        _emit 0x14
        _emit 0x10
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x0f
        _emit 0x5f
        _emit 0x5e
        _emit 0xb8
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0x08
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xc3
        _emit 0x8b
        _emit 0x9c
        _emit 0x24
        _emit 0x18
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x94
        _emit 0x11
        _emit 0x03
        _emit 0x10
        _emit 0x53
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x1c
        _emit 0x68
        _emit 0x8c
        _emit 0x11
        _emit 0x03
        _emit 0x10
        _emit 0x52
        _emit 0xe8
        _emit 0x22
        _emit 0x48
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x24
        _emit 0x68
        _emit 0x4c
        _emit 0x94
        _emit 0x02
        _emit 0x10
        _emit 0x50
        _emit 0xe8
        _emit 0x00
        _emit 0x48
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xf0
        _emit 0x83
        _emit 0xc4
        _emit 0x18
        _emit 0x85
        _emit 0xf6
        _emit 0x75
        _emit 0x28
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x54
        _emit 0x11
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0xf5
        _emit 0x04
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x04
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0x9b
        _emit 0xdb
        _emit 0xfe
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xb8
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x5f
        _emit 0x5e
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0x08
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xc3
        _emit 0x8b
        _emit 0x0d
        _emit 0x30
        _emit 0x8c
        _emit 0x0a
        _emit 0x10
        _emit 0x56
        _emit 0x6a
        _emit 0x58
        _emit 0x68
        _emit 0x4d
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x51
        _emit 0xe8
        _emit 0x9f
        _emit 0x4f
        _emit 0x00
        _emit 0x00
        _emit 0x56
        _emit 0xe8
        _emit 0xb9
        _emit 0x46
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x40
        _emit 0x11
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0xdc
        _emit 0xb9
        _emit 0x00
        _emit 0x00
        _emit 0xe8
        _emit 0xa0
        _emit 0x0a
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x1c
        _emit 0xa3
        _emit 0x50
        _emit 0xe4
        _emit 0x1d
        _emit 0x10
        _emit 0x85
        _emit 0xc0
        _emit 0x75
        _emit 0x0f
        _emit 0x5f
        _emit 0x5e
        _emit 0xb8
        _emit 0xfc
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0x08
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xc3
        _emit 0x68
        _emit 0x2c
        _emit 0x11
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0x18
        _emit 0xf2
        _emit 0x14
        _emit 0x00
        _emit 0xe8
        _emit 0x76
        _emit 0x0a
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0xf8
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x85
        _emit 0xff
        _emit 0x89
        _emit 0x3d
        _emit 0x34
        _emit 0x8c
        _emit 0x0a
        _emit 0x10
        _emit 0x75
        _emit 0x0f
        _emit 0x5f
        _emit 0x5e
        _emit 0xb8
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0x08
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xc3
        _emit 0x68
        _emit 0x20
        _emit 0x11
        _emit 0x03
        _emit 0x10
        _emit 0xb9
        _emit 0x86
        _emit 0x3c
        _emit 0x05
        _emit 0x00
        _emit 0x33
        _emit 0xc0
        _emit 0x53
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x1c
        _emit 0x68
        _emit 0x8c
        _emit 0x11
        _emit 0x03
        _emit 0x10
        _emit 0xf3
        _emit 0xab
        _emit 0x52
        _emit 0xe8
        _emit 0x53
        _emit 0x47
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x24
        _emit 0x68
        _emit 0x4c
        _emit 0x94
        _emit 0x02
        _emit 0x10
        _emit 0x50
        _emit 0xe8
        _emit 0x31
        _emit 0x47
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xf0
        _emit 0x83
        _emit 0xc4
        _emit 0x18
        _emit 0x85
        _emit 0xf6
        _emit 0x75
        _emit 0x28
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0xe8
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0x2d
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x04
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0xcc
        _emit 0xda
        _emit 0xfe
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xb8
        _emit 0xfa
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0x5f
        _emit 0x5e
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0x08
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xc3
        _emit 0x8b
        _emit 0x0d
        _emit 0x50
        _emit 0xe4
        _emit 0x1d
        _emit 0x10
        _emit 0x55
        _emit 0x56
        _emit 0x68
        _emit 0xdc
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x41
        _emit 0x51
        _emit 0xe8
        _emit 0xcf
        _emit 0x4e
        _emit 0x00
        _emit 0x00
        _emit 0x56
        _emit 0xe8
        _emit 0xe9
        _emit 0x45
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0xc4
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0x36
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x04
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0x89
        _emit 0xda
        _emit 0xfe
        _emit 0xff
        _emit 0xe8
        _emit 0x04
        _emit 0xfb
        _emit 0xff
        _emit 0xff
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0xa4
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0x3a
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x04
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0x6e
        _emit 0xda
        _emit 0xfe
        _emit 0xff
        _emit 0xe8
        _emit 0xf9
        _emit 0x24
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x64
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0x3e
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x04
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0x53
        _emit 0xda
        _emit 0xfe
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x44
        _emit 0x33
        _emit 0xf6
        _emit 0x8b
        _emit 0x15
        _emit 0x30
        _emit 0x8c
        _emit 0x0a
        _emit 0x10
        _emit 0x8b
        _emit 0x2d
        _emit 0x50
        _emit 0xe4
        _emit 0x1d
        _emit 0x10
        _emit 0xc7
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xc7
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x40
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x7c
        _emit 0x16
        _emit 0x23
        _emit 0x66
        _emit 0x8b
        _emit 0x17
        _emit 0x66
        _emit 0x81
        _emit 0xfa
        _emit 0xff
        _emit 0xff
        _emit 0x74
        _emit 0x30
        _emit 0x8b
        _emit 0xc2
        _emit 0x8b
        _emit 0xdd
        _emit 0x25
        _emit 0xff
        _emit 0x7f
        _emit 0x00
        _emit 0x00
        _emit 0x8b
        _emit 0xc8
        _emit 0xc1
        _emit 0xe1
        _emit 0x06
        _emit 0x03
        _emit 0xd9
        _emit 0x8b
        _emit 0xc8
        _emit 0x03
        _emit 0xcb
        _emit 0x8a
        _emit 0x09
        _emit 0x80
        _emit 0xf9
        _emit 0x02
        _emit 0x74
        _emit 0x05
        _emit 0x80
        _emit 0xf9
        _emit 0x06
        _emit 0x75
        _emit 0x10
        _emit 0x3d
        _emit 0xfd
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x74
        _emit 0x09
        _emit 0xf6
        _emit 0xc6
        _emit 0x80
        _emit 0x74
        _emit 0x04
        _emit 0xff
        _emit 0x44
        _emit 0x24
        _emit 0x10
        _emit 0x8b
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x83
        _emit 0xc7
        _emit 0x02
        _emit 0x48
        _emit 0x89
        _emit 0x44
        _emit 0x24
        _emit 0x14
        _emit 0x75
        _emit 0xb8
        _emit 0xa1
        _emit 0x30
        _emit 0x8c
        _emit 0x0a
        _emit 0x10
        _emit 0x8a
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0x8a
        _emit 0x5c
        _emit 0x06
        _emit 0x21
        _emit 0x81
        _emit 0xc6
        _emit 0x4d
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x02
        _emit 0xda
        _emit 0x81
        _emit 0xfe
        _emit 0x78
        _emit 0xca
        _emit 0x00
        _emit 0x00
        _emit 0x88
        _emit 0x9c
        _emit 0x06
        _emit 0xd4
        _emit 0xfd
        _emit 0xff
        _emit 0xff
        _emit 0x0f
        _emit 0x8c
        _emit 0x70
        _emit 0xff
        _emit 0xff
        _emit 0xff
        _emit 0xe8
        _emit 0xb9
        _emit 0x44
        _emit 0x00
        _emit 0x00
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x54
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0x68
        _emit 0x88
        _emit 0x05
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x04
        _emit 0x10
        _emit 0x03
        _emit 0x10
        _emit 0xe8
        _emit 0xa3
        _emit 0xd9
        _emit 0xfe
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0x33
        _emit 0xc0
        _emit 0x5d
        _emit 0x5f
        _emit 0x5e
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0x08
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xc3
    }
}
#else
// CFLAGS: /DREBREW_ALLOW_NAKED /O2 /Gd
// FUNCTION: SERVER 0x10015950
// gm_Open

int __cdecl gm_Open(int map_id)
{
	unsigned int* src_player_ptr;
	unsigned int* dst_player_ptr;
	unsigned int player_field;
	FILE* file_handle;
	int next_offset;
	unsigned short slot_entry;
	char item_category;
	int producible_count;
	unsigned short* slot_ptr;
	int slot_counter;
	unsigned char path_buf[512];
	int table_offset;

	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4d3, "gm_Open(): enter", 1);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4d6, "gm_Open(): Spieler initialisieren", 1);
	src_player_ptr = (unsigned int*) &g_100a8cf8;
	dst_player_ptr = (unsigned int*) &g_1009b764;
	do {
		dst_player_ptr[-1] = src_player_ptr[-0x14];
		player_field = *src_player_ptr;
		dst_player_ptr[0] = 1000;
		dst_player_ptr[1] = player_field;
		dst_player_ptr[2] = 1000;
		memcpy((void*) &dst_player_ptr[3], (void*) &g_1002dde0, 0x2a80);
		src_player_ptr = src_player_ptr + 0xbd;
		dst_player_ptr = dst_player_ptr + 0xaa4;
	} while ((int) src_player_ptr < (int) 0x100a9bbc);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4e3, "gm_Open(): Gebaeude-Daten", 1);
	g_entity_type_table = (int) m_AllocTracked(0xca78, (const char*) 0x100311d8);
	if (g_entity_type_table == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4e8, "Memory could not be allocated!", 1);
		return -1;
	}
	g_1014d8c0 = (int) m_AllocTracked(0xa900, (const char*) 0x100311a0);
	memset((void*) g_1014d8c0, 0, 0xa900);
	if (g_1014d8c0 == 0) {
		return -2;
	}
	sprintf((char*) path_buf, (char*) 0x1003118c, map_id, (char*) 0x10031194);
	file_handle = fopen((char*) path_buf, (char*) 0x1002944c);
	if (file_handle == 0) {
		LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x4f5, (char*) 0x10031154, 1);
		return -3;
	}
	fread((void*) g_entity_type_table, 0x24d, 0x58, file_handle);
	fflush(file_handle);
	g_item_def_table = (int) m_AllocTracked(0xb9dc, (const char*) 0x10031140);
	if (g_item_def_table == 0) {
		return -4;
	}
	g_100a8c34 = (int) m_AllocTracked(0x14f218, (const char*) 0x1003112c);
	if (g_100a8c34 == 0) {
		return -5;
	}
	memset((void*) g_100a8c34, 0, 0x14f218);
	sprintf((char*) path_buf, (char*) 0x1003118c, map_id, (char*) 0x10031120);
	file_handle = fopen((char*) path_buf, (char*) 0x1002944c);
	if (file_handle == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
			0x52d,
			"Objekt-Daten konnten nicht geladen werden! (A_Obj.dat)",
			1
		);
		return -6;
	}
	fread((void*) g_item_def_table, 0x41, 0x2dc, file_handle);
	fflush(file_handle);
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x536, "gm_Open(): gm_InitObjektHersteller", 1);
	gm_InitObjektHersteller();
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x53a, "gm_Open(): gm_KillAllSpieler", 1);
	gm_InitEntitySlots();
	LogMessageInternal(
		"D:\\Develop\\DieGildeAddOn\\game\\spiel.c",
		0x53e,
		"gm_Open(): ---- Das dusselige Datendesign hinbiegen !! -----",
		1
	);
	table_offset = 0;
	do {
		producible_count = 0;
		slot_counter = 0x40;
		slot_ptr = (unsigned short*) (table_offset + 0x23 + g_entity_type_table);
		do {
			slot_entry = *slot_ptr;
			if (slot_entry != 0xffff) {
				item_category = *(char*) (g_item_def_table + (slot_entry & 0x7fff) * 0x41);
				if (((item_category == '\x02') || (item_category == '\x06')) && ((slot_entry & 0x7fff) != 0xfd) &&
					((slot_entry & 0x8000) != 0)) {
					producible_count = producible_count + 1;
				}
			}
			slot_ptr = slot_ptr + 1;
			slot_counter = slot_counter + -1;
		} while (slot_counter != 0);
		next_offset = table_offset + 0x24d;
		*(char*) (table_offset + 0x21 + g_entity_type_table) =
			*(char*) (table_offset + 0x21 + g_entity_type_table) + producible_count;
		table_offset = next_offset;
	} while (next_offset < 0xca78);
	_getpid();
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\game\\spiel.c", 0x588, "gm_Open(): exit", 1);
	return 0;
}
#endif


/* Resets all entities to initial state. Walks the entity
 * tables and clears all active entities without deallocation. */
int g_citizen_count;
extern unsigned char g_current_season;
extern int g_dynasty_field_44;
int g_dynasty_field_48;
extern char g_dynasty_field_49;
extern int g_dynasty_field_4c;
char g_query_active;
extern int g_query_count;
char g_query_flag1;
char g_query_flag2;
char g_query_flag3;
extern unsigned char* g_query_filter_base;
unsigned short* g_query_cursor;
extern int g_entity_table_end;
extern int g_current_year;
extern int g_default_value_b;
extern int g_default_value_c;
extern short g_default_value_d;
extern char* g_slot_table;
extern char g_entity_state_base;
extern int g_entity_ref_table;
extern char g_entity_type_bytes;
int g_array_count[4] = {
    0x00, 0x00, 0x00, 0x00,
};
int g_stat1[4] = {
    0x00, 0x00, 0x00, 0x00,
};
int g_stat2[4] = {
    0x00, 0x00, 0x00, 0x00,
};
int g_stat3[4] = {
    0x00, 0x00, 0x00, 0x00,
};
int g_stat4[4] = {
    0x00, 0x00, 0x00, 0x00,
};
int g_flag_3c[4] = {
    0x00, 0x00, 0x00, 0x00,
};
void* g_array_ptr[4] = {
    0x00, 0x00, 0x00, 0x00,
};
char g_stream_pool[1] = {
    0x00,
};
int g_stream_count[4] = {
    0x00, 0x00, 0x00, 0x00,
};
int g_connection_counter[4] = {
    0x00, 0x00, 0x00, 0x00,
};

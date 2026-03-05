// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 267
// CFLAGS: /O2 /Gd
// SYMBOL: _CmdAllocBuilding

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#endif

#include "../command_internal.h"

typedef struct player_slot {
	char gap_0000[0x2641fc];
	int data;
	char gap_264200[0x64];
} player_slot;

typedef struct copy_12_dwords {
	uint data[12];
} copy_12_dwords;

extern player_slot g_player_slot_0[];
extern char* __cdecl AllocGebaeude(uchar, uint);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);

extern char s_gm_AllocGebaeude___failed_1002cb34[];
extern char s_Invalid__GI_Id__for_cmdt_ALLOC_B_1002caf0[];

// FUNCTION: SERVER 0x1000d350
int __cdecl CmdAllocBuilding(int param_1, char* param_2)
{
	char* pcVar1;
	int iVar3;
	int i;

	*(int*) (param_1 + 0x10) = g_timestamp_0b6c;
	if (*(int*) (param_1 + 0x16) == -1) {
		i = 0xffff;
	}
	else {
		iVar3 = get_field_by_type((char*) param_1, *(int*) (param_1 + 0x16));
		*(int*) (param_1 + 0x16) = iVar3;
		i = 0;
		while ((ushort) i < 0x300) {
			if (*(ushort*) (g_static_entity_table_358a0 + (uint)(ushort) i * 0x21c) != (ushort) 0xffff &&
				*(int*) (g_static_entity_table_358a0 + (uint)(ushort) i * 0x21c + 4) == iVar3) {
				break;
			}
			i = i + 1;
		}
		if ((ushort) i >= 0x300) {
			LogMessageInternal(
				s_D__Develop_DieGildeAddOn_command_1002c748,
				0x280b,
				s_Invalid__GI_Id__for_cmdt_ALLOC_B_1002caf0,
				1
			);
			return 1;
		}
	}
	pcVar1 = AllocGebaeude(*(uchar*) (param_1 + 0x14), i);
	if (pcVar1 == (char*) 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x2817,
			s_gm_AllocGebaeude___failed_1002cb34,
			1
		);
		return 1;
	}
	g_player_slot_0[(uint) *(uchar*) (param_1 + 3)].data = *(int*) (pcVar1 + 1);
	*(ushort*) (pcVar1 + 0x5a) = *(ushort*) (param_1 + 0x1a);
	if (*(int*) (param_1 + 0x1c) != 0) {
		*(copy_12_dwords*) (pcVar1 + 0x65) = *(copy_12_dwords*) (param_1 + 0x20);
	}
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
		param_2[1] = '\x02';
		*(char**) (param_2 + 6) = pcVar1;
	}
	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

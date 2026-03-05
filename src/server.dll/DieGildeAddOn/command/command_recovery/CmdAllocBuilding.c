// FUNCTION: SERVER 0x1000d350
// STATUS: STUB
// BLOCKER: instruction folding (lea vs mov), zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 267
// CFLAGS: /O2 /Gd
// SYMBOL: _CmdAllocBuilding
// BLOCKER_DELTA: 204

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#endif

/*
// BLOCKER_DELTA: 226
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 267B
 *    CFlags: 
 *    Symbol: _CmdAllocBuilding
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl CmdAllocBuilding(int param_1,char *param_2)
 * 
 * {
 *   char *pcVar1;
 *   int in_ECX;
 *   uint uVar2;
 *   int iVar3;
 *   uint uVar4;
 *   undefined4 *puVar5;
 *   char *pcVar6;
 *   
 *   *(undefined4 *)(param_1 + 0x10) = g_timestamp_0b6c;
 *   if (*(int *)(param_1 + 0x16) == -1) {
 *     uVar4 = 0xffff;
 * LAB_1000d36b:
 *     pcVar1 = AllocGebaeude(CONCAT31((int3)((uint)in_ECX >> 8),*(undefined1 *)(param_1 + 0x14)),uVar4
 *                           );
 *     if (pcVar1 != (char *)0x0) {
 *       *(undefined4 *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x2641fc) =
 *            *(undefined4 *)(pcVar1 + 1);
 *       *(undefined2 *)(pcVar1 + 0x5a) = *(undefined2 *)(param_1 + 0x1a);
 *       if (*(int *)(param_1 + 0x1c) != 0) {
 *         puVar5 = (undefined4 *)(param_1 + 0x20);
 *         pcVar6 = pcVar1 + 0x65;
 *         for (iVar3 = 0xc; iVar3 != 0; iVar3 = iVar3 + -1) {
 *           *(undefined4 *)pcVar6 = *puVar5;
 *           puVar5 = puVar5 + 1;
 *           pcVar6 = pcVar6 + 4;
 *         }
 *       }
 *       if (param_2 != (char *)0x0) {
 *         *param_2 = '\x01';
 *         param_2[1] = '\x02';
 *         *(char **)(param_2 + 6) = pcVar1;
 *       }
 *       return 0;
 *     }
 *     pcVar1 = s_gm_AllocGebaeude___failed_1002cb34;
 *     uVar4 = 0x2817;
 *   }
 *   else {
 *     iVar3 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x16));
 */

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

typedef struct copy_12_dwords {
	uint data[12];
} copy_12_dwords;

extern int g_timestamp_0b6c;
extern char g_player_slot_0[];
extern char g_static_entity_table_358a0[];

extern int __cdecl get_field_by_type(char*, int);
extern char* __cdecl AllocGebaeude(uchar, uint);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_gm_AllocGebaeude___failed_1002cb34[];
extern char s_Invalid__GI_Id__for_cmdt_ALLOC_B_1002caf0[];

int __cdecl CmdAllocBuilding(int param_1, char* param_2)
{
	char* pcVar1;
	uint uVar4;
	int i;
	int iVar3;
	uint uVar2;

	*(int*) (param_1 + 0x10) = g_timestamp_0b6c;
	if (*(int*) (param_1 + 0x16) == -1) {
		uVar4 = 0xffff;
	}
	else {
		iVar3 = get_field_by_type((char*) param_1, *(int*) (param_1 + 0x16));
		*(int*) (param_1 + 0x16) = iVar3;
		uVar4 = 0xffff;
		i = 0;
		while ((uint) (ushort) i < 0x300) {
			uVar2 = (uint) (ushort) i;
			if ((*(ushort*) (g_static_entity_table_358a0 + uVar2 * 0x21c) != (ushort) 0xffff) &&
				(*(int*) (g_static_entity_table_358a0 + uVar2 * 0x21c + 4) == iVar3)) {
				uVar4 = uVar2;
				break;
			}
			i = i + 1;
		}
		if ((uint) (ushort) i >= 0x300) {
			LogMessageInternal(
				s_D__Develop_DieGildeAddOn_command_1002c748,
				0x280b,
				s_Invalid__GI_Id__for_cmdt_ALLOC_B_1002caf0,
				1
			);
			return 1;
		}
	}
	pcVar1 = AllocGebaeude(*(uchar*) (param_1 + 0x14), uVar4);
	if (pcVar1 == (char*) 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x2817,
			s_gm_AllocGebaeude___failed_1002cb34,
			1
		);
		return 1;
	}
	uVar2 = (uint) * (uchar*) (param_1 + 3);
	*(int*) (g_player_slot_0 + uVar2 * 0x26410 + 0x2641fc) = *(int*) (pcVar1 + 1);
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

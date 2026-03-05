// FUNCTION: SERVER 0x1000d460
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 267
// CFLAGS: /O2 /Gd
// SYMBOL: _CmdAllocPlayer
// BLOCKER_DELTA: 209

#ifdef __clang__
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
// BLOCKER_DELTA: 209
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 267B
 *    CFlags: 
 *    Symbol: _CmdAllocPlayer
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl CmdAllocPlayer(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   ushort *puVar2;
 *   uint uVar3;
 *   
 *   *(undefined4 *)(param_1 + 0x10) = g_timestamp_0b6c;
 *   iVar1 = rand();
 *   *(int *)(param_1 + 0x26) = iVar1;
 *   crt_thread_set_alt(iVar1);
 *   if (*(int *)(param_1 + 0x1f) == -1) {
 *     puVar2 = (ushort *)0x0;
 *   }
 *   else {
 *     iVar1 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x1f));
 *     *(int *)(param_1 + 0x1f) = iVar1;
 *     puVar2 = StartFilteredEntitySearch(1,1,iVar1);
 *     if (puVar2 == (ushort *)0x0) {
 *       LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2889,
 *                          s_Invalid__GI_Id__for_cmdt_ALLOC_S_1002cb50,1);
 *       return 1;
 *     }
 *   }
 *   uVar3 = CreateEntityFromParents
 *                     ((uint)*(byte *)(param_1 + 0x14),*(int *)(param_1 + 0x15),
 *                      *(int *)(param_1 + 0x19),(uint)*(ushort *)(param_1 + 0x1d),(int)puVar2);
 *   uVar3 = uVar3 & 0xffff;
 *   if (uVar3 == 0xffff) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x2897,
 *                        s_cm_ExAllocSpieler___gm_AllocSpie_1002cb8c,1);
 *     return 1;
 *   }
 *   *(undefined4 *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x2641f8) =
 *        (&g_static_entity0_entity_id)[uVar3 * 0x87];
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *     param_2[1] = '\x01';
 *     *(undefined2 **)(param_2 + 6) = &g_static_entity_table_358a0 + uVar3 * 0x10e;
 *   }
 *   return 0;
 * }
 */

typedef unsigned int uint;
typedef unsigned short ushort;
typedef unsigned char uchar;

extern int g_timestamp_0b6c;
extern char g_player_slot_0[];
extern char g_static_entity_table_358a0[];

extern int __cdecl rand(void);
extern void __cdecl crt_thread_set_alt(int);
extern int __cdecl get_field_by_type(char*, int);
extern void* __cdecl StartFilteredEntitySearch(int, ...);
extern uint __cdecl CreateEntityFromParents(uint, int, int, ushort, int, uint, uint, uint);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_Invalid__GI_Id__for_cmdt_ALLOC_S_1002cb50[];
extern char s_cm_ExAllocSpieler___gm_AllocSpie_1002cb8c[];

int __cdecl CmdAllocPlayer(int param_1, char* param_2)
{
	int iVar1;
	uint uVar2;
	int iVar3;
	char* pcVar5;

	*(int*) (param_1 + 0x10) = g_timestamp_0b6c;
	iVar1 = rand();
	*(int*) (param_1 + 0x26) = iVar1;
	crt_thread_set_alt(iVar1);
	iVar1 = *(int*) (param_1 + 0x1f);
	if (iVar1 == -1) {
		iVar1 = 0;
	}
	else {
		iVar3 = get_field_by_type((char*) param_1, iVar1);
		*(int*) (param_1 + 0x1f) = iVar3;
		iVar1 = (int) StartFilteredEntitySearch(1, 1, iVar3);
		if (iVar1 == 0) {
			LogMessageInternal(
				s_D__Develop_DieGildeAddOn_command_1002c748,
				0x2889,
				s_Invalid__GI_Id__for_cmdt_ALLOC_S_1002cb50,
				1
			);
			return 1;
		}
	}
	uVar2 = CreateEntityFromParents(
		*(uchar*) (param_1 + 0x14),
		*(int*) (param_1 + 0x15),
		*(int*) (param_1 + 0x19),
		*(ushort*) (param_1 + 0x1d),
		iVar1,
		*(uchar*) (param_1 + 0x23),
		*(uchar*) (param_1 + 0x24),
		*(uchar*) (param_1 + 0x25)
	);
	uVar2 = uVar2 & 0xffff;
	if (uVar2 == 0xffff) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x2897,
			s_cm_ExAllocSpieler___gm_AllocSpie_1002cb8c,
			1
		);
		return 1;
	}
	*(int*) (g_player_slot_0 + (uint) *(uchar*) (param_1 + 3) * 0x264264 + 0x2641f8) =
		*(int*) (g_static_entity_table_358a0 + uVar2 * 0x21c + 4);
	if (param_2 != (char*) 0) {
		pcVar5 = g_static_entity_table_358a0 + uVar2 * 0x21c;
		*param_2 = '\x01';
		param_2[1] = '\x01';
		*(char**) (param_2 + 6) = pcVar5;
	}
	return 0;
}

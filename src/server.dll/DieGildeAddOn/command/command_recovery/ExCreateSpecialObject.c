// FUNCTION: SERVER 0x1000f2f0
// STATUS: STUB
// BLOCKER: instruction folding (lea vs mov), zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 176
// CFLAGS: /O2 /Gd
// SYMBOL: _ExCreateSpecialObject

/*
// BLOCKER_DELTA: 114
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 172B
 *    CFlags: 
 *    Symbol: _ExCreateSpecialObject
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl ExCreateSpecialObject(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   char *pcVar2;
 *   
 *   *(undefined4 *)(param_1 + 0x10) = g_timestamp_0b6c;
 *   iVar1 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x14));
 *   *(int *)(param_1 + 0x14) = iVar1;
 *   pcVar2 = AllocGameObject(iVar1,0x1b5,1);
 *   if (pcVar2 == (char *)0x0) {
 *     return 1;
 *   }
 *   *(undefined4 *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x264200) =
 *        *(undefined4 *)(pcVar2 + 2);
 *   pcVar2[0x12] = '@';
 *   *(undefined4 *)(pcVar2 + 0x1c) = *(undefined4 *)(param_1 + 0x18);
 *   *(undefined2 *)(pcVar2 + 0x20) = *(undefined2 *)(param_1 + 0x1c);
 *   pcVar2[0x22] = *(char *)(param_1 + 0x1e);
 *   pcVar2[0x22] = '\0';
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x40db,
 *                      s_cm_ExAllocThemaPredigt____Execut_1002d184,1);
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *     param_2[1] = '\x03';
 *     *(char **)(param_2 + 6) = pcVar2;
 *   }
 *   return 0;
 * }
*/

extern int __cdecl get_field_by_type(char*, int);
extern char* __cdecl AllocGameObject(int, unsigned int, int);
extern void __cdecl LogMessageInternal(char*, int, char*, int);

extern int g_timestamp_0b6c;
extern char g_player_slot_0[];
extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ExAllocThemaPredigt____Execut_1002d184[];

int __cdecl ExCreateSpecialObject(int param_1, char* param_2)
{
	int iVar1;
	char* pcVar2;
	char* src;
	char* dst;

	*(int*) (param_1 + 0x10) = g_timestamp_0b6c;
	iVar1 = get_field_by_type((char*) param_1, *(int*) (param_1 + 0x14));
	*(int*) (param_1 + 0x14) = iVar1;
	pcVar2 = AllocGameObject(iVar1, 0x1b5, 1);
	if (pcVar2 == (char*) 0) {
		return 1;
	}
	*(int*) (g_player_slot_0 + (unsigned int) *(unsigned char*) (param_1 + 3) * 0x264264 + 0x264200) =
		*(int*) (pcVar2 + 2);
	pcVar2[0x12] = '@';
	param_1 += 0x18;
	dst = pcVar2 + 0x1c;
	*(int*) dst = *(int*) param_1;
	*(unsigned short*) (dst + 4) = *(unsigned short*) (param_1 + 4);
	dst[6] = *(char*) (param_1 + 6);
	pcVar2[0x22] = '\0';
	LogMessageInternal(
		s_D__Develop_DieGildeAddOn_command_1002c748,
		0x40db,
		s_cm_ExAllocThemaPredigt____Execut_1002d184,
		1
	);
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
		param_2[1] = '\x03';
		*(char**) (param_2 + 6) = pcVar2;
	}
	return 0;
}

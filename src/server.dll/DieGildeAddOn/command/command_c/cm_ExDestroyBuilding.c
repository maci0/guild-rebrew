// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 171

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 171B
 *    CFlags: 
 *    Symbol: _DestroyBuilding
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExDestroyBuilding(int param_1,char *param_2)
 * 
 * {
 *   ushort *puVar1;
 *   ushort *puVar2;
 *   int *piVar3;
 *   
 *   puVar1 = StartFilteredEntitySearch(1,1,*(undefined4 *)(param_1 + 0x10));
 *   if (puVar1 != (ushort *)0x0) {
 *     puVar2 = StartEntityQuery(0,2,7,4,0x1d);
 *     while (puVar2 != (ushort *)0x0) {
 *       if (*(int *)(puVar2 + 0xe) == *(int *)((int)puVar1 + 1)) {
 *         RemoveEntityLink((int)puVar2);
 *       }
 *       puVar2 = NextEntityQueryMatch();
 *     }
 *     piVar3 = &g_work_building_ptrs;
 *     do {
 *       if ((ushort *)*piVar3 == puVar1) {
 *         *piVar3 = 0;
 *       }
 *       piVar3 = piVar3 + 0x87;
 *     } while ((int)piVar3 < 0x1009ae0c);
 *     CleanupBuildingEntity((uchar *)puVar1);
 *     if (param_2 != (char *)0x0) {
 *       *param_2 = '\x02';
 *       param_2[1] = '\0';
 *       param_2[6] = '\0';
 *       param_2[7] = '\0';
 *       param_2[8] = '\0';
 *       param_2[9] = '\0';
 *     }
 *     return 0;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x4c32,
 *                      s_cm_ExSetGebUpgrade____Could_not_f_1002d2ec,1);
 *   return 1;
 * }
*/

#include "../command_internal.h"

extern ushort* __cdecl StartFilteredEntitySearch(int, int, int);
extern ushort* __cdecl StartEntityQuery(int, int, int, int, int);
extern ushort* __cdecl NextEntityQueryMatch(void);
extern void __cdecl RemoveEntityLink(int);
extern int __cdecl CleanupBuildingEntity(uchar*);
extern void __cdecl LogMessageInternal(char*, int, char*, int);

extern int g_work_building_ptrs;
extern char s_cm_ExSetGebUpgrade____Could_not_f_1002d2ec[];

// FUNCTION: SERVER 0x1000f680
int __cdecl cm_ExDestroyBuilding(int param_1, char* param_2)
{
	ushort* puVar1;
	ushort* puVar2;
	int* piVar3;

	puVar1 = StartFilteredEntitySearch(1, 1, *(int*) (param_1 + 0x10));
	if (puVar1 == (ushort*) 0x0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x4c32,
			s_cm_ExSetGebUpgrade____Could_not_f_1002d2ec,
			1
		);
		return 1;
	}

	puVar2 = StartEntityQuery(0, 2, 7, 4, 0x1d);
	while (puVar2 != (ushort*) 0x0) {
		if (*(int*) (puVar2 + 0xe) == *(int*) ((int) puVar1 + 1)) {
			RemoveEntityLink((int) puVar2);
		}
		puVar2 = NextEntityQueryMatch();
	}

	piVar3 = &g_work_building_ptrs;
	do {
		if ((ushort*) *piVar3 == puVar1) {
			*piVar3 = 0;
		}
		piVar3 = piVar3 + 0x87;
	} while ((int) piVar3 < 0x1009ae0c);

	CleanupBuildingEntity((uchar*) puVar1);

	if (param_2 != (char*) 0x0) {
		*param_2 = '\x02';
		param_2[1] = '\0';
		*(int*) (param_2 + 6) = 0;
	}
	return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 206

#include "../command_internal.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#endif

/*
// BLOCKER_DELTA: 81
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 206B
 *    CFlags: 
 *    Symbol: _SetBuildingOwner
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl SetBuildingOwner(int param_1,char *param_2)
 * 
 * {
 *   ushort *puVar1;
 *   ushort *puVar2;
 *   ushort *puVar3;
 *   uint line;
 *   char *msg;
 *   
 *   puVar1 = StartFilteredEntitySearch(1,1,*(undefined4 *)(param_1 + 0x10));
 *   if (puVar1 == (ushort *)0x0) {
 *     msg = s_cm_ExSetGebBesitzer____Could_not_1002d214;
 *     line = 0x4972;
 *   }
 *   else {
 *     puVar2 = (ushort *)LookupEntityRecordById(*(int *)(param_1 + 0x18));
 *     if ((puVar2 != (ushort *)0x0) || (*(int *)(param_1 + 0x18) == -1)) {
 *       puVar3 = (ushort *)LookupEntityRecordById(*(int *)(param_1 + 0x14));
 *       if ((puVar3 == (ushort *)0x0) && (*(int *)(param_1 + 0x14) != -1)) {
 *         LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x4990,
 *                            s_cm_ExSetGebBesitzer____Could_not_1002d1a8,1);
 *         return 2;
 *       }
 *       AssignBuildingOwner((uchar *)puVar1,*puVar3,(uint)*puVar2);
 *       if (param_2 != (char *)0x0) {
 *         *param_2 = '\x02';
 *         param_2[1] = '\0';
 *         param_2[6] = '\0';
 *         param_2[7] = '\0';
 *         param_2[8] = '\0';
 *         param_2[9] = '\0';
 *       }
 *       return 0;
 *     }
 *     msg = s_cm_ExSetGebBesitzer____Could_not_1002d1e0;
 *     line = 0x4980;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,msg,1);
 *   return 1;
 * }
 */

extern ushort* __cdecl StartFilteredEntitySearch(int, ...);
extern void __cdecl AssignBuildingOwner(char*, uint, uint);
extern void __cdecl LogMessageInternal(const char*, uint, const char*, int);

extern char s_cm_ExSetGebBesitzer____Could_not_1002d214[];
extern char s_cm_ExSetGebBesitzer____Could_not_1002d1e0[];
extern char s_cm_ExSetGebBesitzer____Could_not_1002d1a8[];

// FUNCTION: SERVER 0x1000f3b0
int __cdecl SetBuildingOwner(int param_1, char* param_2)
{
	ushort* building;
	ushort* old_owner;
	ushort* new_owner;
	uint old_owner_value;
	uint new_owner_value;

	building = StartFilteredEntitySearch(1, 1, *(int*) (param_1 + 0x10));
	if (building == (ushort*) 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x4972,
			s_cm_ExSetGebBesitzer____Could_not_1002d214,
			1
		);
		return 1;
	}

	old_owner = (ushort*) LookupEntityRecordById(*(int*) (param_1 + 0x18));
	if ((old_owner == (ushort*) 0) && (*(int*) (param_1 + 0x18) != -1)) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x4980,
			s_cm_ExSetGebBesitzer____Could_not_1002d1e0,
			1
		);
		return 1;
	}

	new_owner = (ushort*) LookupEntityRecordById(*(int*) (param_1 + 0x14));
	if ((new_owner == (ushort*) 0) && (*(int*) (param_1 + 0x14) != -1)) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x4990,
			s_cm_ExSetGebBesitzer____Could_not_1002d1a8,
			1
		);
		return 2;
	}

	old_owner_value = *(ushort*) old_owner;
	new_owner_value = *(ushort*) new_owner;
	AssignBuildingOwner((char*) building, new_owner_value, old_owner_value);

	if (param_2 != (char*) 0) {
		*param_2 = '\x02';
		param_2[1] = '\0';
		*(int*) (param_2 + 6) = 0;
	}
	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

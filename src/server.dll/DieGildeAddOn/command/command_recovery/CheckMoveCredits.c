// FUNCTION: SERVER 0x1000cb20
// STATUS: STUB
// BLOCKER: jump condition swap, loop rotation / branch layout, stack frame choice (push vs sub esp), zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 171
// CFLAGS: /O2 /Gd
// SYMBOL: _CheckMoveCredits

/*
// BLOCKER_DELTA: 165
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 267B
 *    CFlags: 
 *    Symbol: _CheckMoveCredits
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl CheckMoveCredits(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   int *piVar3;
 *   undefined4 extraout_ECX;
 *   uint line;
 *   char *msg;
 *   void *local_8;
 *   void *local_4;
 *   
 *   iVar1 = param_1;
 *   if (*(int *)(param_1 + 0x14) == -1) {
 *     return 0;
 *   }
 *   iVar2 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x14));
 *   *(int *)(iVar1 + 0x14) = iVar2;
 *   iVar2 = ResolveEntityById((void **)&param_1,&local_8,&local_4,iVar2);
 *   if (iVar2 == 0) {
 *     msg = s_cm_ChkMoveCredits____Invalid__qu_1002c7a4;
 *     line = 0x22f9;
 *   }
 *   else {
 *     if (param_1 == 0) {
 *       if (local_8 == (void *)0x0) {
 *         piVar3 = (int *)((int)local_4 + 0x178);
 *       }
 *       else {
 *         piVar3 = (int *)((int)local_8 + 0x14);
 *       }
 *     }
 *     else {
 *       piVar3 = (int *)(param_1 + 0x5d);
 *     }
 *     iVar2 = QueryEntitySum(*piVar3,CONCAT31((int3)((uint)extraout_ECX >> 8),
 *                                             *(undefined1 *)(iVar1 + 0x1c)));
 *     if (-1 < iVar2 - *(int *)(iVar1 + 0x1d)) {
 *       return 0;
 *     }
 *     msg = s_cm_ChkMoveCredits____Not_enough_m_1002c774;
 *     line = 0x231b;
*/

extern int __cdecl get_field_by_type(char*, int);
extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern int __cdecl QueryEntitySum(int, int);
extern void __cdecl LogMessageInternal(char*, int, char*, int);

extern char s_D__Develop_DieGildeAddOn_command_1002c748[];
extern char s_cm_ChkMoveCredits____Invalid__qu_1002c7a4[];
extern char s_cm_ChkMoveCredits____Not_enough_m_1002c774[];

int __cdecl CheckMoveCredits(int param_1, char* param_2)
{
	int cmd;
	int value;
	int* sum_ptr;
	void* local_8;
	void* local_4;

	cmd = param_1;
	if (*(int*) (param_1 + 0x14) == -1) {
		return 0;
	}
	value = get_field_by_type((char*) param_1, *(int*) (param_1 + 0x14));
	*(int*) (cmd + 0x14) = value;
	if (ResolveEntityById((void**) &param_1, &local_8, &local_4, value) == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x22f9,
			s_cm_ChkMoveCredits____Invalid__qu_1002c7a4,
			1
		);
		return 1;
	}

	if (param_1 != 0) {
		sum_ptr = (int*) (param_1 + 0x5d);
	}
	else {
		if (local_8 != (void*) 0x0) {
			sum_ptr = (int*) ((int) local_8 + 0x14);
		}
		else if (param_2 != (char*) 0x0) {
			sum_ptr = (int*) ((int) param_2 + 0x14);
		}
		else {
			sum_ptr = (int*) ((int) local_4 + 0x178);
		}
	}

	value = QueryEntitySum(*sum_ptr, (unsigned int) *(unsigned char*) (cmd + 0x1c));
	if (value - *(int*) (cmd + 0x1d) >= 0) {
		return 0;
	}

	LogMessageInternal(
		s_D__Develop_DieGildeAddOn_command_1002c748,
		0x231b,
		s_cm_ChkMoveCredits____Not_enough_m_1002c774,
		1
	);
	return 1;
}

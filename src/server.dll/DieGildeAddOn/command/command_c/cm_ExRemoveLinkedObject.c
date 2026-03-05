// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 197
// CFLAGS: /O2 /Gd
// SYMBOL: _RemoveLinkedObject
// BLOCKER: prologue register pre-load ordering, instruction folding (lea vs mov), jump condition swap, nodeId register allocation (esi vs ecx)
// BLOCKER_DELTA: 176

#include "../command_internal.h"

extern ushort* __cdecl StartEntityQuery(int, int, int, int, int);
extern int __cdecl RemoveLinkedNodeById(int*, int);

// FUNCTION: SERVER 0x1000f0d0
int __cdecl RemoveLinkedObject(int param_1, char *param_2)
{
	char *pcVar1;
	int iVar3;
	int nodeId;
	void *local_4;

	pcVar1 = param_2;
	iVar3 = param_1;
	if (param_2 != (char *)0x0) {
		*param_2 = '\x02';
	}
	ResolveEntityById((void **)&param_1, (void **)&param_2, &local_4, *(int *)(iVar3 + 0x10));
	if (param_1 != 0) {
		if (*(int *)(iVar3 + 0x14) == -1) {
			nodeId = *(int *)(iVar3 + 0x18);
			param_1 = param_1 + 0x5d;
			goto LAB_1000f154;
		}
		param_2 = (char *)StartEntityQuery(*(int *)(param_1 + 0x5d), 2, 6, 1, *(int *)(iVar3 + 0x14));
		if (param_2 == (char *)0x0) {
			return -2;
		}
		nodeId = *(int *)(iVar3 + 0x18);
		param_1 = (int)param_2 + 0x14;
		goto LAB_1000f154;
	}
	if (local_4 != (void *)0x0) {
		nodeId = *(int *)(iVar3 + 0x18);
		param_1 = (int)local_4 + 0x178;
		goto LAB_1000f154;
	}
	if (param_2 == (char *)0x0) {
		return -1;
	}
	iVar3 = RemoveLinkedNodeById((int *)((int)param_2 + 0x14), *(int *)(iVar3 + 0x18));
	if (iVar3 != 0) {
		return iVar3;
	}
	goto LAB_1000f181;
LAB_1000f154:
	iVar3 = RemoveLinkedNodeById((int *)param_1, nodeId);
	if (iVar3 != 0) {
		return iVar3;
	}
LAB_1000f181:
	if (pcVar1 != (char *)0x0) {
		*pcVar1 = '\x01';
	}
	return 0;
}

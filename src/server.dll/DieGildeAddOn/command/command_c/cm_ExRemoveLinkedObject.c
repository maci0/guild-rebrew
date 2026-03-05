// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 197
// BLOCKER: prologue register pre-load ordering, instruction folding (lea vs mov), jump condition swap, nodeId register allocation (esi vs ecx)
// BLOCKER_DELTA: 176

#include "../command_internal.h"

extern ushort* __cdecl gm_StartEntityQuery(int, int, int, int, int);
extern int __cdecl gm_RemoveLinkedNodeById(int*, int);

// FUNCTION: SERVER 0x1000f0d0
int __cdecl cm_ExRemoveLinkedObject(int param_1, char *param_2)
{
	char *statusOut;
	int result;
	int nodeId;
	void *dynEntity;

	statusOut = param_2;
	result = param_1;
	if (param_2 != (char *)0x0) {
		*param_2 = '\x02';
	}
	gm_ResolveEntityById((void **)&param_1, (void **)&param_2, &dynEntity, *(int *)(result + 0x10));
	if (param_1 != 0) {
		if (*(int *)(result + 0x14) == -1) {
			nodeId = *(int *)(result + 0x18);
			param_1 = param_1 + 0x5d;
			goto LAB_1000f154;
		}
		param_2 = (char *)gm_StartEntityQuery(*(int *)(param_1 + 0x5d), 2, 6, 1, *(int *)(result + 0x14));
		if (param_2 == (char *)0x0) {
			return -2;
		}
		nodeId = *(int *)(result + 0x18);
		param_1 = (int)param_2 + 0x14;
		goto LAB_1000f154;
	}
	if (dynEntity != (void *)0x0) {
		nodeId = *(int *)(result + 0x18);
		param_1 = (int)dynEntity + 0x178;
		goto LAB_1000f154;
	}
	if (param_2 == (char *)0x0) {
		return -1;
	}
	result = gm_RemoveLinkedNodeById((int *)((int)param_2 + 0x14), *(int *)(result + 0x18));
	if (result != 0) {
		return result;
	}
	goto LAB_1000f181;
LAB_1000f154:
	result = gm_RemoveLinkedNodeById((int *)param_1, nodeId);
	if (result != 0) {
		return result;
	}
LAB_1000f181:
	if (statusOut != (char *)0x0) {
		*statusOut = '\x01';
	}
	return 0;
}

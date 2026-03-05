// FUNCTION: SERVER 0x1000f0d0
// STATUS: STUB
// BLOCKER: instruction folding (lea vs mov), jump condition swap
// ORIGIN: GAME
// SIZE: 197
// CFLAGS: /O2 /Gd
// SYMBOL: _RemoveLinkedObject

/*
// BLOCKER_DELTA: 191
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 197B
 *    CFlags: 
 *    Symbol: _RemoveLinkedObject
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl RemoveLinkedObject(int param_1,char *param_2)
 * 
 * {
 *   char *pcVar1;
 *   ushort *puVar2;
 *   int iVar3;
 *   void *local_4;
 *   
 *   pcVar1 = param_2;
 *   iVar3 = param_1;
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x02';
 *   }
 *   ResolveEntityById((void **)&param_1,&param_2,&local_4,*(int *)(param_1 + 0x10));
 *   if (param_1 == 0) {
 *     if (local_4 == (void *)0x0) {
 *       if (param_2 == (char *)0x0) {
 *         return -1;
 *       }
 *       iVar3 = RemoveLinkedNodeById((int *)(param_2 + 0x14),*(int *)(iVar3 + 0x18));
 *       if (iVar3 != 0) {
 *         return iVar3;
 *       }
 *       goto LAB_1000f181;
 *     }
 *     iVar3 = *(int *)(iVar3 + 0x18);
 *     puVar2 = (ushort *)((int)local_4 + 0x178);
 *   }
 *   else if (*(int *)(iVar3 + 0x14) == -1) {
 *     iVar3 = *(int *)(iVar3 + 0x18);
 *     puVar2 = (ushort *)(param_1 + 0x5d);
 *   }
 *   else {
 *     param_2 = (char *)StartEntityQuery(*(int *)(param_1 + 0x5d),2,6,1,*(int *)(iVar3 + 0x14));
 *     if ((ushort *)param_2 == (ushort *)0x0) {
 *       return -2;
 *     }
 *     iVar3 = *(int *)(iVar3 + 0x18);
 *     puVar2 = (ushort *)((int)param_2 + 0x14);
 *   }
 *   iVar3 = RemoveLinkedNodeById((int *)puVar2,iVar3);
 *   if (iVar3 != 0) {
*/

typedef unsigned short ushort;

extern int __cdecl ResolveEntityById(void**, void**, void**, int);
extern ushort* __cdecl StartEntityQuery(int, int, int, int, int);
extern int __cdecl RemoveLinkedNodeById(int*, int);

int __cdecl RemoveLinkedObject(int param_1, char* param_2)
{
	char* status;
	int* node;
	int cmd;
	int ret;
	void* local_4;

	status = param_2;
	cmd = param_1;
	if (param_2 != (char*) 0x0) {
		*param_2 = '\x02';
	}

	ResolveEntityById((void**) &param_1, (void**) &param_2, &local_4, *(int*) (cmd + 0x10));
	if (param_1 != 0) {
		if (*(int*) (cmd + 0x14) == -1) {
			node = (int*) (param_1 + 0x5d);
			cmd = *(int*) (cmd + 0x18);
			goto LAB_1000f154;
		}

		param_2 = (char*) StartEntityQuery(*(int*) (param_1 + 0x5d), 2, 6, 1, *(int*) (cmd + 0x14));
		if (param_2 == (char*) 0x0) {
			return -2;
		}

		node = (int*) ((int) param_2 + 0x14);
		cmd = *(int*) (cmd + 0x18);
		goto LAB_1000f154;
	}

	if (local_4 != (void*) 0x0) {
		node = (int*) ((int) local_4 + 0x178);
		cmd = *(int*) (cmd + 0x18);
		goto LAB_1000f154;
	}

	if (param_2 == (char*) 0x0) {
		return -1;
	}

	node = (int*) ((int) param_2 + 0x14);
	cmd = *(int*) (cmd + 0x18);

LAB_1000f154:
	ret = RemoveLinkedNodeById(node, cmd);
	if (ret != 0) {
		return ret;
	}

	if (status != (char*) 0x0) {
		*status = '\x01';
	}
	return 0;
}

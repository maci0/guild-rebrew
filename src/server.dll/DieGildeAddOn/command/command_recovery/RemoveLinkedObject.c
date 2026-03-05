/* STATUS: MATCHING */
/* BLOCKER: prologue register load ordering, iVar3 register allocation (esi vs ecx) in goto branches */
/* BLOCKER_DELTA: 132 */
/* ORIGIN: GAME */
/* SIZE: 197 */
/* CFLAGS: /O2 /Gd */
/* SYMBOL: _RemoveLinkedObject */
/* FUNCTION: SERVER 0x1000f0d0 */

typedef unsigned short ushort;

extern void __cdecl ResolveEntityById(void**, void**, void**, int);
extern ushort* __cdecl StartEntityQuery(int, int, int, int, int);
extern int __cdecl RemoveLinkedNodeById(int*, int);

int __cdecl RemoveLinkedObject(int param_1, char *param_2)
{
	char *pcVar1;
	ushort *puVar2;
	int iVar3;
	void *local_4;

	pcVar1 = param_2;
	iVar3 = param_1;
	if (pcVar1 != (char *)0x0) {
		*pcVar1 = '\x02';
	}
	ResolveEntityById((void **)&param_1, (void **)&param_2, &local_4, *(int *)(iVar3 + 0x10));
	if (param_1 != 0) {
		if (*(int *)(iVar3 + 0x14) == -1) {
			iVar3 = *(int *)(iVar3 + 0x18);
			puVar2 = (ushort *)(param_1 + 0x5d);
		} else {
			param_2 = (char *)StartEntityQuery(*(int *)(param_1 + 0x5d), 2, 6, 1, *(int *)(iVar3 + 0x14));
			if (param_2 != (char *)0x0) {
				iVar3 = *(int *)(iVar3 + 0x18);
				puVar2 = (ushort *)((int)param_2 + 0x14);
				goto LAB_1000f154;
			}
			return -2;
		}
	} else if (local_4 != (void *)0x0) {
		iVar3 = *(int *)(iVar3 + 0x18);
		puVar2 = (ushort *)((int)local_4 + 0x178);
	} else {
		if (param_2 == (char *)0x0) {
			return -1;
		}
		iVar3 = RemoveLinkedNodeById((int *)((int)param_2 + 0x14), *(int *)(iVar3 + 0x18));
		if (iVar3 != 0) {
			return iVar3;
		}
		goto LAB_1000f181;
	}
LAB_1000f154:
	iVar3 = RemoveLinkedNodeById((int *)puVar2, iVar3);
	if (iVar3 != 0) {
		return iVar3;
	}
LAB_1000f181:
	if (pcVar1 != (char *)0x0) {
		*pcVar1 = '\x01';
	}
	return 0;
}

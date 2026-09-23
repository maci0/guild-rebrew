#include "../command_internal.h"

int __cdecl gm_RemoveLinkedNodeById(int*, int);
unsigned short* __cdecl gm_ff_Objekt(int, int, int, ...);

// FUNCTION: GOLD 0x004c9450
// SIZE: 208
// FUNCTION: GOLDTL 0x4c9ff0
// SIZE: 208
// FUNCTION: SERVER 0x1000f0d0

int __cdecl cm_ExRemoveLinkedObject(int cmd, char *status_ptr)
{
	char *statusOut;
	int result;
	void *dynEntity;

	/* The volatile read loads param_2 straight into edi at the top instead
	 * of staging it through eax, which is what makes the prologue push
	 * ecx/esi/edi before any load. */
	statusOut = *(char* volatile*)&status_ptr;
	if (statusOut != (char *)0x0) {
		*statusOut = '\x02';
	}
	result = cmd;
	gm_ResolveEntityById((void **)&cmd, (void **)&status_ptr, &dynEntity, *(int *)(result + 0x10));
	/* Each arm spells out its own gm_RemoveLinkedNodeById call; the compiler
	 * tail-merges them onto the shared push/call, which is what emits the
	 * target's per-branch `push <nodeId>` followed by `jmp` into the merge
	 * point.  A hand-written goto merge with a shared nodeId local instead
	 * parks the id in esi and sinks the push past the jmp. */
	if (cmd != 0) {
		if (*(int *)(result + 0x14) == -1) {
			result = gm_RemoveLinkedNodeById((int *)(cmd + 0x5d), *(int *)(result + 0x18));
		} else {
			status_ptr = (char *)gm_ff_Objekt(*(int *)(cmd + 0x5d), 2, 6, 1, *(int *)(result + 0x14));
			/* Positive guard: the target falls through on success and keeps
			 * the -2 return out of line after it (`je` to the error block). */
			if (status_ptr != (char *)0x0) {
				result = gm_RemoveLinkedNodeById((int *)((int)status_ptr + 0x14), *(int *)(result + 0x18));
			} else {
				return -2;
			}
		}
	} else if (dynEntity != (void *)0x0) {
		result = gm_RemoveLinkedNodeById((int *)((int)dynEntity + 0x178), *(int *)(result + 0x18));
	} else if (status_ptr != (char *)0x0) {
		/* This arm keeps its own push/call in the target rather than joining
		 * the merge point the other three share; checking result here instead
		 * of at the common tail is what stops it being merged in.  The guard
		 * is positive so the -1 return sits out of line past the tail. */
		result = gm_RemoveLinkedNodeById((int *)((int)status_ptr + 0x14), *(int *)(result + 0x18));
		if (result != 0) {
			return result;
		}
		goto ok;
	} else {
		return -1;
	}
	if (result != 0) {
		return result;
	}
ok:
	if (statusOut != (char *)0x0) {
		*statusOut = '\x01';
	}
	return 0;
}


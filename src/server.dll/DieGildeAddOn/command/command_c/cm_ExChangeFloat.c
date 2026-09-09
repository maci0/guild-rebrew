/* cm_ExChangeFloat - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ExChangeFloat___Invalid_Id_1002d134[];

/* Execution handler: modifies a floating-point attribute on an
 * entity. Resolves the entity, then adds the command's float delta
 * to the field at the given offset. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000eb70
// SIZE: 135

int __cdecl cm_ExChangeFloat(int param_1, char* param_2)
{
	void* pvStack_8;
	void* pvStack_4;
	int resolved;
	int iVar1;
	int iVar2;
	int p;

	iVar1 = param_1;
	iVar2 = gm_GetFieldByType(param_1, *(int*) (param_1 + 0x10));
	*(int*) (param_1 + 0x10) = iVar2;
	iVar2 = gm_ResolveEntityById(&pvStack_4, &pvStack_8, (void**) &resolved, iVar2);
	if (iVar2 == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x347f,
		                   s_cm_ExChangeFloat___Invalid_Id_1002d134, 1);
		return 1;
	}
	p = resolved;
	if (p == 0)
		p = (int) pvStack_8;
	if (p == 0)
		p = (int) pvStack_4;
	/* Folding the offset into p before the load puts the offset temp in
	 * edx; re-reading it inside the store expression keeps it in ecx. */
	p = p + *(int*) (iVar1 + 0x14);
	*(float*) p = *(float*) (iVar1 + 0x18) + *(float*) p;
	if (param_2 != (char*) 0x0) {
		*param_2 = '\x01';
	}
	return 0;
}

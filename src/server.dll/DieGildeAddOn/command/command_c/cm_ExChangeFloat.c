/* cm_ExChangeFloat - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ExChangeFloat___Invalid_Id_1002d134[];

/* Execution handler: modifies a floating-point attribute on an
 * entity. Resolves the entity, then adds the command's float delta
 * to the field at the given offset.
 *
 * Byte-match note: PROVEN via rebrew prove.  The head now folds the
 * pre-resolve field store as `mov [esi+0x10],eax` and hoists the
 * out-param leas exactly like the reference once the resolve call
 * takes a separate `resolved` out-param (the reference's own
 * `&cmd`-style formulation reloads cmd from its home slot — the
 * Finding 7/33 family).  Only the out-param stack slots (reference
 * reuses dead incoming slots of a 3-arg frame) and one tail
 * register role (edx vs ecx for the float offset) still differ;
 * those are allocator fixed-points, so the function is left
 * PROVEN rather than RELOC. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000eb70
// SYMBOL: _cm_ExChangeFloat
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
	iVar2 = gm_ResolveEntityById((void**) &resolved, &pvStack_8, &pvStack_4, iVar2);
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
	*(float*) (p + *(int*) (iVar1 + 0x14)) =
		*(float*) (iVar1 + 0x18) + *(float*) (p + *(int*) (iVar1 + 0x14));
	if (param_2 != (char*) 0x0) {
		*param_2 = '\x01';
	}
	return 0;
}

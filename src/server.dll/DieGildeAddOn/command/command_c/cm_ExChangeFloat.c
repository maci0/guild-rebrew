/* cm_ExChangeFloat - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ExChangeFloat___Invalid_Id_1002d134[];

/* Execution handler: modifies a floating-point attribute on an
 * entity. Resolves the entity, then adds the command's float delta
 * to the field at the given offset.
 *
 * Byte-match note: the head differs from the reference by one
 * instruction — the reference folds the pre-resolve field store as
 * `mov [esi+0x10],eax` (base copy held in esi); every C formulation
 * either CSE-hoists `lea esi,[eax+0x10]` (extra prologue push, docs/
 * msvc6-allocator.md Finding 7 family) or reloads the param from its
 * home slot (`mov ecx,[esp+0x18]`), and MSVC6 8168 computes the three
 * resolve out-param leas after the arg4 push instead of the reference's
 * hoisted arg3 lea (Finding 33).  The tail (entity selection, float
 * `fld/fadd/add/fstp`, result-byte store) matches byte-for-byte. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000eb70
// SYMBOL: _cm_ExChangeFloat
// SIZE: 135

int __cdecl cm_ExChangeFloat(int param_1, char* param_2)
{
	void* pvStack_8;
	void* pvStack_4;
	int iVar1;
	int iVar2;
	int p;

	iVar1 = param_1;
	iVar2 = gm_GetFieldByType(param_1, *(int*) (param_1 + 0x10));
	*(int*) (param_1 + 0x10) = iVar2;
	iVar2 = gm_ResolveEntityById(&pvStack_4, &pvStack_8, (void**) &param_1, iVar2);
	if (iVar2 == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x347f,
		                   s_cm_ExChangeFloat___Invalid_Id_1002d134, 1);
		return 1;
	}
	p = param_1;
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

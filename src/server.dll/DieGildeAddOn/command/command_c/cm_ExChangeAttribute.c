// STATUS: MATCHING
// BLOCKER: instruction folding (lea vs mov), stack frame choice (push vs sub esp)
// ORIGIN: GAME
// SIZE: 242
// BLOCKER_DELTA: 25

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
// BLOCKER_DELTA: 210
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 242B
 *    CFlags: 
 *    Symbol: _ExAccumulateEntityFields
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExChangeAttribute(int param_1,char *param_2)
 * 
 * {
 *   char cVar1;
 *   int iVar2;
 *   int iVar3;
 *   int iVar4;
 *   ushort *puVar5;
 *   int *piVar6;
 *   int *piVar7;
 *   uint uVar8;
 *   void *pvStack_8;
 *   void *pvStack_4;
 *   
 *   iVar2 = param_1;
 *   iVar3 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x10));
 *   iVar4 = gm_ResolveEntityById((void **)&param_1,&pvStack_8,&pvStack_4,iVar3);
 *   if (iVar4 == 0) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x31f7,
 *                        s_cm_ExChangeAttribute___Invalid_I_1002d0b0,1);
 *     return 1;
 *   }
 *   *(int *)(iVar2 + 0x10) = iVar3;
 *   if ((param_1 == 0) && (param_1 = (int)pvStack_8, pvStack_8 == (void *)0x0)) {
 *     param_1 = (int)pvStack_4;
 *   }
 *   uVar8 = 0;
 *   piVar6 = (int *)(iVar2 + 0x15);
 *   if (*(char *)(iVar2 + 0x14) != '\0') {
 *     do {
 *       cVar1 = (char)*piVar6;
 *       iVar3 = (int)*(char *)((int)piVar6 + 1);
 *       puVar5 = (ushort *)((int)piVar6 + 2);
 *       piVar6 = piVar6 + 1;
 *       piVar7 = (int *)((uint)*puVar5 + param_1);
 *       if (cVar1 == '\x01') {
 *         for (; iVar3 != 0; iVar3 = iVar3 + -1) {
 *           *(char *)piVar7 = (char)*piVar7 + (char)*piVar6;
 *           piVar6 = (int *)((int)piVar6 + 1);
 *           piVar7 = (int *)((int)piVar7 + 1);
 *         }
 *       }
 */


extern char s_cm_ExChangeAttribute___Invalid_I_1002d0b0[];

// FUNCTION: SERVER 0x1000e7d0
int __cdecl cm_ExChangeAttribute(int param_1, char *param_2)
{
	signed char elem_size;
	int msg;
	int field_id;
	int resolved;
	int count;
	unsigned int offset;
	char *src_ptr;
	char *dst_ptr;
	uint iter;
	void *existing_ref;
	void *static_ref;

	msg = param_1;
	field_id = gm_GetFieldByType((char *)param_1, *(int *)(param_1 + 0x10));
	resolved = gm_ResolveEntityById((void **)&param_1, &existing_ref, &static_ref, field_id);
	if (resolved == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x31f7,
			s_cm_ExChangeAttribute___Invalid_I_1002d0b0, 1);
		return 1;
	}
	*(int *)(msg + 0x10) = field_id;
	if (param_1 != 0) {
		resolved = param_1;
	} else if ((resolved = (int)existing_ref, existing_ref != (void *)0)) {
		/* resolved already set */
	} else {
		resolved = (int)static_ref;
	}
	iter = 0;
	src_ptr = (char *)(msg + 0x15);
	if (*(unsigned char *)(msg + 0x14) != 0) {
		do {
			elem_size = *src_ptr;
			count = (int)(signed char)src_ptr[1];
			src_ptr += 2;
			offset = (unsigned int)*(ushort *)src_ptr;
			src_ptr += 2;
			dst_ptr = (char *)(offset + (uint)resolved);
			switch (elem_size) {
			case 1:
				while (count > 0) {
					*dst_ptr = *dst_ptr + *src_ptr;
					src_ptr++;
					dst_ptr++;
					count--;
				}
				break;
			case 2:
				while (count > 0) {
					*(short *)dst_ptr = (short)(*(short *)dst_ptr + *(short *)src_ptr);
					src_ptr += 2;
					dst_ptr += 2;
					count--;
				}
				break;
			case 4:
				while (count > 0) {
					*(int *)dst_ptr = *(int *)dst_ptr + *(int *)src_ptr;
					src_ptr += 4;
					dst_ptr += 4;
					count--;
				}
				break;
			}
			iter++;
		} while (iter < *(unsigned char *)(msg + 0x14));
	}
	if (param_2 != (char *)0) {
		*param_2 = '\x01';
	}
	return 0;
}


#include "../command_internal.h"
#include "../../../Units/Error/error.h"

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 346B
 *    CFlags:
 *    Symbol: _ExMoveObject
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExMoveObjekt(int param_1,char *param_2)
 *
 * {
 *   int iVar1;
 *   int iVar2;
 *   int iVar3;
 *   int *piVar4;
 *   int *piVar5;
 *   uint line;
 *   char *msg;
 *   int iVar6;
 *   void *pvStack_8;
 *   void *pvStack_4;
 *
 *   iVar6 = param_1;
 *   iVar2 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x14));
 *   *(int *)(iVar6 + 0x14) = iVar2;
 *   iVar2 = gm_ResolveEntityById(&pvStack_8,(void **)&param_1,&pvStack_4,iVar2);
 *   if (iVar2 == 0) {
 *     iVar6 = 8;
 *     msg = s_cm_ExMoveObjekt___Invalid__quell_1002d024;
 *     line = 0x30a1;
 *   }
 *   else {
 *     if (pvStack_8 == (void *)0x0) {
 *       if (param_1 == 0) {
 *         piVar4 = (int *)((int)pvStack_4 + 0x178);
 *       }
 *       else {
 *         piVar4 = (int *)(param_1 + 0x14);
 *       }
 *     }
 *     else {
 *       piVar4 = (int *)((int)pvStack_8 + 0x5d);
 *     }
 *     iVar2 = gm_GetFieldByType((char *)iVar6,*(int *)(iVar6 + 0x10));
 *     *(int *)(iVar6 + 0x10) = iVar2;
 *     iVar2 = gm_ResolveEntityById(&pvStack_8,(void **)&param_1,&pvStack_4,iVar2);
 *     if (iVar2 == 0) {
 *       iVar6 = 1;
 *       msg = s_cm_ExMoveObjekt___Invalid__ziel__1002cff4;
 *       line = 0x30bd;
 */

/* Round-534: ascending REF VA decl order (R521/R531/R532 mid-pocket lever). */

/* Execution handler: moves an object from one inventory slot
 * to another. Validates source and destination entities, then
 * transfers the object via gm_SubObjekt + gm_AddObjekt. */

// FUNCTION: SERVER 0x1000e530
int __cdecl cm_ExMoveObjekt(int cmd, char* result)
{
	int object_id;
	void* ent_a;
	void* ent_c;
	int entity_or_node;
	int* src_list;
	int* dst_list;
	int prev;

	object_id = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x14));
	*(int*) (cmd + 0x14) = object_id;
	if (gm_ResolveEntityById(&ent_a, (void**) &entity_or_node, &ent_c, object_id) == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\command\\command.c",
			0x30a1,
			"cm_ExMoveObjekt() Invalid 'quell_besitzer_id'",
			8
		);
		return 1;
	}

	if (ent_a != (void*) 0x0) {
		src_list = (int*) ((char*) ent_a + 0x5d);
	}
	else if (entity_or_node != 0) {
		src_list = (int*) (entity_or_node + 0x14);
	}
	else {
		src_list = (int*) ((char*) ent_c + 0x178);
	}

	object_id = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x10));
	*(int*) (cmd + 0x10) = object_id;
	if (gm_ResolveEntityById(&ent_a, (void**) &entity_or_node, &ent_c, object_id) == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\command\\command.c",
			0x30bd,
			"cm_ExMoveObjekt() Invalid 'ziel_besitzer_id'",
			1
		);
		return 1;
	}

	if (ent_a != (void*) 0x0) {
		dst_list = (int*) ((char*) ent_a + 0x5d);
	}
	else if (entity_or_node != 0) {
		dst_list = (int*) (entity_or_node + 0x14);
	}
	else {
		dst_list = (int*) ((char*) ent_c + 0x178);
	}

	object_id = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x18));
	*(int*) (cmd + 0x18) = object_id;

	prev = 0;
	entity_or_node = *src_list;
	while (entity_or_node != 0) {
		if (*(int*) (entity_or_node + 2) == object_id) {
			if (prev == 0) {
				*src_list = *(int*) (entity_or_node + 0x3f);
			}
			else {
				*(int*) (prev + 0x3f) = *(int*) (entity_or_node + 0x3f);
			}
			break;
		}
		prev = entity_or_node;
		entity_or_node = *(int*) (entity_or_node + 0x3f);
	}

	if (entity_or_node == 0) {
		LogMessageInternal(
			"D:\\Develop\\DieGildeAddOn\\command\\command.c",
			0x30f9,
			"cm_ExMoveObjekt() Object not found at source",
			8
		);
		return 1;
	}

	*(int*) (entity_or_node + 6) = *(int*) (cmd + 0x10);
	*(int*) (entity_or_node + 0x3f) = *dst_list;
	*dst_list = entity_or_node;

	if (result != (char*) 0x0) {
		*result = '\x01';
	}

	return 0;
}

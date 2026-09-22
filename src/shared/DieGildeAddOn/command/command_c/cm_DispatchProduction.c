
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 144B
 *    CFlags:
 *    Symbol: _DispatchProductionCommand
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_DispatchProduction(int param_1,char *param_2)
 *
 * {
 *   uint32_t *puVar1;
 *   int iVar2;
 *   uint uVar3;
 *
 *   *(undefined4 *)(param_1 + 0x27) = g_next_object_id;
 *   iVar2 = rand();
 *   *(int *)(param_1 + 0x2b) = iVar2;
 *   puVar1 = (uint32_t *)(param_1 + 0x10);
 *   switch(*(undefined4 *)(param_1 + 0x10)) {
 *   case 0:
 *     uVar3 = AssignProductionSlot((int)puVar1);
 *     return uVar3;
 *   case 1:
 *     uVar3 = gv_HireProductionWorker((int)puVar1);
 *     return uVar3;
 *   case 2:
 *     uVar3 = gv_ExtendProductionTime(puVar1);
 *     return uVar3;
 *   case 3:
 *     iVar2 = gv_ReplaceProductionWorker((uchar *)puVar1);
 *     return iVar2;
 *   case 4:
 *     iVar2 = gv_ActivateSection((uchar *)puVar1);
 *     return iVar2;
 *   case 5:
 *     iVar2 = gv_UpdateProductionProgress((uchar *)puVar1);
 *     return iVar2;
 *   case 6:
 *     iVar2 = gv_ValidateEntityAction((uchar *)puVar1);
 *     return iVar2;
 *   default:
 *     return -1;
 *   }
 * }
 */

#include "../command_internal.h"

unsigned int __cdecl AssignProductionSlot(void*);
unsigned int __cdecl gv_HireProductionWorker(int);
unsigned int __cdecl gv_ExtendProductionTime(uint32_t*);
int __cdecl gv_ReplaceProductionWorker(void*);
int __cdecl gv_ActivateSection(uchar*);
int __cdecl gv_UpdateProductionProgress(void*);
int __cdecl gv_ValidateEntityAction(void*);

/* Dispatch handler: routes production commands based on the
 * sub-command type at cmd+0x10. Dispatches to:
 * 0=AssignProductionSlot, 1=gv_HireProductionWorker,
 * 2=gv_ExtendProductionTime, 3=gv_ReplaceProductionWorker,
 * 4=gv_ActivateSection, 5=gv_UpdateProductionProgress,
 * 6=gv_ValidateEntityAction. Stamps timestamp and random seed. */

// FUNCTION: SERVER 0x10010260
int __cdecl cm_DispatchProduction(int cmd, char* result)
{
	uint32_t* data_ptr;
	int rc;
	unsigned int status;

	(void) result;

	*(int*) (cmd + 0x27) = g_next_object_id;
	rc = rand();
	*(int*) (cmd + 0x2b) = rc;
	data_ptr = (uint32_t*) (cmd + 0x10);
	switch (*(int*) (cmd + 0x10)) {
	case 0:
		status = AssignProductionSlot(data_ptr);
		return status;
	case 1:
		status = gv_HireProductionWorker((int) data_ptr);
		return status;
	case 2:
		status = gv_ExtendProductionTime(data_ptr);
		return status;
	case 3:
		rc = gv_ReplaceProductionWorker(data_ptr);
		return rc;
	case 4:
		rc = gv_ActivateSection((uchar*) data_ptr);
		return rc;
	case 5:
		rc = gv_UpdateProductionProgress(data_ptr);
		return rc;
	case 6:
		rc = gv_ValidateEntityAction(data_ptr);
		return rc;
	default:
		return -1;
	}
}

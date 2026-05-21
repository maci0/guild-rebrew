
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
 *   *(undefined4 *)(param_1 + 0x27) = g_timestamp_0b6c;
 *   iVar2 = rand();
 *   *(int *)(param_1 + 0x2b) = iVar2;
 *   puVar1 = (uint32_t *)(param_1 + 0x10);
 *   switch(*(undefined4 *)(param_1 + 0x10)) {
 *   case 0:
 *     uVar3 = AssignProductionSlot((int)puVar1);
 *     return uVar3;
 *   case 1:
 *     uVar3 = HireProductionWorker((int)puVar1);
 *     return uVar3;
 *   case 2:
 *     uVar3 = ExtendProductionTime(puVar1);
 *     return uVar3;
 *   case 3:
 *     iVar2 = gv_ReplaceProductionWorker((uchar *)puVar1);
 *     return iVar2;
 *   case 4:
 *     iVar2 = ActivateGraveyardSection((uchar *)puVar1);
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

typedef unsigned int uint32_t;

unsigned int __cdecl AssignProductionSlot(int);
unsigned int __cdecl HireProductionWorker(int);
unsigned int __cdecl ExtendProductionTime(uint32_t*);
int __cdecl gv_ReplaceProductionWorker(uchar*);
int __cdecl ActivateGraveyardSection(uchar*);
int __cdecl gv_UpdateProductionProgress(uchar*);
int __cdecl gv_ValidateEntityAction(uchar*);

/* Dispatch handler: routes production commands based on the
 * sub-command type at cmd+0x10. Dispatches to:
 * 0=AssignProductionSlot, 1=HireProductionWorker,
 * 2=ExtendProductionTime, 3=ReplaceProductionWorker,
 * 4=ActivateGraveyardSection, 5=UpdateProductionProgress,
 * 6=ValidateEntityAction. Stamps timestamp and random seed. */

// FUNCTION: SERVER 0x10010260
int __cdecl cm_DispatchProduction(int cmd, char* result)
{
	uint32_t* data_ptr;
	int rc;
	unsigned int status;

	(void) result;

	*(int*) (cmd + 0x27) = g_timestamp_0b6c;
	rc = rand();
	*(int*) (cmd + 0x2b) = rc;
	data_ptr = (uint32_t*) (cmd + 0x10);
	switch (*(int*) (cmd + 0x10)) {
	case 0:
		status = AssignProductionSlot((int) data_ptr);
		return status;
	case 1:
		status = HireProductionWorker((int) data_ptr);
		return status;
	case 2:
		status = ExtendProductionTime(data_ptr);
		return status;
	case 3:
		rc = gv_ReplaceProductionWorker((uchar*) data_ptr);
		return rc;
	case 4:
		rc = ActivateGraveyardSection((uchar*) data_ptr);
		return rc;
	case 5:
		rc = gv_UpdateProductionProgress((uchar*) data_ptr);
		return rc;
	case 6:
		rc = gv_ValidateEntityAction((uchar*) data_ptr);
		return rc;
	default:
		return -1;
	}
}

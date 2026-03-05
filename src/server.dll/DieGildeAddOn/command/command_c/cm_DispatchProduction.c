// FUNCTION: SERVER 0x10010260
// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 144
// CFLAGS: /O2 /Gd
// SYMBOL: _DispatchProductionCommand

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 144B
 *    CFlags: 
 *    Symbol: _DispatchProductionCommand
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl DispatchProductionCommand(int param_1,char *param_2)
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
 *     iVar2 = ReplaceProductionWorker((uchar *)puVar1);
 *     return iVar2;
 *   case 4:
 *     iVar2 = ActivateGraveyardSection((uchar *)puVar1);
 *     return iVar2;
 *   case 5:
 *     iVar2 = UpdateProductionProgress((uchar *)puVar1);
 *     return iVar2;
 *   case 6:
 *     iVar2 = ValidateEntityAction((uchar *)puVar1);
 *     return iVar2;
 *   default:
 *     return -1;
 *   }
 * }
 */

#include "../command_internal.h"

typedef unsigned int uint32_t;

extern unsigned int __cdecl AssignProductionSlot(int);
extern unsigned int __cdecl HireProductionWorker(int);
extern unsigned int __cdecl ExtendProductionTime(uint32_t*);
extern int __cdecl ReplaceProductionWorker(uchar*);
extern int __cdecl ActivateGraveyardSection(uchar*);
extern int __cdecl UpdateProductionProgress(uchar*);
extern int __cdecl ValidateEntityAction(uchar*);

int __cdecl DispatchProductionCommand(int param_1, char* param_2)
{
	uint32_t* puVar1;
	int iVar2;
	unsigned int uVar3;

	*(int*) (param_1 + 0x27) = g_timestamp_0b6c;
	iVar2 = rand();
	*(int*) (param_1 + 0x2b) = iVar2;
	puVar1 = (uint32_t*) (param_1 + 0x10);
	switch (*(int*) (param_1 + 0x10)) {
	case 0:
		uVar3 = AssignProductionSlot((int) puVar1);
		return uVar3;
	case 1:
		uVar3 = HireProductionWorker((int) puVar1);
		return uVar3;
	case 2:
		uVar3 = ExtendProductionTime(puVar1);
		return uVar3;
	case 3:
		iVar2 = ReplaceProductionWorker((uchar*) puVar1);
		return iVar2;
	case 4:
		iVar2 = ActivateGraveyardSection((uchar*) puVar1);
		return iVar2;
	case 5:
		iVar2 = UpdateProductionProgress((uchar*) puVar1);
		return iVar2;
	case 6:
		iVar2 = ValidateEntityAction((uchar*) puVar1);
		return iVar2;
	default:
		return -1;
	}
}

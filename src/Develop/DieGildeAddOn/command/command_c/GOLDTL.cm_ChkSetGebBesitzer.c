
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 64B
 *    CFlags:
 *    Symbol: _find_validate
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ChkSetGebBesitzer(char *obj)
 *
 * {
 *   ushort *puVar1;
 *
 *                     / * Command validation handler for changing building ownership
 *                        (ChkSetGebBesitzer). Looks up the building entity using
 *                        gm_StartFilteredEntitySearch, checks its state flags, and validates the command.
 *                        Returns 0 if valid. * /
 *   puVar1 = gm_StartFilteredEntitySearch(1,1,*(undefined4 *)(obj + 0x10));
 *   if ((puVar1 != (ushort *)0x0) && ((puVar1[0x2d] & 2) != 0)) {
 *     return 0;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x256b,
 *                      s_cm_ChkSetGebBesitzer___Invalid_I_1002ca74,1);
 *   return 1;
 * }
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

// GLOBAL: GOLDTL 0x6b8300
extern int g_6b8300;
// GLOBAL: GOLD 0x633738
extern int g_6b8300;
// FUNCTION: GOLD 0x0040bf60
// SIZE: 96
// FUNCTION: GOLDTL 0x40ce80
// SIZE: 82
void* __cdecl fcn_00422460(void*, int);
void* __cdecl ahm_AllocateEntitySlot(void*, int, int, float);

void __cdecl cm_ChkSetGebBesitzer(char* cmd)
{
	void* e;
	void* r;
	e = *(void**) (cmd + 0x14);
	r = fcn_00422460(0, cmd + 0x130);
	if (r != 0) {
		if (*(int*) ((char*)&g_6b8300) != 0) {
			ahm_AllocateEntitySlot(r, *(int*) ((char*) e + 0x34), 0x7f, 3000.0f);
		} else {
			ahm_AllocateEntitySlot(r, *(int*) ((char*) e + 0x34), 0x7f, 1000.0f);
		}
	}
}

/* cm_ExClearLagerslot - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

// FUNCTION: GOLDTL 0x404410
// SIZE: 334


int __cdecl cm_ExClearLagerslot(short* cmd, uchar* result)
{
	int field;
	short* resolved;
	unsigned short* query_result;

	field = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 8));
	*(int*) (cmd + 8) = field;
	field = gm_ResolveEntityById(0, (void**) &resolved, 0, field);
	if (field == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x314b,
		                   s_cm_ExClearLagerslot___Invalid__L_1002d088, 1);
		return 1;
	}
	if ((*resolved == 0x2a) || (*resolved == 0x116)) {
		query_result = gm_ff_Objekt(*(int*) ((char*) resolved + 0x14), 1, 0,
		                        (uint) (ushort) cmd[0x14 / 2]);
		if (query_result == 0) {
			return 1;
		}
		if (*(int*) (query_result + 7) != 1) {
			return 1;
		}
		gm_RemoveObjectByType((void**) ((char*) resolved + 0x14), (uint) (ushort) cmd[0x14 / 2]);
		if (result != 0) {
			*result = 1;
		}
		return 0;
	}
	LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x3155,
	                   s_cm_ExClearLagerslot___Lager_has_n_1002d054, 1);
	return 1;
}

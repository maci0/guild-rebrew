/* cm_ExClearLagerslot - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ExClearLagerslot___Invalid__L_1002d088[];
extern char s_cm_ExClearLagerslot___Lager_has_n_1002d054[];
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

/* Execution handler: clears an inventory slot of a warehouse-like
 * entity.  Resolves the entity, verifies the slot holds a movable
 * object type, then removes it via gm_RemoveObjectByType.
 *
 * Byte-match note: same Finding 7-family allocator fixed-point as the
 * other resolve-with-&cmd handlers — the reference keeps the short*
 * base in esi and folds `mov [esi+0x10],eax`, passing &cmd in the
 * middle of gm_ResolveEntityById(0, &cmd, 0, field); every C shape
 * either CSE-hoists `lea esi,[eax+0x10]` (extra edi push, docs/
 * msvc6-allocator.md Finding 42) or reloads the param from its home
 * slot for the store.  The remainder (type checks, query call,
 * remove call, result-byte store) matches structurally with cascaded
 * register-role swaps (dx/cx, eax/edx). */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000e690
// SYMBOL: _cm_ExClearLagerslot
// SIZE: 191

int __cdecl cm_ExClearLagerslot(short* cmd, uchar* result)
{
	short* psVar1;
	int field;
	unsigned short* q;
	uint line;
	char* msg;

	psVar1 = cmd;
	field = gm_GetFieldByType((char*) psVar1, *(int*) (psVar1 + 8));
	*(int*) (cmd + 8) = field;
	field = gm_ResolveEntityById(0, (void**) &cmd, 0, field);
	if (field == 0) {
		msg = s_cm_ExClearLagerslot___Invalid__L_1002d088;
		line = 0x314b;
	} else {
		if ((*cmd == 0x2a) || (*cmd == 0x116)) {
			q = gm_StartEntityQuery(*(int*) ((char*) cmd + 0x14), 1, 0, (uint) (ushort) psVar1[0x14 / 2]);
			if (q == 0) {
				return 1;
			}
			if (*(int*) (q + 7) != 1) {
				return 1;
			}
			gm_RemoveObjectByType((void**) ((char*) cmd + 0x14), (uint) (ushort) psVar1[0x14 / 2]);
			if (result != 0) {
				*result = 1;
			}
			return 0;
		}
		msg = s_cm_ExClearLagerslot___Lager_has_n_1002d054;
		line = 0x3155;
	}
	LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, line, msg, 1);
	return 1;
}

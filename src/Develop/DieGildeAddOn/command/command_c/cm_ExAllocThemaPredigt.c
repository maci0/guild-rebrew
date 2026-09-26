#include "../command_internal.h"
#include "../../../Units/Error/error.h"

char* __cdecl gm_AllocObjekt(int, int, int);

/* Execution handler: allocates a sermon theme (Thema Predigt)
 * for a church/religious building entity. */
// FUNCTION: GOLDTL 0x466330
// SIZE: 176
// FUNCTION: SERVER 0x1000f2f0

int __cdecl cm_ExAllocThemaPredigt(int cmd, char* result)
{
	int field;
	char* obj;
	char* dst;
	uint f;

	*(int*) (cmd + 0x10) = g_next_object_id;
	field = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x14));
	*(int*) (cmd + 0x14) = field;
	obj = gm_AllocObjekt(field, 0x1b5, 1);
	if (obj == 0) {
		return 1;
	}
	f = 0x99099 * (unsigned char) *(char*) (cmd + 3);
	cmd += 0x18;
	dst = obj + 0x1c;
	*(int*) (0x10442d08 + f * 4) = *(int*) (obj + 2);
	obj[0x12] = 0x40;
	memcpy(dst, cmd, 7);
	obj[0x22] = 0;
	LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command\\command.c", 0x40db,
	                   "cm_ExAllocThemaPredigt(): Executed", 1);
	if (result != 0) {
		*result = 1;
		result[1] = 3;
		*(char**) (result + 6) = obj;
	}
	return 0;
}

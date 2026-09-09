/* cm_ExFree - proper C */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

/* Execution handler: frees/deallocates a game entity. Resolves
 * entity by ID and removes it from the game world. Logs error
 * on invalid entity ID. */

// FUNCTION: SERVER 0x1000d730
// SIZE: 180

int __cdecl cm_ExFree(int cmd, char* result)
{
	void* dyn;
	void* exist;
	void* static_rec;
	int field;
	int rc;

	field = gm_GetFieldByType((char*) cmd, (unsigned short) *(unsigned short*) (cmd + 0x10));
	*(unsigned short*) (cmd + 0x10) = (unsigned short) field;
	field &= 0xffff;
	rc = gm_ResolveEntityById(&dyn, &exist, &static_rec, field);
	if (rc == 0) {
		LogMessageInternal((char*) 0x1002c748, 0x2a09, (char*) 0x1002cc5c, 1);
		return 1;
	}
	if (dyn != 0) {
		rc = gm_CleanupBuildingEntity((unsigned char*) dyn);
		if (rc != 0) {
			return 1;
		}
	} else {
		if (exist != 0) {
			LogMessageInternal((char*) 0x1002c748, 0x2a21, (char*) 0x1002cc3c, 1);
			return 1;
		}
		gm_DeallocEntity((unsigned short) *(unsigned short*) static_rec, 1);
	}
	if (result != 0) {
		*result = 1;
	}
	return 0;
}

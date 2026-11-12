/* The native caller 0x4C7A60 keeps a live ecx across the call to 0x4C4DC0
 * and stores through it after the call, which MSVC 6 only emits when the callee
 * is defined in the same translation unit. Both bodies live in this file. */

extern char cm_LastEntityId[];
extern char cm_LastBuildingId[];
extern char cm_LastObjectId[];

/* ADDRESS: GOLD 0x004c4450 */
/* ADDRESS: GOLDTL 0x004c4dc0 */
int __cdecl fcn_004c4dc0(int a1, int a2)
{
	if (a2 == -2) {
		return *(int*) cm_LastEntityId;
	}
	if (a2 == -3) {
		return *(int*) cm_LastBuildingId;
	}
	if (a2 == -4) {
		return *(int*) cm_LastObjectId;
	}
	return a2;
}

int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl fcn_00504130(void* entity);
void __cdecl gm_KillSpieler(int entity_id, int flag);

/* ADDRESS: GOLDTL 0x004c7a60 */
int __cdecl fcn_004c7a60(void* e, char* flag)
{
	void* existing;
	void* stat; unsigned short id;

	id = (unsigned short) fcn_004c4dc0((int) e, (int) *(unsigned short*) ((char*) e + 0x10)); *(unsigned short*) ((char*) e + 0x10) = id;
	if (!gm_ResolveEntityById(&e, &existing, &stat, (int) id))
		return 1;
	if (e != 0) {
		if (fcn_00504130(e))
			return 1;
	}
	else {
		if (existing != 0)
			return 1;
		gm_KillSpieler((int) *(unsigned short*) stat, 1);
	}
	if (flag != 0)
		*flag = 1;
	return 0;
}

int __cdecl fcn_004c4dc0(int a1, int a2);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);
int __cdecl fcn_00504130(void* entity);
void __cdecl gm_KillSpieler(int entity_id, int flag);

/* ADDRESS: GOLDTL 0x004c7a60 */
int __cdecl fcn_004c7a60(void* e, char* flag)
{
	void* existing;
	void* stat;

	*(unsigned short*) ((char*) e + 0x10) = (unsigned short) fcn_004c4dc0((int) e, (int) *(unsigned short*) ((char*) e + 0x10));
	if (!gm_ResolveEntityById(&e, &existing, &stat, (int) *(unsigned short*) ((char*) e + 0x10)))
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

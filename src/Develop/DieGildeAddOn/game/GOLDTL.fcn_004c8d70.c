int __cdecl cm_ResolveSpecialEntityId(char*, int);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);


/* ADDRESS: GOLDTL 0x004c8d70 */
/* ADDRESS: GOLDDE 0x004b6550 */
int __cdecl cm_ClientExChangeFloat(char* m, char* out)
{
	void* dyn;
	void* ex;
	void* st;
	char* p;

	*(int*) (m + 0x10) = cm_ResolveSpecialEntityId(m, *(int*) (m + 0x10));
	if (gm_ResolveEntityById(&dyn, &ex, &st, *(int*) (m + 0x10)) == 0)
		return 1;
	p = st;
	if (p == 0)
		p = ex;
	if (p == 0)
		p = dyn;
	p += *(int*) (m + 0x14);
	*(float*) p += *(float*) (m + 0x18);
	if (out != 0)
		*out = 1;
	return 0;
}

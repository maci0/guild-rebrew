int __cdecl fcn_004c4dc0(char*, int);
int __cdecl gm_ResolveEntityById(void** dynamic, void** existing, void** static_ptr, int entity_id);

// FUNCTION: GOLDTL 0x004c8d70
// SIZE: 110

int __cdecl fcn_004c8d70(char* m, char* out)
{
	void* dyn;
	void* ex;
	void* st;
	char* p;

	*(int*) (m + 0x10) = fcn_004c4dc0(m, *(int*) (m + 0x10));
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

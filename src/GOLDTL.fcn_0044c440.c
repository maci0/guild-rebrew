// FUNCTION: GOLDTL 0x44c440

void __cdecl gv_SpawnEntities(void*);

void __cdecl fcn_0044c440(char* p)
{
	if (p == 0) {
		return;
	}
	if (*(int*) (p + 0x1e0) <= 0) {
		return;
	}
	gv_SpawnEntities(p);
}

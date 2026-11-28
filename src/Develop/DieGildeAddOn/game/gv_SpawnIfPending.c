

void __cdecl gv_SpawnEntities(void*);

/* ADDRESS: GOLDDE 0x004428e0 */
void __cdecl gv_SpawnIfPending(char* p)
{
	if (p == 0) {
		return;
	}
	if (*(int*) (p + 0x1e0) <= 0) {
		return;
	}
	gv_SpawnEntities(p);
}

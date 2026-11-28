int __cdecl gm_QueryEntities(int a, int b, int c, int d, int e);
char* __cdecl ai_PickIdleGraveyardWorker(char* owner);
int __cdecl he_StartHandlungSearch(int a, int b, int c, int d, int e);
unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x0048fb10 */
/* ADDRESS: GOLDDE 0x0047e9e0 */
int __cdecl ai_PlanDeathPact(int unused, char* actor, char* req, char* out)
{
	char* worker;

	*(int*) (req + 0x10) = 3;
	*(int*) (req + 0xc) = *(int*) (actor + 1);
	if (!gm_QueryEntities(*(int*) (actor + 0x5d), 2, 0, 0x1fb, 6)) {
		return 0;
	}
	worker = ai_PickIdleGraveyardWorker(actor);
	if (!worker) {
		return 0;
	}
	if (he_StartHandlungSearch(2, 0, 0x8a, 3, *(int*) (actor + 1))) {
		return 0;
	}
	*(int*) (out + 4) = *(int*) (worker + 4);
	return !gm_RandomMod(3);
}

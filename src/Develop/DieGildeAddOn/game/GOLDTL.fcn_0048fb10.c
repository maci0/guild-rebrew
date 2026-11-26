int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
char* __cdecl ai_PickIdleGraveyardWorker(char* owner);
int __cdecl he_StartHandlungSearch(int a, int b, int c, int d, int e);
unsigned short __cdecl gm_RandomMod(int n);

/* ADDRESS: GOLDTL 0x0048fb10 */
int __cdecl fcn_0048fb10(int a1, char* e, char* r, char* out)
{
	char* c;

	*(int*) (r + 0x10) = 3;
	*(int*) (r + 0xc) = *(int*) (e + 1);
	if (!fcn_00502cd0(*(int*) (e + 0x5d), 2, 0, 0x1fb, 6)) {
		return 0;
	}
	c = ai_PickIdleGraveyardWorker(e);
	if (!c) {
		return 0;
	}
	if (he_StartHandlungSearch(2, 0, 0x8a, 3, *(int*) (e + 1))) {
		return 0;
	}
	*(int*) (out + 4) = *(int*) (c + 4);
	return !gm_RandomMod(3);
}

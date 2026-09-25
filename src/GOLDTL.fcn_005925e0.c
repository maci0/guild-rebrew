// FUNCTION: GOLD 0x0058a0d0
// SIZE: 79
// FUNCTION: GOLDTL 0x5925e0
// SIZE: 79

extern char g_779d00[];

char* __cdecl fcn_005049a0(char*);
char* __cdecl gm_SetupEntityQuery(char*);

void __cdecl fcn_005925e0(int idx, char* e)
{
	char* r;

	r = 0;
	if (*e != 0x1d) {
		r = fcn_005049a0(e);
		if (r == 0) {
			r = gm_SetupEntityQuery(e);
		}
	}
	*(int*) (g_779d00 + 4 + idx * 12) = *(int*) (e + 1);
	if (r != 0) {
		*(int*) (g_779d00 + 8 + idx * 12) = *(int*) (r + 2);
		return;
	}
	*(int*) (g_779d00 + 8 + idx * 12) = -1;
}

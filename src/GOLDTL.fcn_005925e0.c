// FUNCTION: GOLDTL 0x5925e0
// SIZE: 79

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
	*(int*) (idx * 12 + 0x779d04) = *(int*) (e + 1);
	if (r != 0) {
		*(int*) (idx * 12 + 0x779d08) = *(int*) (r + 2);
		return;
	}
	*(int*) (idx * 12 + 0x779d08) = -1;
}

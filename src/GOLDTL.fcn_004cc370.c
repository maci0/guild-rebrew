// FUNCTION: GOLDTL 0x4cc370
// SIZE: 82

char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl fcn_00505370(char*);
void __cdecl fcn_0052db70(char*);

int __cdecl fcn_004cc370(char* a1, char* a2)
{
	char* p;

	p = gm_StartFilteredEntitySearch(1, 1, *(int*) (a1 + 0x10));
	if (p != 0 && *(int*) (p + 0x61) != 0 && fcn_00505370(p) == 0) {
		fcn_0052db70(p);
	}
	if (a2 != 0) {
		a2[0] = 1;
		a2[1] = 0;
		*(int*) (a2 + 6) = 0;
	}
	return 0;
}

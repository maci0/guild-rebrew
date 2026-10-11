int __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
char* __cdecl fcn_0048f450(char* owner);
int __cdecl fcn_005463a0(int a, int b, int c, int d, int e);
unsigned short __cdecl gm_RandomMod(int n);

// FUNCTION: GOLD 0x00490560
// FUNCTION: GOLDTL 0x48fb10
int __cdecl fcn_0048fb10(int a1, char* e, char* r, char* out)
{
	char* c;

	*(int*) (r + 0x10) = 3;
	*(int*) (r + 0xc) = *(int*) (e + 1);
	if (!fcn_00502cd0(*(int*) (e + 0x5d), 2, 0, 0x1fb, 6)) {
		return 0;
	}
	c = fcn_0048f450(e);
	if (!c) {
		return 0;
	}
	if (fcn_005463a0(2, 0, 0x8a, 3, *(int*) (e + 1))) {
		return 0;
	}
	*(int*) (out + 4) = *(int*) (c + 4);
	return !gm_RandomMod(3);
}

// FUNCTION: GOLDTL 0x4cb650
// SIZE: 151

char* __cdecl fcn_00503fe0(int, ...);
unsigned short* __cdecl fcn_00508e40(int);
void __cdecl fcn_005059b0(char*, int, int);

int __cdecl fcn_004cb650(char* x, char* out)
{
	char* e;
	unsigned short* a;
	unsigned short* b;

	e = fcn_00503fe0(1, 1, *(int*) (x + 0x10));
	if (e == 0)
		return 1;
	a = fcn_00508e40(*(int*) (x + 0x18));
	if (a == 0 && *(int*) (x + 0x18) != -1)
		return 1;
	b = fcn_00508e40(*(int*) (x + 0x14));
	if (b == 0 && *(int*) (x + 0x14) != -1)
		return 2;
	fcn_005059b0(e, *b, *a);
	if (out != 0) {
		out[0] = 2;
		out[1] = 0;
		*(int*) (out + 6) = 0;
	}
	return 0;
}

extern char* g_772500;

void __cdecl fcn_0041d9e0(const char* msg);

// FUNCTION: GOLDTL 0x469960
// SIZE: 90
void __cdecl fcn_00469960(int i)
{
	char* e;
	int* p;

	e = g_772500 + i * 0x54;
	if ((*(int*) (e + 0x3c) == 5 || *(int*) (e + 0x3c) == 8) && *(int*) (e + 0x30) == 0) {
		i = *(int*) (e + 0x4c);
	}
	p = (int*) (g_772500 + i * 0x54 + 0x40);
	if (*p > 0) {
		*p -= 1;
		return;
	}
	fcn_0041d9e0((const char*) 0x67d4e0);
}

extern char* g_772500;
extern char g_67d4e0[];

void __cdecl fcn_0041d9e0(const char* msg);

// FUNCTION: GOLD 0x0046cab0
// SIZE: 90
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
	fcn_0041d9e0(g_67d4e0);
}

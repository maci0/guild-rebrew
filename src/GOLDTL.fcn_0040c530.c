// FUNCTION: GOLD 0x0040b610
// SIZE: 112
// FUNCTION: GOLDTL 0x0040c530
// SIZE: 112

extern char* g_6b7e98;
char* __cdecl fcn_00426fd0(int id);
void __cdecl fcn_00428340(char* o, int n, ...);

char* __cdecl fcn_0040c530(int* a, int* b, int* c)
{
	char* o;

	o = fcn_00426fd0(*a);
	if (o == 0) {
		return 0;
	}
	*(int*) (o + 0x104) = *(int*) (g_6b7e98 + 0x104);
	*(int*) (o + 0xc8c) = *(int*) (g_6b7e98 + 0xc8c);
	*(int*) (o + 0xc90) = *(int*) (g_6b7e98 + 0xc90);
	fcn_00428340(o, 2, *b, *c);
	return o;
}

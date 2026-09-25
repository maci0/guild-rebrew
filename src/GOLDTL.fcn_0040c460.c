extern char* g_6b7e98;
// FUNCTION: GOLD 0x0040b5b0
// SIZE: 90
// FUNCTION: GOLDTL 0x40c460
// SIZE: 90

char* __cdecl fcn_00426fd0(int);
void __cdecl fcn_00428230(char*);

char* __cdecl fcn_0040c460(int* a1)
{
	char* p;

	p = fcn_00426fd0(*a1);
	if (p == 0) {
		return 0;
	}
	*(int*) (p + 0x104) = *(int*) (g_6b7e98 + 0x104);
	*(int*) (p + 0xc8c) = *(int*) (g_6b7e98 + 0xc8c);
	*(int*) (p + 0xc90) = *(int*) (g_6b7e98 + 0xc90);
	fcn_00428230(p);
	return p;
}

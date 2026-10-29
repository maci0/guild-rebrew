

extern char* g_6b7e98;
char* __cdecl fcn_00426fd0(int id);
void __cdecl fcn_00428340(char* o, int n, ...);

char* __cdecl fcn_0040c5a0(int* a, int* b)
{
	char* o;

	o = fcn_00426fd0(*a);
	if (o == 0) {
		return 0;
	}
	*(int*) (o + 0x104) = *(int*) (g_6b7e98 + 0x104);
	*(int*) (o + 0xc8c) = *(int*) (g_6b7e98 + 0xc8c);
	*(int*) (o + 0xc90) = *(int*) (g_6b7e98 + 0xc90);
	fcn_00428340(o, 1, *b);
	return o;
}

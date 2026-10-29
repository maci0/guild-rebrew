extern char* g_6b7e98;



char* __cdecl fcn_00426fd0(int);
void __cdecl evt_RunScript(char*);

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
	evt_RunScript(p);
	return p;
}

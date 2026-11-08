

char* __cdecl evt_LoadGfxScript(char*);
void __cdecl fcn_00428340(char*, int, int);

void __cdecl fcn_0040d0f0(char* a1)
{
	char* p;

	p = evt_LoadGfxScript(a1 + 0x90);
	if (p != 0) {
		fcn_00428340(p, 1, *(int*) (a1 + 0x180));
		*(int*) (p + 0x104) = *(int*) (a1 + 0x17c);
	}
}

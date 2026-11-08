


extern int g_772f3c;

char* __cdecl evt_LoadGfxScript(int);
void __cdecl fcn_004284d0(char*, int);

int __cdecl fcn_004e44b0(int a1, int a2)
{
	char* p;

	if (g_772f3c == 0) {
		p = evt_LoadGfxScript(a1);
		if (p != 0) {
			fcn_004284d0(p, a2);
			return *(int*) (p + 0x100);
		}
	}
	return 0;
}

extern char* g_1042320;
extern char g_1052a40[];

void __cdecl fcn_00459be0(int a);
int __cdecl fcn_00459cd0(char* p);

// FUNCTION: GOLDTL 0x45a1c0
int __cdecl fcn_0045a1c0(void)
{
	int n;
	char* p;

	n = 0;
	fcn_00459be0(0x104);
	for (p = g_1042320; p != g_1052a40; p = *(char**) (p + 0x160)) {
		n += fcn_00459cd0(p);
	}
	return n;
}

extern char* g_1042c38;
extern char g_1042d00[];

void __cdecl fcn_00459be0(int a);
int __cdecl fcn_00459c70(char* p);

// FUNCTION: GOLDTL 0x45a130
// SIZE: 61
int __cdecl fcn_0045a130(void)
{
	int n;
	char* p;

	n = 0;
	fcn_00459be0(0x110);
	for (p = g_1042c38; p != g_1042d00; p = *(char**) (p + 0x1f8)) {
		n += fcn_00459c70(p);
	}
	return n;
}
